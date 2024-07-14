#include "image.h"

#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

void RGB::SetColors(std::array<unsigned char, 3> &rgb_colors) {
  this->blue = rgb_colors[0] / 255.0;
  this->green = rgb_colors[1] / 255.0;
  this->red = rgb_colors[2] / 255.0;
}

void RGB::GetColors(std::array<unsigned char, 3> &rgb_colors) const {
  rgb_colors[0] = static_cast<unsigned char>(this->blue * 255.0);
  rgb_colors[1] = static_cast<unsigned char>(this->green * 255.0);
  rgb_colors[2] = static_cast<unsigned char>(this->red * 255.0);
}

Image::Image(int32_t height, int32_t width) {
  this->Resize(height, width);
}

RGB Image::GetPixel(int32_t row, int32_t idx) const {
  return this->_matrix[row][idx];
}

void Image::SetPixel(RGB pixel, int32_t row, int32_t idx) {
  this->_matrix[row][idx] = pixel;
}

std::unordered_map<std::string, int32_t> Image::GetSize() const {
  std::unordered_map<std::string, int32_t> ans;
  ans["height"] = this->_height;
  ans["width"] = this->_width;
  return ans;
}

void Image::Resize(int32_t new_height, int32_t new_width) {
  this->_matrix.resize(new_height, std::vector<RGB>(new_width));
  for (int i = 0; i < std::min(this->_height, new_height); ++i) {
    this->_matrix[i].resize(new_width);
  }
  this->_height = new_height;
  this->_width = new_width;
}
