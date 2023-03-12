//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Clock.h"

namespace paging::strategy {

int Clock::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  // search for a not referenced frame
  // in searching, set reference bit to 0 if it is referenced
  while (true) {
    int page_no = frame.GetPage(head_idx_);
    if (page_table.IsValid(page_no) && !page_table.IsReferenced(page_no)) {
      return page_no;
    }
    page_table.SetReference(page_no, false);
    head_idx_ = (head_idx_ + 1) % frame.Size();
  }
}
void Clock::AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) {
  head_idx_ = (head_idx_ + 1) % frame.Size();
}
std::string Clock::GetName() {
  return name_;
}
} // strategy