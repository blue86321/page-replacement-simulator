//
// Created by Chunwei Chang on 2/18/23.
//

#include "paging/PhysicalMemory.h"

namespace paging {
bool PhysicalMemory::IsFull() {
  return empty_frame == 0;
}
int PhysicalMemory::UseOneFrame(int page_number) {
  for (int i = 0; i < frames_.size(); i++) {
    if (frames_[i] == DEFAULT_FRAME_NO) {
      frames_[i] = page_number;
      empty_frame--;
      return i;
    }
  }
  return DEFAULT_FRAME_NO;
}
void PhysicalMemory::Reset() {
  for (auto & frame : frames_) {
    frame = DEFAULT_FRAME_NO;
  }
}

void PhysicalMemory::SetFrameSize(int size) {
  std::vector<int>(size, DEFAULT_FRAME_NO).swap(frames_);
  empty_frame = size;
}
int PhysicalMemory::GetPage(int frame_no) {
  return frames_[frame_no];
}
size_t PhysicalMemory::Size() {
  return frames_.size();
}
void PhysicalMemory::SetFrame(int frame_no, int page_number) {
  frames_[frame_no] = page_number;
}
} // paging