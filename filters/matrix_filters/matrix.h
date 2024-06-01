#pragma once

#include <vector>
#include <cstdint>
#include <memory>

#include "filters/base.h"
#include "image.h"

typedef std::vector<std::vector<double>> DoubleMatrix;

class MatrixFilter : public BaseFilter {
 protected:
  virtual std::unique_ptr<RGBMatrix> CalcNeighborsMatrix(Image &img, int32_t row, int32_t idx);
  virtual RGB CalcPixelVal(Image &img, const DoubleMatrix &coef_matrix, int32_t row, int32_t idx);
};
