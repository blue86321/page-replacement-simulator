//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include "IStrategy.h"

namespace paging::strategy {

class Nru: public IStrategy {
 protected:
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, uint32_t page_number) override;
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, uint32_t page_number) override {};
  void AfterReplace_(PhysicalMemory &frame,
                     PageTable &page_table,
                     uint32_t old_page_number,
                     uint32_t new_page_number) override;
  void PeriodOperation(PhysicalMemory &frame, PageTable &page_table) override;
 public:
  uint32_t GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  std::string name_ = "NRU";
  // element is page number
  std::vector<uint32_t> frame_pn;
};

}

