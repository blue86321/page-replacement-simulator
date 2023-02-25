//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Clock.h"

namespace paging::strategy {
uint32_t Clock::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  while (true) {
    uint32_t page_number = frame_clock[head_idx_];
    if (page_table.IsValid(page_number) && !page_table.IsReferenced(page_number)) {
      return page_number;
    }
    page_table.SetReference(page_number, false);
    head_idx_ = (head_idx_ + 1) % frame_clock.size();
  }
}
void Clock::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, uint32_t page_number) {
  frame_clock.push_back(page_number);
}
void Clock::AfterReplace_(PhysicalMemory &frame,
                          PageTable &page_table,
                          uint32_t old_page_number,
                          uint32_t new_page_number) {
  frame_clock[head_idx_] = new_page_number;
  head_idx_ = (head_idx_ + 1) % frame_clock.size();
}
std::string Clock::GetName() {
  return name_;
}
void Clock::PeriodOperation(PhysicalMemory &frame, PageTable &page_table) {
  for (int i = 0; i < frame.Size(); i ++) {
    page_table.SetReference(frame.GetPage(i), false);
  }
}
} // strategy