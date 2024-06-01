#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "shared_structures.h"

struct ParserResults {
  std::string input_filename;
  std::string output_filename;
  std::vector<FilterDescription> filters;
};

class Parser {
 private:
  ParserResults _res{};
  void ParseFilters(std::vector<std::string> &prompt);
  void CheckFilters() const;
 public:
  void Parse(char **argv);
  [[nodiscard]] ParserResults GetRes() const;
};
