//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include "IStrategy.h"

namespace paging::strategy {

class Nru: public IStrategy {
 public:
  uint32_t GetReplacePage(PageTable &page_table) override;
  void AfterNewPage(PageTable &page_table, uint32_t page_number) override;
  void AfterReference(PageTable &page_table, uint32_t page_number) override;
  void AfterReplace(PageTable &page_table, uint32_t old_page_number, uint32_t new_page_number) override;
  std::string GetName() override;
 private:
  std::string name_ = "NRU";
  // element is page number
  std::vector<uint32_t> frame_pn;
};

}

