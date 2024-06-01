#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

const std::unordered_set<std::string> VALID_FILTERS{
    "-crop",
    "-gs",
    "-neg",
    "-sharp",
    "-edge",
    "-nostalg"
};

const std::unordered_map<std::string, int> FILTER_ARGS_CNT{
    {"-crop", 2},
    {"-gs", 0},
    {"-neg", 0},
    {"-sharp", 0},
    {"-edge", 1},
    {"-nostalg", 0}
};

struct FilterDescription {
  std::string filter_name;
  std::vector<std::string> params;
};
