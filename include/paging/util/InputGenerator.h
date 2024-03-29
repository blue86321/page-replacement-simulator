//
// Created by Chunwei Chang on 2/24/23.
//

#pragma once
#include <iostream>
#include <chrono>
#include <fstream>
#include <random>
#include <sys/stat.h>
#include <string>

namespace paging::util {

class InputGenerator {
 public:
  static void GenerateUniformDistInputIfNotExist(const std::string &file_name,
                                                 size_t max_page,
                                                 int modify_percent_,
                                                 size_t line_cnt);
  static void GenerateHotPageAccessInputIfNotExist(const std::string &file_name,
                                                   size_t max_page,
                                                   int modify_percent_,
                                                   size_t line_cnt,
                                                   int small_block_cnt,
                                                   int page_per_block,
                                                   int interval);
  static void GenerateSequenceInputIfNotExist(const std::string &file_name,
                                              size_t max_page,
                                              int modify_percent_,
                                              size_t line_cnt);
};

} // util

