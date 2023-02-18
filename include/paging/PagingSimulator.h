//
// Created by Chunwei Chang on 2/16/23.
//

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>
#include <map>
#include "paging/strategy/IStrategy.h"
#include "paging/PageTable.h"
#include "paging/Common.h"
#include "paging/PhysicalMemory.h"

namespace paging {

struct Indicator {
  uint32_t line;
  uint32_t page_fault;
};

class PagingSimulator {
 public:
  void SetStrategy(std::unique_ptr<paging::IStrategy> &&strategy);
  void Run();
  void ShowStats();
 private:
  // generate input file
  void GenerateInputIfNotExist();
 private:
  // physical frames, each frame stores the page number
  paging::PhysicalMemory frame_{};
  paging::PageTable page_table_{};
  // stats: strategy_name -> indicators
  std::unordered_map<std::string, std::vector<Indicator>> stats;
  uint32_t cur_page_fault_{0};
  std::unique_ptr<paging::IStrategy> strategy_;
  void AccessMemory(uint32_t page_number);
  void Replace(uint32_t from_page_number, uint32_t to_page_number);
  void SetupNewPage(uint32_t page_number, uint32_t frame_no);
};

}
