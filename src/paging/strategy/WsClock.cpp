//
// Created by Chunwei Chang on 3/12/23.
//

#include "paging/strategy/WsClock.h"

namespace paging::strategy {

int WsClock::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  // search for a not referenced frame
  // in searching, set reference bit to 0 if it is referenced
  int checked_page_cnt = 0;
  int oldest_page_no_ws = -1;
  while (checked_page_cnt++ < frame.Size()) {
    int page_no = frame.GetPage(head_idx_);
    if (page_table.IsValid(page_no)) {
      // if referenced, reset reference and update last visit time
      if (page_table.IsReferenced(page_no) && !page_table.IsModified(page_no)) {
        last_visit_time_[page_no] = cur_time_;
        page_table.SetReference(page_no, false);
      } else {
        // not referenced, check `last visit time` and `working set window`
        // note: we ignore modified data since it will schedule to write, which is not easy to implement here
        uint32_t age = cur_time_ - last_visit_time_[page_no];
        if (age > working_set_window_) {
          return page_no;
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
  return oldest_page_no_ws == -1 ? frame.GetPage(head_idx_) : oldest_page_no_ws;
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