//
// Created by Chunwei Chang on 2/18/23.
//

#include "paging/PhysicalMemory.h"

namespace paging {
bool PhysicalMemory::IsFull() {
  return empty_frame == 0;
}
uint32_t PhysicalMemory::UseOneFrame(uint32_t page_number) {
  for (size_t i = 0; i < frames_.size(); i++) {
    if (frames_[i] == 0) {
      frames_[i] = page_number;
      empty_frame--;
      return i;
    }
  }
  return 0;
}
void PhysicalMemory::Reset() {
  for (auto & frame : frames_) {
    frame = 0;
  }
}

void PhysicalMemory::SetFrameSize(uint32_t size) {
  std::vector<uint32_t>(size).swap(frames_);
  empty_frame = size;
}
uint32_t PhysicalMemory::GetPage(uint32_t frame_no) {
  return frames_[frame_no];
}
} // paging