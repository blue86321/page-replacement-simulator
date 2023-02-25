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
  static void GenerateInputIfNotExist(const std::string &file_name,
                                      size_t max_page,
                                      int modify_percent_,
                                      size_t line_cnt);
  static void GenerateSmallPageFrequentAccessInputIfNotExist(const std::string &file_name,
                                                             size_t max_page,
                                                             int modify_percent_,
                                                             size_t line_cnt,
                                                             int small_page_cnt);
  static void GenerateSequenceInputIfNotExist(const std::string &file_name,
                                              size_t max_page,
                                              int modify_percent_,
                                              size_t line_cnt);
};

} // util

