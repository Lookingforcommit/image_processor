#include "exceptions.h"

#include <string>
#include <format>

#include "execution_control/shared_structures.h"

InvalidFilterException::InvalidFilterException(const std::string &filter) {
  this->_msg = std::vformat(FORMAT, std::make_format_args(filter));
  for (auto &[valid_filter, filter_info] : FILTERS_INFO) {
    this->_msg.append(valid_filter);
    this->_msg.push_back('\n');
  }
}

IncorrectFilterArgsCntException::IncorrectFilterArgsCntException(const std::string &filter) {
  int correct_cnt = FILTERS_INFO.find(filter)->second.args_cnt;
  this->_msg = std::vformat(FORMAT, std::make_format_args(filter, correct_cnt));
}

InvalidFilterArgsFormatException::InvalidFilterArgsFormatException(const std::string &filter) {
  this->_msg = std::vformat(FORMAT, std::make_format_args(filter));
}

FileOpenException::FileOpenException(const std::string &filename) {
  this->_msg = std::vformat(FORMAT, std::make_format_args(filename));
}
InvalidImageFormatException::InvalidImageFormatException(const std::string &filename) {
  this->_msg = std::vformat(FORMAT, std::make_format_args(filename));
}
