#pragma once

#include "image.h"
#include "filters/base.h"

struct ColorCoeffStruct {
  RGB blue_coef;
  RGB green_coef;
  RGB red_coef;
};

class NostalgicFilter : public BaseFilter {
 private:
  const ColorCoeffStruct COLOR_MUL{
      {0.131, 0.534, 0.272},
      {0.168, 0.686, 0.349},
      {0.189, 0.769, 0.393}
  };
  static double CalcColorComp(RGB comp_coeffs, RGB pixel);
 public:
  void Apply(Image &img) override;
};
