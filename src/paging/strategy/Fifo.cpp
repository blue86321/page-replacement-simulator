//
// Created by Chunwei Chang on 2/18/23.
//

#include "paging/strategy/Fifo.h"

namespace paging::strategy {
int Fifo::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  return queue.front();
}

void Fifo::AfterNewPage_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_no) {
  queue.push(page_no);
}
void Fifo::AfterReplace_(paging::PhysicalMemory &frame,
                         PageTable &page_table,
                         int old_page_no,
                         int new_page_no) {
  queue.pop();
  queue.push(new_page_no);
}
std::string Fifo::GetName() {
  return name_;
}
void Fifo::Reset_() {
  std::queue<int>().swap(queue);
}
} // paging