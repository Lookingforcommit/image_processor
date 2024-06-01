#include "nostalgic.h"

#include <cstdint>
#include <unordered_map>
#include <string>
#include <algorithm>

#include "image.h"

double NostalgicFilter::CalcColorComp(RGB comp_coeffs, RGB pixel) {
  double blue_val = pixel.blue * comp_coeffs.blue;
  double green_val = pixel.green * comp_coeffs.green;
  double red_val = pixel.red * comp_coeffs.red;
  return std::max(0.0, std::min(1.0, blue_val + green_val + red_val));
}

void NostalgicFilter::Apply(Image &img) {
  std::unordered_map<std::string, int32_t> img_size = img.GetSize();
  RGB pixel, pixel_copy;
  for (int32_t row = 0; row < img_size["height"]; ++row) {
    for (int32_t idx = 0; idx < img_size["width"]; ++idx) {
      pixel = img.GetPixel(row, idx);
      pixel_copy = pixel;
      pixel.blue = CalcColorComp(COLOR_MUL.blue_coef, pixel_copy);
      pixel.green = CalcColorComp(COLOR_MUL.green_coef, pixel_copy);
      pixel.red = CalcColorComp(COLOR_MUL.red_coef, pixel_copy);
      img.SetPixel(pixel, row, idx);
    }
  }
}
