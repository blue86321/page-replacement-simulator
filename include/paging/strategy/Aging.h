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
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_no) override;
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_no) override;
  void AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) override;
  void PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) override;
  void Reset_() override;
 public:
  int GetReplacePage(PhysicalMemory &a, paging::PageTable &b) override;
  std::string GetName() override;
 private:
  std::unordered_map<int, unsigned int> age_map{};
  std::unordered_set<int> ref_page_cur_period{};
  std::string name_ = "Aging";
};

} // paging

