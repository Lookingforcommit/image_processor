#pragma once

#include <exception>
#include <string>
#include <format>

#include "execution_control/shared_structures.h"

class CustomException : public std::exception {};

class InvalidCommandFormatException : public CustomException {
 private:
  const std::string MSG{"Invalid command format, the correct format is:\n" + COMMAND_FORMAT};
 public:
  [[nodiscard]] const char *what() const
  noexcept override{return MSG.c_str();};
};

class InvalidFilterException : public CustomException {
 private:
  const std::string_view FORMAT{"Invalid filter '{}', list of valid filters:\n"};
  std::string _msg;
 public:
  explicit InvalidFilterException(const std::string &filter);
  [[nodiscard]] const char *what() const
  noexcept override{return this->_msg.c_str();};
};

class IncorrectFilterArgsCntException : public CustomException {
 private:
  const std::string_view FORMAT{"Incorrect filter arguments count for filter '{}', the correct count is {}"};
  std::string _msg;
 public:
  explicit IncorrectFilterArgsCntException(const std::string &filter);
  [[nodiscard]] const char *what() const
  noexcept override{return this->_msg.c_str();};
};

class InvalidFilterArgsFormatException : public CustomException {
 private:
  const std::string FORMAT{"Incorrect filter arguments format for filter '{}'"};
  std::string _msg;
 public:
  explicit InvalidFilterArgsFormatException(const std::string &filter);
  [[nodiscard]] const char *what() const
  noexcept override{return this->_msg.c_str();};
};

class FileOpenException : public CustomException {
 private:
  const std::string FORMAT{"Unable to open file '{}'"};
  std::string _msg;
 public:
  explicit FileOpenException(const std::string &filename);
  [[nodiscard]] const char *what() const
  noexcept override{return this->_msg.c_str();};
};

class InvalidImageFormatException : public CustomException {
 private:
  const std::string FORMAT{"Invalid input image format of '{}'"};
  std::string _msg;
 public:
  explicit InvalidImageFormatException(const std::string &filename);
  [[nodiscard]] const char *what() const
  noexcept override{return this->_msg.c_str();};
};
