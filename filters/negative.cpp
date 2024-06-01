#include "negative.h"

#include <cstdint>
#include <string>
#include <unordered_map>

#include "image.h"

void NegativeFilter::Apply(Image &img) {
  std::unordered_map<std::string, int32_t> img_size = img.GetSize();
  RGB pixel;
  for (int32_t row = 0; row < img_size["height"]; ++row) {
    for (int32_t idx = 0; idx < img_size["width"]; ++idx) {
      pixel = img.GetPixel(row, idx);
      pixel.red = 1 - pixel.red;
      pixel.green = 1 - pixel.green;
      pixel.blue = 1 - pixel.blue;
      img.SetPixel(pixel, row, idx);
    }
  }
}
