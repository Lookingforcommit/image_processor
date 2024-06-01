#include "crop.h"

#include <cstdint>
#include <string>
#include <unordered_map>

#include "image.h"

void CropFilter::Apply(Image &img) {
  std::unordered_map<std::string, int32_t> img_size;
  img_size = img.GetSize();
  this->_height = std::min(this->_height, img_size["height"]);
  this->_width = std::min(this->_width, img_size["width"]);
  img.Resize(this->_height, this->_width);
}
