//
// Created by Chunwei Chang on 2/18/23.
//

#pragma once
#include <vector>
#include "Common.h"
#include "PageTable.h"

#define DEFAULT_FRAME_NO -1

namespace paging {

class PhysicalMemory {
 public:
  explicit PhysicalMemory(int size) : empty_frame(size), frames_(size, DEFAULT_FRAME_NO) {};
 public:
  bool IsFull();
  void Reset();
  int GetPage(int frame_no);
  int UseOneFrame(int page_number);
  void SetFrame(int frame_no, int page_number);
  void SetFrameSize(int size);
  size_t Size();
 private:
  // frame store page_number to visit page_entry status (valid, reference...)
  // Note: in reality, frame contains actual data as well, but here we ignore it.
  std::vector<int> frames_;
  int empty_frame;
};

} // paging
