#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <map>

struct FilterParams {
  std::string filter_name;
  std::vector<std::string> params;
};

struct FilterInfo {
  std::string filter_format;
  std::string info_text;
  int args_cnt;
};

const std::map<std::string, FilterInfo> FILTERS_INFO{
    {"-crop", {"-crop {width} {height}", "Crop the image leaving the top-left part of it",
               2}},
    {"-gs", {"-gs", "Convert the image into shades of gray", 0}},
    {"-neg", {"-neg", "Convert the image into its negative", 0}},
    {"-sharp", {"-sharp", "Increase sharpness of the image", 0}},
    {"-edge", {"-edge {threshold}", "Highlight the borders of the image. Pixels with values "
                                    "higher than the {threshold} will be colored white, others - black", 1}},
    {"-nostalg", {"-nostalg", "Apply a nostalgic, yellowish filter to the image", 0}}
};

const int MIN_SPACING = 4;

const std::string COMMAND_FORMAT = "image_processor {input_filename} {output_filename} [-{filter_1} "
                                   "[filter_param_1][filter_param_2] ...] [-{filter_2} [filter_param_1] "
                                   "[filter_param_2] ...]";

const std::string WELCOME_MESSAGE = "This is a CLI app for applying various filters to BMP images. Usage format:\n" +
    COMMAND_FORMAT + "\nList of supported filters:";
