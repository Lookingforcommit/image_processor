#pragma once

#include <cstdint>

#include "image.h"
#include "filters/base.h"

class CropFilter : public BaseFilter {
 private:
  int32_t _height{};
  int32_t _width{};
 public:
  CropFilter(int32_t height, int32_t width) : _height{height}, _width{width} {};
  void Apply(Image &img) override;
};
