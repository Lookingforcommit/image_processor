#include "processor.h"

#include <vector>

#include "image.h"
#include "producer.h"

void Processor::CreateFilters(std::vector<FilterParams> &filter_descs) {
  for (FilterParams &desc : filter_descs) {
    FilterProducerFunc producer_func = FILTER_PRODUCER_FUNC_MAP.find(desc.filter_name)->second;
    this->_filters.push_back(producer_func(desc.params));
  }
}

void Processor::ApplyFilters(Image &img) {
  for (auto &filter : this->_filters) {
    filter->Apply(img);
  }
}
