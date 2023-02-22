//
// Created by Chunwei Chang on 2/18/23.
//

#include "paging/PhysicalMemory.h"

namespace paging {
bool PhysicalMemory::IsFull() {
  return empty_frame == 0;
}
uint32_t PhysicalMemory::UseOneFrame() {
  for (size_t i = 0; i < size_; i++) {
    if (!frames_[i]) {
      frames_[i] = true;
      empty_frame--;
      return i;
    }
  }
  return -1;
}
void PhysicalMemory::Reset() {
  std::fill(frames_.begin(), frames_.end(), false);
  empty_frame = size_;
}

void PhysicalMemory::SetFrameSize(uint32_t size) {
  std::vector(size, false).swap(frames_);
  empty_frame = size;
  size_ = size;
}
} // paging