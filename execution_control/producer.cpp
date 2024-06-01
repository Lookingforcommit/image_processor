#include "producer.h"

#include <vector>
#include <string>
#include <memory>

#include "exceptions.h"
#include "filters/base.h"
#include "filters/crop.h"
#include "filters/grayscale.h"
#include "filters/negative.h"
#include "filters/nostalgic.h"
#include "filters/matrix_filters/sharp.h"
#include "filters/matrix_filters/edge_detection.h"

std::unique_ptr<BaseFilter> CreateCropFilter(std::vector<std::string> &params) {
  try {
    int32_t height = std::stol(params[0]), width = std::stol(params[1]);
    std::unique_ptr<BaseFilter> ans = std::make_unique<CropFilter>(height, width);
    return ans;
  }
  catch (const std::exception &e) {
    throw InvalidFilterArgsFormatException{"-crop"};
  }
}

std::unique_ptr<BaseFilter> CreateGrayScaleFilter([[maybe_unused]] std::vector<std::string> &params) {
  std::unique_ptr<BaseFilter> ans = std::make_unique<GrayScaleFilter>();
  return ans;
}

std::unique_ptr<BaseFilter> CreateNegativeFilter([[maybe_unused]] std::vector<std::string> &params) {
  std::unique_ptr<BaseFilter> ans = std::make_unique<NegativeFilter>();
  return ans;
}

std::unique_ptr<BaseFilter> CreateNostalgicFilter([[maybe_unused]] std::vector<std::string> &params) {
  std::unique_ptr<BaseFilter> ans = std::make_unique<NostalgicFilter>();
  return ans;
}

std::unique_ptr<BaseFilter> CreateSharpFilter([[maybe_unused]] std::vector<std::string> &params) {
  std::unique_ptr<BaseFilter> ans = std::make_unique<SharpFilter>();
  return ans;
}

std::unique_ptr<BaseFilter> CreateEdgeFilter(std::vector<std::string> &params) {
  try {
    double threshold = std::stod(params[0]);
    std::unique_ptr<BaseFilter> ans = std::make_unique<EdgeFilter>(threshold);
    return ans;
  }
  catch (const std::exception &e) {
    throw InvalidFilterArgsFormatException{"-edge"};
  }
}
