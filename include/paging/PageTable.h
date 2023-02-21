//
// Created by Chunwei Chang on 2/17/23.
//

#pragma once
#include <array>

#include "paging/Common.h"

namespace paging {

struct PageEntry {
  bool reference;
  bool modified;
  bool valid;
  bool protect;
  uint32_t frame_no;
};

class PageTable {
 public:
  bool IsValid(uint32_t page_number);
  bool IsReferenced(uint32_t page_number);
  bool IsModified(uint32_t page_number);
  void SetReference(uint32_t page_number, bool is_reference);
  uint32_t GetFrameNumber(uint32_t page_number);
  void Set(uint32_t page_number, PageEntry page_entry);
  void Invalidate(uint32_t page_number);
  void Reference(uint32_t page_number);
  void Reset();
 private:
  std::array<PageEntry, PAGE_TABLE_SIZE> page_table_{};
};

} // paging
