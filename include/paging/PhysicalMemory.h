//
// Created by Chunwei Chang on 2/18/23.
//

#pragma once
#include <vector>
#include "Common.h"

namespace paging {

class PhysicalMemory {
 public:
  explicit PhysicalMemory(uint32_t size) : size_(size), empty_frame(size), frames_(size, false) {};
  bool IsFull();
  void Reset();
  uint32_t UseOneFrame();
  void SetFrameSize(uint32_t size);
  uint32_t Size() { return size_; };
 private:
  std::vector<bool> frames_;
  uint32_t empty_frame;
  uint32_t size_;
};

} // paging
