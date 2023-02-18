//
// Created by Chunwei Chang on 2/18/23.
//

#pragma once

#include <array>
#include <paging/Common.h>
namespace paging {

class PhysicalMemory {
 public:
  bool IsFull();
  uint32_t UseOneFrame();
 private:
  std::array<bool, FRAME_SIZE> frames_{};
  uint32_t empty_frame = FRAME_SIZE;
};

} // paging
