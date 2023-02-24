//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Clock.h"

namespace paging::strategy {
uint32_t Clock::GetReplacePage(paging::PageTable &page_table) {
  while (true) {
    uint32_t page_number = frame_clock[head_idx_];
    if (page_table.IsValid(page_number) && !page_table.IsReferenced(page_number)) {
      return page_number;
    }
    page_table.SetReference(page_number, false);
    head_idx_ = (head_idx_ + 1) % frame_clock.size();
  }
}
void Clock::AfterNewPage(PageTable &page_table, uint32_t page_number) {
  frame_clock.push_back(page_number);
  CheckPeriod(page_table);
}
void Clock::AfterReference(PageTable &page_table, uint32_t page_number) {
  CheckPeriod(page_table);
}
void Clock::AfterReplace(PageTable &page_table, uint32_t old_page_number, uint32_t new_page_number) {
  frame_clock[head_idx_] = new_page_number;
  head_idx_ = (head_idx_ + 1) % frame_clock.size();
  CheckPeriod(page_table);
}
std::string Clock::GetName() {
  return name_;
}
void Clock::CheckPeriod(PageTable &page_table) {
  if (cur_period_++ == period_) {
    cur_period_ = 0;
    for (const auto& pn : frame_clock) {
      page_table.SetReference(pn, false);
    }
  }
}
} // strategy