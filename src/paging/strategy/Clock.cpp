//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Clock.h"

namespace paging::strategy {
uint32_t Clock::GetReplacePage(paging::PageTable &page_table) {
  while (true) {
    uint32_t page_number = frame_clock[head_idx_];
    if (page_table.IsValid(page_number) && !page_table.IsReferenced(page_number)) {
      head_idx_ = (head_idx_ + 1) % frame_clock.size();
      return page_number;
    }
    page_table.SetReference(page_number, false);
    head_idx_ = (head_idx_ + 1) % frame_clock.size();
  }
}
void Clock::AfterNewPage(PageTable &page_table, uint32_t page_number) {
  frame_clock.push_back(page_number);
  AfterReference(page_table, page_number);
}
void Clock::AfterReference(PageTable &page_table, uint32_t page_number) {
  for (auto pn : frame_clock) {
    if (pn != page_number) {
      page_table.SetReference(pn, false);
    }
  }
}
void Clock::AfterReplace(PageTable &page_table, uint32_t new_page_number) {
  frame_clock[(head_idx_ + frame_clock.size() - 1) % frame_clock.size()] = new_page_number;
}
std::string Clock::GetName() {
  return name_;
}
} // strategy