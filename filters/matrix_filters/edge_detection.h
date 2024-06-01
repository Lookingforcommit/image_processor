#pragma once

#include <memory>

#include "image.h"
#include "matrix.h"

class EdgeFilter : public MatrixFilter {
 private:
  const DoubleMatrix COEF_MATRIX{
      {0, -1, 0},
      {-1, 4, -1},
      {0, -1, 0}
  };
  double _threshold;
 public:
  explicit EdgeFilter(double threshold) : _threshold{threshold} {};
  void Apply(Image &img) override;
};