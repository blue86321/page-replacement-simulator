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
  void AfterNewPage_(paging::PhysicalMemory &frame, paging::PageTable &page_table, uint32_t page_number) override;
  void PeriodOperation(PhysicalMemory &frame, PageTable &page_table) override {};
  void AfterReference_(paging::PhysicalMemory &frame, paging::PageTable &page_table, uint32_t page_number) override {};
  void AfterReplace_(paging::PhysicalMemory &frame, paging::PageTable &page_table, uint32_t old_page_number, uint32_t new_page_number) override;
 public:
  uint32_t GetReplacePage(paging::PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  std::string name_ = "FIFO";
  std::queue<uint32_t> queue;

};

} // paging
