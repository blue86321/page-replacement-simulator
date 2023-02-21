//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Aging.h"

namespace paging {
uint32_t strategy::Aging::GetReplacePage(PageTable &page_table) {
  auto& page_age = priority_queue_.top();
  uint32_t page_number = page_age.page_number;
  priority_queue_.pop();
  return page_number;
}
void strategy::Aging::AfterNewPage(PageTable &page_table, uint32_t page_number) {
  auto* pa = new PageAge(page_number, 1);
  priority_queue_.push(*pa);
}
void strategy::Aging::AfterReference(PageTable &page_table, uint32_t page_number) {
  priority_queue_.updateAge(page_number);
}
void strategy::Aging::AfterReplace(PageTable &page_table, uint32_t new_page_number) {
  AfterNewPage(page_table, new_page_number);
}
std::string strategy::Aging::GetName() {
  return name_;
}

void strategy::CustomPq::updateAge(uint32_t key) {
  for (auto page_page : this->c) {
    if (page_page.page_number == key) {
      page_page.age = (page_page.age >> 1) | (1 << 32);
    } else {
      page_page.age = (page_page.age >> 1);
    }
  }
}
} // paging