//
// Created by Chunwei Chang on 2/18/23.
//

#include "paging/strategy/Fifo.h"

namespace paging::strategy {
int Fifo::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  if (verbose_) {
    std::cout << "Queue: ";
    for (auto& page_no : queue_verbose_) {
      if (page_no == queue_.front()) {
        std::cout << page_no << "(victim) ";
      } else {
        std::cout << page_no << " ";
      }
    }
  }
  return queue_.front();
}

void Fifo::AfterNewPage_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_no) {
  queue_.push(page_no);
  if (verbose_)
    queue_verbose_.push_back(page_no);
}
void Fifo::AfterReplace_(paging::PhysicalMemory &frame,
                         PageTable &page_table,
                         int old_page_no,
                         int new_page_no) {
  queue_.pop();
  queue_.push(new_page_no);
  if (verbose_) {
    queue_verbose_.erase(std::find(queue_verbose_.begin(), queue_verbose_.end(), old_page_no));
    queue_verbose_.push_back(new_page_no);
  }
}
std::string Fifo::GetName() {
  return name_;
}
void Fifo::Reset_() {
  std::queue<int>().swap(queue_);
}
} // paging