#include "sharp.h"

#include <string>
#include <cstdint>
#include <unordered_map>

#include "image.h"

void SharpFilter::Apply(Image &img) {
  Image image_copy{img};
  std::unordered_map<std::string, int32_t> img_size = img.GetSize();
  RGB pixel;
  for (int row = 0; row < img_size["height"]; ++row) {
    for (int idx = 0; idx < img_size["width"]; ++idx) {
      pixel = CalcPixelVal(image_copy, this->COEF_MATRIX, row, idx);
      img.SetPixel(pixel, row, idx);
    }
  }
}
