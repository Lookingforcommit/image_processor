#pragma once

#include "image.h"
#include "matrix.h"

class SharpFilter : public MatrixFilter {
 private:
  const DoubleMatrix COEF_MATRIX{
      {0, -1, 0},
      {-1, 5, -1},
      {0, -1, 0}
  };
 public:
  void Apply(Image &img) override;
};
