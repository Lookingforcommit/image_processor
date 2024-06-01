#pragma once

#include "image.h"
#include "filters/base.h"

class GrayScaleFilter : public BaseFilter {
 private:
  const double RED_MUL = 0.299;
  const double GREEN_MUL = 0.587;
  const double BLUE_MUL = 0.114;
 public:
  void Apply(Image &img) override;
};