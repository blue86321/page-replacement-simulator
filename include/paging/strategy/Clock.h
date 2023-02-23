//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include "IStrategy.h"

namespace paging::strategy {


class Clock: public paging::IStrategy {
 public:
  uint32_t GetReplacePage(paging::PageTable &page_table) override;
  void AfterNewPage(paging::PageTable &page_table, uint32_t page_number) override;
  void AfterReference(paging::PageTable &page_table, uint32_t page_number) override;
  void AfterReplace(paging::PageTable &page_table, uint32_t old_page_number, uint32_t new_page_number) override;
  std::string GetName() override;
 private:
  std::string name_ = "Clock";
  uint32_t head_idx_ = 0;
  // element is page number
  std::vector<uint32_t> frame_clock;
};

}

