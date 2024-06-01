#pragma once

#include <vector>
#include <string>
#include <memory>
#include <functional>

#include "filters/base.h"

typedef std::function<std::unique_ptr<BaseFilter>(std::vector < std::string > &)> FilterProducerFunc;
std::unique_ptr<BaseFilter> CreateCropFilter(std::vector<std::string> &params);
std::unique_ptr<BaseFilter> CreateGrayScaleFilter([[maybe_unused]] std::vector<std::string> &params);
std::unique_ptr<BaseFilter> CreateNegativeFilter([[maybe_unused]] std::vector<std::string> &params);
std::unique_ptr<BaseFilter> CreateSharpFilter([[maybe_unused]] std::vector<std::string> &params);
std::unique_ptr<BaseFilter> CreateEdgeFilter(std::vector<std::string> &params);
std::unique_ptr<BaseFilter> CreateNostalgicFilter([[maybe_unused]] std::vector<std::string> &params);
