#pragma once

#include "image.h"
#include "filters/base.h"

class NegativeFilter : public BaseFilter {
 public:
  void Apply(Image &img) override;
};
