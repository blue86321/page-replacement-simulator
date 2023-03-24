//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Clock.h"
#include <iomanip>

namespace paging::strategy {

int Clock::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  if (verbose_) {
    std::cout << "Before: \n";
    std::cout << std::setw(7) << "Page" << std::setw(7) << "Ref\n";
    for (int i = 0; i < frame.Size(); i++ ) {
      std::cout << std::setw(7) << frame.GetPage(i) << std::setw(7) << page_table.IsReferenced(frame.GetPage(i));
      if (head_idx_ == i) {
        std::cout << " --- head";
      }
      std::cout << "\n";
    }
  }
  // search for a not referenced frame
  // in searching, set reference bit to 0 if it is referenced
  int victim;
  while (true) {
    int page_no = frame.GetPage(head_idx_);
    if (page_table.IsValid(page_no) && !page_table.IsReferenced(page_no)) {
      victim = page_no;
      break;
    }
    page_table.SetReference(page_no, false);
    head_idx_ = (head_idx_ + 1) % frame.Size();
  }
  if (verbose_) {
    std::cout << "After: \n";
    std::cout << std::setw(7) << "Page" << std::setw(7) << "Ref\n";
    for (auto& page_no : frame.GetFrames()) {
      std::cout << std::setw(7) << page_no << std::setw(7) << page_table.IsReferenced(page_no);
      if (page_no == victim) {
        std::cout << " --- victim";
      }
      std::cout << "\n";
    }
  }
  return victim;
}
void Clock::AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) {
  head_idx_ = (head_idx_ + 1) % frame.Size();
}
std::string Clock::GetName() {
  return name_;
}
void Clock::Reset_() {
  head_idx_ = 0;
}
void Clock::PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) {
  // reset all frames' reference bit to 0
  for (int i = 0; i < frame.Size(); i++) {
    page_table.SetReference(frame.GetPage(i), false);
  }
}
} // strategy