#include "grayscale.h"

#include <string>
#include <cstdint>
#include <unordered_map>

#include "image.h"

void GrayScaleFilter::Apply(Image &img) {
  std::unordered_map<std::string, int32_t> img_size = img.GetSize();
  RGB pixel;
  double color_val;
  for (int32_t row = 0; row < img_size["height"]; ++row) {
    for (int32_t idx = 0; idx < img_size["width"]; ++idx) {
      pixel = img.GetPixel(row, idx);
      color_val = pixel.red * RED_MUL + pixel.green * GREEN_MUL + pixel.blue * BLUE_MUL;
      pixel.red = pixel.green = pixel.blue = color_val;
      img.SetPixel(pixel, row, idx);
    }
  }
}
