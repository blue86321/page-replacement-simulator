//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Aging.h"

namespace paging::strategy {
int Aging::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  auto& page_age = priority_queue_.top();
  int page_number = page_age.page_number;
  return page_number;
}
void Aging::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_number) {
  priority_queue_.emplace(page_number, 1 << 31);
}
void Aging::AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_number) {
  priority_queue_.UpdateAge(page_number);
}
void Aging::AfterReplace_(PhysicalMemory &frame,
                          PageTable &page_table,
                          int old_page_number,
                          int new_page_number) {
  priority_queue_.pop();
  AfterNewPage_(frame, page_table, new_page_number);
}
std::string Aging::GetName() {
  return name_;
}
void Aging::PeriodOperation(PhysicalMemory &frame, PageTable &page_table) {
  priority_queue_.Aging(page_table);
}

void CustomPq::Aging(PageTable& page_table) {
  for (auto& element : this->c) {
    if (page_table.IsReferenced(element.page_number)) {
      page_table.SetReference(element.page_number, false);
    } else {
      element.age = (element.age >> 1);
    }
  }
  std::make_heap(this->c.begin(), this->c.end(), Comparator());
}
void CustomPq::UpdateAge(int key) {
  for (auto& element : this->c) {
    if (element.page_number == key) {
      element.age = (element.age >> 1) | (1 << 31);
      break;
    }
  }
  std::make_heap(this->c.begin(), this->c.end(), Comparator());
}
} // paging