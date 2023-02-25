//
// Created by Chunwei Chang on 2/17/23.
//

#pragma once
#include <vector>

#include "Common.h"

namespace paging {

struct PageEntry {
  bool reference;
  bool modified;
  bool valid;
  bool protect;
  uint32_t frame_no;
  PageEntry() : reference(false), modified(false), valid(false), protect(false), frame_no(0) {};
  // construct with `frame_no` means `reference` and `valid`
  explicit PageEntry(uint32_t t_frame_no)
      : reference(true), modified(false), valid(true), protect(false), frame_no(t_frame_no) {};
};

class PageTable {
 public:
  explicit PageTable(uint32_t size) : size_(size), page_table_(size) {};
 public:
  bool IsValid(uint32_t page_number);
  bool IsReferenced(uint32_t page_number);
  bool IsModified(uint32_t page_number);
  void SetReference(uint32_t page_number, bool is_reference);
  uint32_t GetFrameNumber(uint32_t page_number);
  void Set(uint32_t page_number, PageEntry &page_entry);
  void Invalidate(uint32_t page_number);
  void Reference(uint32_t page_number);
  void Reset();
  void SetPageTableSize(uint32_t size);
  uint32_t Size() { return size_; };
 private:
  std::vector<PageEntry> page_table_;
  uint32_t size_;
};

} // paging
