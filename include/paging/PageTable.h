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
  explicit PageTable(int size) : size_(size), page_table_(size) {};
 public:
  bool IsValid(int page_number);
  bool IsReferenced(int page_number);
  bool IsModified(int page_number);
  void SetReference(int page_number, bool is_reference);
  int GetFrameNumber(int page_number);
  void Set(int page_number, PageEntry &page_entry);
  void Invalidate(int page_number);
  void Reference(int page_number);
  void Modify(int page_number);
  void Reset();
  void SetPageTableSize(int size);
  int Size() { return size_; };
 private:
  std::vector<PageEntry> page_table_;
  int size_;
};

} // paging
