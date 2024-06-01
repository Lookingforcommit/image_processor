#pragma once

#include <vector>
#include <unordered_map>
#include <cstdint>
#include <string>

struct RGB {
  double blue{0};
  double green{0};
  double red{0};
  void SetColors(std::array<unsigned char, 3> &rgb_colors); // convert colors to double and write to structure
  void GetColors(std::array<unsigned char, 3> &rgb_colors) const; // read colors from structure and convert them to char
};

typedef std::vector<std::vector<RGB>> RGBMatrix;

class Image {
 private:
  RGBMatrix _matrix{};
  int32_t _height{};
  int32_t _width{};
 public:
  Image() = default;
  Image(int32_t height, int32_t width);
  [[nodiscard]] RGB GetPixel(int32_t row, int32_t idx) const;
  void SetPixel(RGB pixel, int32_t row, int32_t idx);
  void Resize(int32_t new_height, int32_t new_width);
  [[nodiscard]] std::unordered_map<std::string, int32_t> GetSize() const;
};
