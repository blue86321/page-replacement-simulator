//
// Created by Chunwei Chang on 2/17/23.
//

#include "paging/PageTable.h"

namespace paging {
void PageTable::Invalidate(int page_no) {
  page_table_[page_no].valid = false;
}

void PageTable::Reference(int page_no) {
  page_table_[page_no].reference = true;
}
void PageTable::Set(int page_no, PageEntry &page_entry) {
  page_table_[page_no] = page_entry;
}
int PageTable::GetFrameNumber(int page_no) {
  return page_table_[page_no].frame_no;
}
bool PageTable::IsValid(int page_no) {
  return page_table_[page_no].valid;
}
void PageTable::Reset() {
  for (auto &page_entry : page_table_) {
    page_entry.valid = false;
  }
}
bool PageTable::IsReferenced(int page_no) {
  return page_table_[page_no].reference;
}
bool PageTable::IsModified(int page_no) {
  return page_table_[page_no].modified;
}
void PageTable::SetReference(int page_no, bool is_reference) {
  page_table_[page_no].reference = is_reference;
}
void PageTable::SetPageTableSize(int size) {
  page_table_.resize(size);
  Reset();
}
void PageTable::Modify(int page_no) {
  page_table_[page_no].modified = true;
}
size_t PageTable::Size() {
  return page_table_.size();
}
} // paging