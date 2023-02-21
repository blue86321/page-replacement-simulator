//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Clock.h"

namespace paging::strategy {
uint32_t Clock::GetReplacePage(paging::PageTable &page_table) {
  while (true) {
    if (page_table.IsValid(head_idx_) && !page_table.IsReferenced(head_idx_)) {
      return head_idx_;
    }
    page_table.SetReference(head_idx_, false);
    head_idx_ = (head_idx_ + 1) % PAGE_TABLE_SIZE;
  }
}
std::string Clock::GetName() {
  return name_;
}
} // strategy