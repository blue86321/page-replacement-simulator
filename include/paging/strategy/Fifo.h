//
// Created by Chunwei Chang on 2/18/23.
//

#pragma once

#include <queue>
#include <iostream>

#include "IStrategy.h"

namespace paging::strategy {

class Fifo : public paging::IStrategy {
 public:
  uint32_t GetReplacePage(paging::PageTable &page_table) override;
  void AfterNewPage(paging::PageTable &page_table, uint32_t page_number) override;
  void AfterReference(paging::PageTable &page_table, uint32_t page_number) override {};
  void AfterReplace(paging::PageTable &page_table, uint32_t page_number) override;
  std::string GetName() override;
 private:
  std::string name_ = "FIFO";
  std::queue<uint32_t> queue;

};

} // paging
