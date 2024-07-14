#include <iostream>

#include "bmp.h"
#include "execution_control/parser.h"
#include "execution_control/processor.h"
#include "exceptions.h"

int main(int argc, char **argv) {
  Parser parser;
  BMPReader reader;
  BMPWriter writer;
  Image input_img;
  Processor processor;
  try {
    bool convert_image = parser.Parse(argv);
    if (convert_image) {
      ParserResults parsing_res = parser.GetRes();
      reader.ReadFile(parsing_res.input_filename, input_img);
      BMPFileHeader file_header = reader.GetFileHeader();
      BMPInfoHeader info_header = reader.GetInfoHeader();
      processor.CreateFilters(parsing_res.filters);
      processor.ApplyFilters(input_img);
      writer.WriteFile(parsing_res.output_filename, input_img, file_header, info_header);
    }
  }
  catch (const CustomException &e) {
    std::cout << e.what();
  }
  catch (const std::exception &e) {
    std::cout << "Uncaught exception\n" << e.what();
  }
  return 0;
}
