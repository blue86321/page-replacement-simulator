//
// Created by Chunwei Chang on 3/12/23.
//

#include "paging/strategy/WsClock.h"
#include <iomanip>

namespace paging::strategy {

int WsClock::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  if (verbose_) {
    std::cout << "Before: \n";
    std::cout << std::setw(7) << "Page" << std::setw(7) << "Ref" << std::setw(7) << "Age" << std::setw(15) << "WorkingSet" << std::setw(15) << "InWorkingSet" << "\n";
    for (int i = 0; i < frame.Size(); i++ ) {
      int page_no = frame.GetPage(i);
      std::cout
        << std::setw(7) << page_no
        << std::setw(7) << page_table.IsReferenced(page_no)
        << std::setw(7) << (cur_time_ - last_visit_time_[page_no])
        << std::setw(15) << (working_set_window_)
        << std::setw(15) << ((cur_time_ - last_visit_time_[page_no]) <= working_set_window_);
      if (i == head_idx_) {
        std::cout << " --- head";
      }
      std::cout << "\n";
    }
  }
  // search for a not referenced frame
  // in searching, set reference bit to 0 if it is referenced
  int victim = -1;
  int checked_page_cnt = 0;
  int oldest_page_no_ws = -1;
  while (checked_page_cnt++ < frame.Size()) {
    int page_no = frame.GetPage(head_idx_);
    if (page_table.IsValid(page_no)) {
      // if referenced, reset reference
      if (page_table.IsReferenced(page_no)) {
        page_table.SetReference(page_no, false);
      } else {
        // not referenced, check `last visit time` and `working set window`
        // note: we ignore modified data since it will schedule to write, which is not easy to implement here
        uint32_t age = cur_time_ - last_visit_time_[page_no];
        if (age > working_set_window_) {
          victim = page_no;
          break;
        } else {
          // still in working set, calc oldest as backup
          if (oldest_page_no_ws == -1 || last_visit_time_[page_no] < last_visit_time_[oldest_page_no_ws]) {
            oldest_page_no_ws = page_no;
          }
        }
      }
    }
    head_idx_ = (head_idx_ + 1) % frame.Size();
  }
  // if every page is referenced, output the first one. otherwise, output the oldest page
  if (victim == -1) {
    victim = oldest_page_no_ws == -1 ? frame.GetPage(head_idx_) : oldest_page_no_ws;
  }
  if (verbose_) {
    std::cout << "After: \n";
    std::cout << std::setw(7) << "Page" << std::setw(7) << "Ref" << std::setw(7) << "Age" << std::setw(15) << "WorkingSet" << std::setw(15) << "InWorkingSet" << "\n";
    for (auto& page_no : frame.GetFrames()) {
      std::cout
        << std::setw(7) << page_no
        << std::setw(7) << page_table.IsReferenced(page_no)
        << std::setw(7) << (cur_time_ - last_visit_time_[page_no])
        << std::setw(15) << (working_set_window_)
        << std::setw(15) << ((cur_time_ - last_visit_time_[page_no]) <= working_set_window_);
      if (victim == page_no) {
        std::cout << " --- victim (oldest one if all pages are in working set)";
      }
      std::cout << "\n";
    }
  }
  return victim;
}

void WsClock::AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) {
  last_visit_time_.erase(old_page_no);
  last_visit_time_[new_page_no] = ++cur_time_;
  head_idx_ = (head_idx_ + 1) % frame.Size();
}

std::string WsClock::GetName() {
  return name_;
}

void WsClock::PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) {
  // reset all frames' reference bit to 0
  for (int i = 0; i < frame.Size(); i++) {
    page_table.SetReference(frame.GetPage(i), false);
  }
}

void WsClock::Reset_() {
  cur_time_ = 0;
  head_idx_ = 0;
  std::unordered_map<int, uint32_t>().swap(last_visit_time_);
}

void WsClock::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_no) {
  last_visit_time_[page_no] = ++cur_time_;
}

void WsClock::AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_no) {
  last_visit_time_[page_no] = ++cur_time_;
}
} // strategy