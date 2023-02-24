//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include "IStrategy.h"

namespace paging::strategy {

class Nru: public IStrategy {
 public:
  explicit Nru(uint32_t period = 5): period_(period) {};
  uint32_t GetReplacePage(PageTable &page_table) override;
  void AfterNewPage(PageTable &page_table, uint32_t page_number) override;
  void AfterReference(PageTable &page_table, uint32_t page_number) override;
  void AfterReplace(PageTable &page_table, uint32_t old_page_number, uint32_t new_page_number) override;
  std::string GetName() override;
 private:
  void CheckPeriod(PageTable &page_table);
 private:
  std::string name_ = "NRU";
  // element is page number
  std::vector<uint32_t> frame_pn;
  uint32_t period_;
  uint32_t cur_period_ = 0;
};

}

