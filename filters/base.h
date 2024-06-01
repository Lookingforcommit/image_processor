#pragma once

#include "image.h"

class BaseFilter {
 public:
  virtual void Apply(Image &img) = 0;
  virtual ~BaseFilter() = default;
};
