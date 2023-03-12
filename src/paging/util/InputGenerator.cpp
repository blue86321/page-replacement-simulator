//
// Created by Chunwei Chang on 2/24/23.
//

#include "paging/util/InputGenerator.h"

namespace paging::util {

void InputGenerator::GenerateInputIfNotExist(const std::string &file_name,
                                             size_t max_page,
                                             int modify_percent_,
                                             size_t line_cnt) {
  // generate page reference in uniform distribution
  struct stat buffer{};
  bool exists = stat(file_name.c_str(), &buffer) == 0;
  if (!exists) {
    std::ofstream file;
    file.open(file_name);
    file << "Page" << ' ' << "IsModify" << "\n";

    std::random_device rd;  // non-deterministic generator
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> page_dist(0, max_page - 1);
    std::vector<double> data_range{0, 0, 1, 1};
    double m_pct = modify_percent_ / 100.0;
    std::vector<double> weight{1 - m_pct, 0, m_pct};
    std::piecewise_constant_distribution<> modify_dist(data_range.begin(), data_range.end(), weight.begin());
    for (int i = 0; i < line_cnt; i++) {
      file << page_dist(generator) << ' ' << modify_dist(generator) << "\n";
    }
    file.close();
  }
}

void InputGenerator::GenerateSmallPageFrequentAccessInputIfNotExist(const std::string &file_name,
                                                                    size_t max_page,
                                                                    int modify_percent_,
                                                                    size_t line_cnt,
                                                                    int small_block_cnt,
                                                                    int page_per_block,
                                                                    int interval) {
  // frequent access pages
  std::vector<std::vector<int>> blocks(small_block_cnt);
  for (int i = 0; i < small_block_cnt; i++) {
    std::vector<int> pages = std::vector<int>(page_per_block);
    for (int j = 0; j < page_per_block; j++) {
      pages[j] = j;
    }
    blocks[i] = pages;
  }
  // generate input
  struct stat buffer{};
  bool exists = stat(file_name.c_str(), &buffer) == 0;
  if (!exists) {
    std::ofstream file;
    file.open(file_name);
    file << "Page" << ' ' << "IsModify" << "\n";

    std::random_device rd;  // non-deterministic generator
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> page_dist(page_per_block, (int) max_page - 1);
    std::uniform_int_distribution<> block_dist(0, blocks.size() - 1);
    std::vector<double> data_range{0, 0, 1, 1};
    double m_pct = modify_percent_ / 100.0;
    std::vector<double> weight{1 - m_pct, 0, m_pct};
    std::piecewise_constant_distribution<> modify_dist(data_range.begin(), data_range.end(), weight.begin());
    int i = 0;
    int other_page_i = 0;
    while (i < line_cnt) {
      // insert `pages` every `interval`
      if (other_page_i >= interval) {
        other_page_i = 0;
        // pick 1 block randomly
        int blockIdx = block_dist(generator);
        for (const auto &page : blocks[blockIdx]) {
          if (i < line_cnt) {
            file << page << ' ' << 0 << "\n";
            i++;
          }
        }
      } else {
        file << page_dist(generator) << ' ' << modify_dist(generator) << "\n";
        other_page_i++;
        i++;
      }
    }
    file.close();
  }
}
void InputGenerator::GenerateSequenceInputIfNotExist(const std::string &file_name,
                                                     size_t max_page,
                                                     int modify_percent_,
                                                     size_t line_cnt) {
  struct stat buffer{};
  bool exists = stat(file_name.c_str(), &buffer) == 0;
  if (!exists) {
    std::ofstream file;
    file.open(file_name);
    file << "Page" << ' ' << "IsModify" << "\n";

    std::random_device rd;  // non-deterministic generator
    std::mt19937 generator(rd());
    std::vector<double> data_range{0, 0, 1, 1};
    double m_pct = modify_percent_ / 100.0;
    std::vector<double> weight{1 - m_pct, 0, m_pct};
    std::piecewise_constant_distribution<> modify_dist(data_range.begin(), data_range.end(), weight.begin());
    for (int i = 0; i < line_cnt; i++) {
      file << i % max_page << ' ' << modify_dist(generator) << "\n";
    }
    file.close();
  }
}
} // util