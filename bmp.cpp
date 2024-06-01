#include "bmp.h"

#include <cstdint>
#include <unordered_map>
#include <string>
#include <array>
#include <filesystem>

#include "image.h"
#include "exceptions.h"
#include <exception>

int CalcRowPadding(int32_t width, uint16_t bit_per_pxl) {
  std::unordered_map<uint16_t, int32_t> pad_map = {
      {24, width % 4},
  };
  if (pad_map.find(bit_per_pxl) == pad_map.end()) {
    throw std::exception{};
  }
  return pad_map[bit_per_pxl];
}

void BMPReader::ReadFile(const std::string &filename, Image &img) {
  std::ifstream bmp_file{filename, std::ios::binary};
  std::filesystem::path path{filename};
  if (not bmp_file.is_open()) {
    throw FileOpenException{filename};
  }
  ReadFileHeader(bmp_file);
  uint32_t file_size = std::filesystem::file_size(path);
  if (this->_file_header.bf_type != BMP_FILE_TYPE or this->_file_header.bf_size != file_size) {
    throw InvalidImageFormatException{filename};
  }
  ReadInfoHeader(bmp_file);
  if (this->_info_header.bi_height < 0) {
    throw InvalidImageFormatException{filename};
  }
  try {
    ReadImage(bmp_file, img);
  }
  catch (const std::exception &e) {
    throw InvalidImageFormatException{filename};
  }
}

void BMPReader::ReadImage(std::ifstream &bmp_file, Image &img) {
  img.Resize(this->_info_header.bi_height, this->_info_header.bi_width);
  RGB pixel = {};
  std::streampos padded_width = CalcRowPadding(this->_info_header.bi_width,
                                               this->_info_header.bi_bit_count);
  int32_t ins_row;
  std::array<unsigned char, 3> pxl_colors{};
  for (int32_t row = 0; row < this->_info_header.bi_height; ++row) {
    for (int32_t idx = 0; idx < this->_info_header.bi_width; ++idx) {
      ins_row = this->_info_header.bi_height - row - 1;
      bmp_file.read((char *) &pxl_colors, sizeof(pxl_colors));
      pixel.SetColors(pxl_colors);
      img.SetPixel(pixel, ins_row, idx);
    }
    bmp_file.seekg(bmp_file.tellg() + padded_width);
  }
}

void BMPReader::ReadFileHeader(std::ifstream &bmp_file) {
  bmp_file.read((char *) &(this->_file_header), sizeof(this->_file_header));
}

void BMPReader::ReadInfoHeader(std::ifstream &bmp_file) {
  bmp_file.read((char *) &(this->_info_header), sizeof(this->_info_header));
}

BMPFileHeader BMPReader::GetFileHeader() const {
  return this->_file_header;
}

BMPInfoHeader BMPReader::GetInfoHeader() const {
  return this->_info_header;
}

void BMPWriter::WriteFile(const std::string &filename, Image &img, BMPFileHeader file_header,
                          BMPInfoHeader info_header) {
  this->_file_header = file_header;
  this->_info_header = info_header;
  std::unordered_map<std::string, int32_t> img_size = img.GetSize();
  std::ofstream bmp_file{filename, std::ios::binary};
  uint32_t padded_width = CalcRowPadding(img_size["width"], info_header.bi_bit_count);
  this->_info_header.bi_height = img_size["height"];
  this->_info_header.bi_width = img_size["width"];
  this->_file_header.bf_size = CalcBMPSize(padded_width);
  WriteFileHeader(bmp_file);
  WriteInfoHeader(bmp_file);
  WriteImage(bmp_file, img, padded_width);
}

void BMPWriter::WriteImage(std::ofstream &bmp_file, Image &img, uint32_t padded_width) const {
  RGB pixel;
  int32_t ins_row;
  std::vector<unsigned char> padding_arr(padded_width, 0);
  std::array<unsigned char, 3> pxl_colors{};
  for (int32_t row = 0; row < this->_info_header.bi_height; ++row) {
    for (int32_t idx = 0; idx < this->_info_header.bi_width; ++idx) {
      ins_row = this->_info_header.bi_height - row - 1;
      pixel = img.GetPixel(ins_row, idx);
      pixel.GetColors(pxl_colors);
      bmp_file.write((char *) &pxl_colors, sizeof(pxl_colors));
    }
    bmp_file.write((char *) &padding_arr, padded_width);
  }
}

uint32_t BMPWriter::CalcBMPSize(uint32_t padded_width) { // Calculates output image size in bytes
  uint32_t height = this->_info_header.bi_height, width = this->_info_header.bi_width;
  uint32_t total_size = height * (width * this->_info_header.bi_bit_count / 8 + padded_width);
  total_size += sizeof(this->_info_header) + sizeof(this->_file_header);
  return total_size;
}

void BMPWriter::WriteFileHeader(std::ofstream &bmp_file) {
  bmp_file.write((char *) &(this->_file_header), sizeof(this->_file_header));
}

void BMPWriter::WriteInfoHeader(std::ofstream &bmp_file) {
  bmp_file.write((char *) &(this->_info_header), sizeof(this->_info_header));
}
