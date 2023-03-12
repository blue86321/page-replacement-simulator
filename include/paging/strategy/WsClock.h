//
// Created by Chunwei Chang on 3/12/23.
//

#pragma once

#include <string>
#include <unordered_map>
#include "IStrategy.h"

namespace paging::strategy {

class WsClock : public IStrategy {
 protected:
  void PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) override;
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_no) override;
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_no) override;
  void AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) override;
  void Reset_() override;
 public:
  int GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  std::string name_ = "WsClock";
  std::unordered_map<int, uint32_t> last_visit_time_;
  int head_idx_;
  uint32_t working_set_window_ = 30;
  uint32_t cur_time_ = 0;
};

}

