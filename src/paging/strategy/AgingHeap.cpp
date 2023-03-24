//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/AgingHeap.h"
#include <iomanip>

namespace paging::strategy {
int AgingHeap::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  // min age
  auto &page_age = priority_queue_.top();
  int page_no = page_age.page_no;
  if (verbose_) {
    priority_queue_.VerboseGetReplacePage_(frame, page_table, page_no);
  }
  return page_no;
}
void AgingHeap::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_no) {
  priority_queue_.emplace(page_no, 1 << 31);
}
void AgingHeap::AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_no) {
  // insert 1 to the highest bit in current period
  if (ref_page_cur_period_.find(page_no) == ref_page_cur_period_.end()) {
    ref_page_cur_period_.insert(page_no);
    priority_queue_.UpdateAge(page_no);
  }
}
void AgingHeap::AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) {
  priority_queue_.pop();
  AfterNewPage_(frame, page_table, new_page_no);
}

void AgingHeap::PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) {
  // reset all reference bit in the frame
  // insert 1 to the highest bit (aging) if the frame is not referenced in current period
  priority_queue_.Aging(page_table);
  ref_page_cur_period_.clear();
}
void CustomPq::Aging(PageTable &page_table) {
  for (auto &element : this->c) {
    if (page_table.IsReferenced(element.page_no)) {
      page_table.SetReference(element.page_no, false);
    } else {
      element.age = (element.age >> 1);
    }
  }
  std::make_heap(this->c.begin(), this->c.end(), Comparator());
}
void CustomPq::UpdateAge(int key) {
  for (auto &element : this->c) {
    if (element.page_no == key) {
      element.age = (element.age >> 1) | (1 << 31);
      break;
    }
  }
  std::make_heap(this->c.begin(), this->c.end(), Comparator());
}
void CustomPq::VerboseGetReplacePage_(PhysicalMemory &frame, PageTable &page_table, int victim) {
  std::cout << std::setw(7) << "Page" << std::setw(40) << "Age" << "\n";
  for (auto &[page_no, age] : this->c) {
    std::cout << std::setw(7) << page_no << std::setw(40) << age;
    if (page_no == victim) {
      std::cout << " --- victim";
    }
    std::cout << "\n";
  }
}
void AgingHeap::Reset_() {
  age_map_.clear();
  ref_page_cur_period_.clear();
}

std::string AgingHeap::GetName() {
  return name_;
}
} // paging