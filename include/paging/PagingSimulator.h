//
// Created by Chunwei Chang on 2/16/23.
//

#pragma once

#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>
#include <map>
#include "Strategy.h"
#include "paging/PageTable.h"
#include "paging/Common.h"
#include "paging/PhysicalMemory.h"

namespace paging {

class PagingSimulator {
 public:
  void SetStrategy(std::unique_ptr<paging::Strategy> &&strategy);
  void Run();
 private:
  // generate input file
  void GenerateInputIfNotExist();
 private:
  // physical frames, each frame stores the page number
  paging::PhysicalMemory frame_{};
  paging::PageTable page_table_{};
  int page_fault_{0};
  std::unique_ptr<paging::Strategy> strategy_;
  void AccessMemory(uint32_t page_number);
  void Replace(uint32_t from_page_number, uint32_t to_page_number);
  void SetupNewPage(uint32_t page_number, uint32_t frame_no);
};

}
