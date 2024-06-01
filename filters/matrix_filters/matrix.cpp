#include "matrix.h"

#include <cstdint>
#include <memory>
#include <vector>
#include <unordered_map>

#include "image.h"

RGB MatrixFilter::CalcPixelVal(Image &img, const DoubleMatrix &coef_matrix, int32_t row, int32_t idx) {
  std::unique_ptr<RGBMatrix> nbr_matrix_ptr = CalcNeighborsMatrix(img, row, idx);
  RGB res_pixel;
  for (int i = 0; i < nbr_matrix_ptr->size(); ++i) {
    for (int j = 0; j < (*nbr_matrix_ptr)[0].size(); ++j) {
      res_pixel.blue += coef_matrix[i][j] * (*nbr_matrix_ptr)[i][j].blue;
      res_pixel.green += coef_matrix[i][j] * (*nbr_matrix_ptr)[i][j].green;
      res_pixel.red += coef_matrix[i][j] * (*nbr_matrix_ptr)[i][j].red;
    }
  }
  res_pixel.blue = std::max(0.0, std::min(1.0, res_pixel.blue));
  res_pixel.green = std::max(0.0, std::min(1.0, res_pixel.green));
  res_pixel.red = std::max(0.0, std::min(1.0, res_pixel.red));
  return res_pixel;
}

std::unique_ptr<RGBMatrix> MatrixFilter::CalcNeighborsMatrix(Image &img, int32_t row, int32_t idx) {
  std::unique_ptr<RGBMatrix> nbr_matrix_ptr = std::make_unique<RGBMatrix>(3, std::vector < RGB > {3});
  std::unordered_map<std::string, int32_t> img_size = img.GetSize();
  int prev_row = std::max(0, row - 1), prev_idx = std::max(0, idx - 1);
  int next_row = std::min(img_size["height"] - 1, row + 1), next_idx = std::min(img_size["width"] - 1, idx + 1);
  (*nbr_matrix_ptr)[0][0] = img.GetPixel(prev_row, prev_idx);
  (*nbr_matrix_ptr)[0][1] = img.GetPixel(prev_row, idx);
  (*nbr_matrix_ptr)[0][2] = img.GetPixel(prev_row, next_idx);
  (*nbr_matrix_ptr)[1][0] = img.GetPixel(row, prev_idx);
  (*nbr_matrix_ptr)[1][1] = img.GetPixel(row, idx);
  (*nbr_matrix_ptr)[1][2] = img.GetPixel(row, next_idx);
  (*nbr_matrix_ptr)[2][0] = img.GetPixel(next_row, prev_idx);
  (*nbr_matrix_ptr)[2][1] = img.GetPixel(next_row, idx);
  (*nbr_matrix_ptr)[2][2] = img.GetPixel(next_row, next_idx);
  return nbr_matrix_ptr;
}
