//
// Created by Chunwei Chang on 2/17/23.
//

#include "paging/PageTable.h"

namespace paging {
void PageTable::Invalidate(uint32_t page_number) {
  page_table_[page_number].valid = false;
}

void PageTable::Reference(uint32_t page_number) {
  page_table_[page_number].reference = true;
}
void PageTable::Set(uint32_t page_number, PageEntry page_entry) {
  page_table_[page_number] = page_entry;
}
uint32_t PageTable::GetFrameNumber(uint32_t page_number) {
  return page_table_[page_number].frame_no;
}
bool PageTable::IsValid(uint32_t page_number) {
  return page_table_[page_number].valid;
}
void PageTable::Reset() {
  for (auto entry : page_table_) {
    entry.valid = false;
  }
}
} // paging