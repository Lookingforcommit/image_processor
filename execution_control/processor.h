#pragma once

#include <vector>
#include <memory>

#include "image.h"
#include "shared_structures.h"
#include "filters/base.h"
#include "producer.h"

class Processor {
 private:
  const std::unordered_map<std::string, FilterProducerFunc> FILTER_PRODUCER_FUNC_MAP = {
      {"-crop", CreateCropFilter},
      {"-gs", CreateGrayScaleFilter},
      {"-neg", CreateNegativeFilter},
      {"-sharp", CreateSharpFilter},
      {"-edge", CreateEdgeFilter},
      {"-nostalg", CreateNostalgicFilter}
  };
  std::vector<std::unique_ptr<BaseFilter>> _filters;
 public:
  void CreateFilters(std::vector<FilterParams> &filter_descs);
  void ApplyFilters(Image &img);
};
