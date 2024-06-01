#pragma once

#include <fstream>
#include <cstdint>
#include <string>

#include "image.h"

const uint16_t BMP_FILE_TYPE = 19778;

int CalcRowPadding(int32_t width, uint16_t bit_per_pxl);

#pragma pack(push, 1)
struct BMPFileHeader {
  [[maybe_unused]] uint16_t bf_type;
  [[maybe_unused]] uint32_t bf_size;
  [[maybe_unused]] uint16_t bf_reserved_1;
  [[maybe_unused]] uint16_t bf_reserved_2;
  [[maybe_unused]] uint32_t bf_off_bits;
};

struct BMPInfoHeader {
  [[maybe_unused]] uint32_t bi_size;
  int32_t bi_width;
  int32_t bi_height;
  [[maybe_unused]] uint16_t bi_planes;
  uint16_t bi_bit_count;
  [[maybe_unused]] uint32_t bi_compression;
  [[maybe_unused]] uint32_t bi_size_image;
  [[maybe_unused]] int32_t bi_xpels_per_meter;
  [[maybe_unused]] int32_t bi_ypels_per_meter;
  [[maybe_unused]] uint32_t bi_clr_used;
  [[maybe_unused]] uint32_t bi_clr_important;
};
#pragma pack(pop)

class BMPReader {
 private:
  BMPFileHeader _file_header{};
  BMPInfoHeader _info_header{};
  void ReadImage(std::ifstream &bmp_file, Image &img);
  void ReadFileHeader(std::ifstream &bmp_file);
  void ReadInfoHeader(std::ifstream &bmp_file);
 public:
  void ReadFile(const std::string &filename, Image &image);
  [[nodiscard]] BMPFileHeader GetFileHeader() const;
  [[nodiscard]] BMPInfoHeader GetInfoHeader() const;
};

class BMPWriter {
 private:
  BMPFileHeader _file_header{};
  BMPInfoHeader _info_header{};
  void WriteImage(std::ofstream &bmp_file, Image &img, uint32_t padded_width) const;
  void WriteFileHeader(std::ofstream &bmp_file);
  void WriteInfoHeader(std::ofstream &bmp_file);
  uint32_t CalcBMPSize(uint32_t padded_width);
 public:
  void WriteFile(const std::string &filename, Image &img, BMPFileHeader file_header, BMPInfoHeader info_header);
};

