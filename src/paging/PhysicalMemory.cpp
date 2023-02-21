//
// Created by Chunwei Chang on 2/18/23.
//

#include "paging/PhysicalMemory.h"

namespace paging {
bool PhysicalMemory::IsFull() {
  return empty_frame == 0;
}
uint32_t PhysicalMemory::UseOneFrame() {
  for (size_t i = 0; i < FRAME_SIZE; i++) {
    if (!frames_[i]) {
      frames_[i] = true;
      empty_frame--;
      return i;
    }
  }
  return -1;
}
void PhysicalMemory::Reset() {
  frames_.fill(false);
  empty_frame = FRAME_SIZE;
}
} // paging