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
  int frame_no;
  PageEntry() : reference(false), modified(false), valid(false), protect(false), frame_no(-1) {};
  // construct with `frame_no` means `reference` and `valid`
  explicit PageEntry(int t_frame_no, bool is_modify)
      : reference(true), modified(is_modify), valid(true), protect(false), frame_no(t_frame_no) {};
};

class PageTable {
 public:
  explicit PageTable(int size) : page_table_(size) {};
 public:
  bool IsValid(int page_no);
  bool IsReferenced(int page_no);
  bool IsModified(int page_no);
  void SetReference(int page_no, bool is_reference);
  int GetFrameNumber(int page_no);
  void Set(int page_no, PageEntry &page_entry);
  void Invalidate(int page_no);
  void Reference(int page_no);
  void Modify(int page_no);
  void Reset();
  void SetPageTableSize(int size);
  size_t Size();
 private:
  std::vector<PageEntry> page_table_;
};

} // paging
