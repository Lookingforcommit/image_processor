#include "parser.h"

#include <vector>
#include <string>

#include "shared_structures.h"
#include "exceptions.h"

void Parser::Parse(char **argv) {
  std::vector<std::string> prompt;
  while (*argv) {
    prompt.emplace_back(*argv);
    argv++;
  }
  this->_res.input_filename = prompt[1];
  this->_res.output_filename = prompt[2];
  ParseFilters(prompt);
  CheckFilters();
}

void Parser::ParseFilters(std::vector<std::string> &prompt) {
  int idx = 3;
  FilterDescription filter;
  while (idx < prompt.size()) {
    filter.filter_name = prompt[idx++];
    filter.params = {};
    std::string param;
    while (idx < prompt.size()) {
      param = prompt[idx];
      if (param[0] == '-') {
        break;
      }
      filter.params.push_back(prompt[idx]);
      ++idx;
    }
    this->_res.filters.push_back(filter);
  }
}

void Parser::CheckFilters() const {
  for (const auto &filter : this->_res.filters) {
    if (FILTER_ARGS_CNT.find(filter.filter_name) == FILTER_ARGS_CNT.end()) {
      throw InvalidFilterException{filter.filter_name};
    }
    if (FILTER_ARGS_CNT.find(filter.filter_name)->second != filter.params.size()) {
      throw IncorrectFilterArgsCntException{filter.filter_name};
    }
  }
}

ParserResults Parser::GetRes() const {
  return this->_res;
}

