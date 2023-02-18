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
  void PostNewPage(paging::PageTable &page_table, uint32_t page_number) override;
  void PostReference(paging::PageTable &page_table, uint32_t page_number) override {};
  void PostReplace(paging::PageTable &page_table, uint32_t page_number) override;
 private:
  std::queue<uint32_t> queue;

};

} // paging
