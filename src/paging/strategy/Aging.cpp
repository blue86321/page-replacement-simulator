//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Aging.h"

namespace paging::strategy {
uint32_t Aging::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  auto& page_age = priority_queue_.top();
  uint32_t page_number = page_age.page_number;
  return page_number;
}
void Aging::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, uint32_t page_number) {
  priority_queue_.emplace(page_number, 0);
  priority_queue_.UpdateAge(page_number);
}
void Aging::AfterReference_(PhysicalMemory &frame, PageTable &page_table, uint32_t page_number) {
  priority_queue_.UpdateAge(page_number);
}
void Aging::AfterReplace_(PhysicalMemory &frame,
                          PageTable &page_table,
                          uint32_t old_page_number,
                          uint32_t new_page_number) {
  priority_queue_.pop();
  AfterNewPage_(frame, page_table, new_page_number);
}
std::string Aging::GetName() {
  return name_;
}
void Aging::PeriodOperation(PhysicalMemory &frame, PageTable &page_table) {
  priority_queue_.Aging();
}

void CustomPq::Aging() {
  for (auto& page_page : this->c) {
    page_page.age = (page_page.age >> 1);
  }
  std::make_heap(this->c.begin(), this->c.end(), Comparator());
}
void CustomPq::UpdateAge(uint32_t key) {
  for (auto& page_page : this->c) {
    if (page_page.page_number == key) {
      page_page.age = (page_page.age >> 1) | (1 << 31);
      break;
    }
  }
  std::make_heap(this->c.begin(), this->c.end(), Comparator());
}
} // paging