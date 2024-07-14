#include "parser.h"

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

#include "shared_structures.h"
#include "exceptions.h"

bool Parser::Parse(char **argv) {
  std::vector<std::string> prompt;
  while (*argv) {
    prompt.emplace_back(*argv);
    argv++;
  }
  if (prompt.size() == 1) {
    PrintHelp();
    return false;
  } else if (prompt.size() <= 3) {
    throw InvalidCommandFormatException{};
  }
  this->_res.input_filename = prompt[1];
  this->_res.output_filename = prompt[2];
  ParseFilters(prompt);
  CheckFilters();
  return true;
}

void Parser::PrintHelp() {
  int spacing = 0;
  for (const auto &[filter, filter_info] : FILTERS_INFO) {
    spacing = std::max(spacing, (int) filter_info.filter_format.size());
  }
  spacing += MIN_SPACING;
  std::cout << WELCOME_MESSAGE << '\n';
  for (const auto &[filter, filter_info] : FILTERS_INFO) {
    std::cout << std::left << std::setw(spacing) << filter_info.filter_format << filter_info.info_text << '\n';
  }
}

void Parser::ParseFilters(std::vector<std::string> &prompt) {
  int idx = 3;
  FilterParams filter;
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
    if (FILTERS_INFO.find(filter.filter_name) == FILTERS_INFO.end()) {
      throw InvalidFilterException{filter.filter_name};
    }
    FilterInfo filter_info = FILTERS_INFO.find(filter.filter_name)->second;
    int correct_cnt = FILTERS_INFO.find(filter.filter_name)->second.args_cnt;
    if (correct_cnt != filter.params.size()) {
      throw IncorrectFilterArgsCntException{filter.filter_name};
    }
  }
}

ParserResults Parser::GetRes() const {
  return this->_res;
}

