#include "edge_detection.h"

#include <cstdint>
#include <string>
#include <unordered_map>

#include "image.h"
#include "filters/grayscale.h"

void EdgeFilter::Apply(Image &img) {
  GrayScaleFilter preprocess_filter{};
  preprocess_filter.Apply(img);
  Image image_copy{img};
  std::unordered_map<std::string, int32_t> img_size = img.GetSize();
  RGB pixel;
  for (int row = 0; row < img_size["height"]; ++row) {
    for (int idx = 0; idx < img_size["width"]; ++idx) {
      pixel = CalcPixelVal(image_copy, COEF_MATRIX, row, idx);
      if (pixel.blue > this->_threshold) {
        pixel.blue = pixel.green = pixel.red = 1;
      } else {
        pixel.blue = pixel.green = pixel.red = 0;
      }
      img.SetPixel(pixel, row, idx);
    }
  }
}
