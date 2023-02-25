//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "IStrategy.h"

namespace paging::strategy {

class Aging : public IStrategy {
 protected:
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_number) override;
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_number) override;
  void AfterReplace_(PhysicalMemory &frame,
                     PageTable &page_table,
                     int old_page_number,
                     int new_page_number) override;
  void PeriodOperation(PhysicalMemory &frame, PageTable &page_table) override;
 public:
  int GetReplacePage(PhysicalMemory &a, paging::PageTable &b) override;
  std::string GetName() override;
 private:
  std::unordered_map<int, unsigned int> age_map{};
  std::string name_ = "Aging";
  std::unordered_set<int> ref_page_this_period{};
};

} // paging

