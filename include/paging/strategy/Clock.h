//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include "IStrategy.h"

namespace paging::strategy {


class Clock: public IStrategy {
 protected:
  void PeriodOperation(PhysicalMemory &frame, PageTable &page_table) override;
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_number) override {};
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_number) override {};
  void AfterReplace_(PhysicalMemory &frame,
                     PageTable &page_table,
                     int old_page_number,
                     int new_page_number) override;
 public:
  int GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  std::string name_ = "Clock";
  int head_idx_ = 0;
};

}

