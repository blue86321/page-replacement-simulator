//
// Created by Chunwei Chang on 2/17/23.
//

#include "paging/PageTable.h"

namespace paging {
void PageTable::Invalidate(int page_number) {
  page_table_[page_number].valid = false;
}

void PageTable::Reference(int page_number) {
  page_table_[page_number].reference = true;
}
void PageTable::Set(int page_number, PageEntry &page_entry) {
  page_table_[page_number] = page_entry;
}
int PageTable::GetFrameNumber(int page_number) {
  return page_table_[page_number].frame_no;
}
bool PageTable::IsValid(int page_number) {
  return page_table_[page_number].valid;
}
void PageTable::Reset() {
  for (auto &page_entry : page_table_) {
    page_entry.valid = false;
  }
}
bool PageTable::IsReferenced(int page_number) {
  return page_table_[page_number].reference;
}
bool PageTable::IsModified(int page_number) {
  return page_table_[page_number].modified;
}
void PageTable::SetReference(int page_number, bool is_reference) {
  page_table_[page_number].reference = is_reference;
}
void PageTable::SetPageTableSize(int size) {
  page_table_.resize(size);
  Reset();
}
void PageTable::Modify(int page_number) {
  page_table_[page_number].modified = true;
}
size_t PageTable::Size() {
  return page_table_.size();
}
} // paging