#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include "shared_structures.h"

struct ParserResults {
  std::string input_filename;
  std::string output_filename;
  std::vector<FilterParams> filters;
};

class Parser {
 private:
  ParserResults _res{};
  void PrintHelp();
  void ParseFilters(std::vector<std::string> &prompt);
  void CheckFilters() const;
 public:
  bool Parse(char **argv);
  [[nodiscard]] ParserResults GetRes() const;
};
