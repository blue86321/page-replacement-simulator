//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Clock.h"

namespace paging::strategy {
int Clock::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  while (true) {
    int page_number = frame.GetPage(head_idx_);
    if (page_table.IsValid(page_number) && !page_table.IsReferenced(page_number)) {
      return page_number;
    }
    page_table.SetReference(page_number, false);
    head_idx_ = (head_idx_ + 1) % frame.Size();
  }
}
void Clock::AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_number, int new_page_number) {
  head_idx_ = (head_idx_ + 1) % frame.Size();
}
std::string Clock::GetName() {
  return name_;
}
void Clock::PeriodOperation(PhysicalMemory &frame, PageTable &page_table) {
  for (int i = 0; i < frame.Size(); i++) {
    page_table.SetReference(frame.GetPage(i), false);
  }
}
} // strategy