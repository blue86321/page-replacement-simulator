//
// Created by Chunwei Chang on 2/18/23.
//

#pragma once
#include <vector>
#include "Common.h"
#include "PageTable.h"

namespace paging {

class PhysicalMemory {
 public:
  explicit PhysicalMemory(uint32_t size) : empty_frame(size), frames_(size) {};
 public:
  bool IsFull();
  void Reset();
  uint32_t GetPage(uint32_t frame_no);
  uint32_t UseOneFrame(uint32_t page_number);
  void SetFrameSize(uint32_t size);
  uint32_t Size() { return frames_.size(); };
 private:
  // frame store page_number to visit page_entry status (valid, reference...)
  // Note: in reality, frame contains actual data as well, but here we ignore it.
  std::vector<uint32_t> frames_;
  uint32_t empty_frame;
};

} // paging
