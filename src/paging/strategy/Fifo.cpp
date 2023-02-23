//
// Created by Chunwei Chang on 2/18/23.
//

#include "paging/strategy/Fifo.h"

namespace paging::strategy {
uint32_t Fifo::GetReplacePage(paging::PageTable &page_table) {
  return queue.front();
}

void Fifo::AfterNewPage(paging::PageTable &page_table, uint32_t page_number) {
  queue.push(page_number);
}
void Fifo::AfterReplace(PageTable &page_table, uint32_t old_page_number, uint32_t new_page_number) {
  queue.pop();
  queue.push(new_page_number);
}
std::string Fifo::GetName() {
  return name_;
}
} // paging