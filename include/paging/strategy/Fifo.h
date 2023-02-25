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
  void AfterNewPage_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_number) override;
  void PeriodOperation(PhysicalMemory &frame, PageTable &page_table) override {};
  void AfterReference_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_number) override {};
  void AfterReplace_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int old_page_number, int new_page_number) override;
 public:
  int GetReplacePage(paging::PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  std::string name_ = "FIFO";
  std::queue<int> queue;

};

} // paging
