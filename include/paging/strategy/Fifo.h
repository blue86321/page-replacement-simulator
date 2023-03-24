//
// Created by Chunwei Chang on 2/18/23.
//

#pragma once

#include <queue>
#include <iostream>
#include "IStrategy.h"
#include "paging/PhysicalMemory.h"

namespace paging::strategy {

class Fifo : public IStrategy {
 protected:
  void Reset_() override;
  void AfterNewPage_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_no) override;
  void PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) override {};
  void AfterReference_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_no) override {};
  void AfterReplace_(paging::PhysicalMemory &frame,
                     paging::PageTable &page_table,
                     int old_page_no,
                     int new_page_no) override;
 public:
  int GetReplacePage(paging::PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  std::string name_ = "FIFO";
  std::queue<int> queue_;
  std::vector<int> queue_verbose_;
};

} // paging
