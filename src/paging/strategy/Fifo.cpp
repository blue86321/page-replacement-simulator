//
// Created by Chunwei Chang on 2/18/23.
//

#include "paging/strategy/Fifo.h"

namespace paging::strategy {
uint32_t Fifo::GetReplacePage(paging::PageTable &page_table) {
  auto page_number = queue.front();
  queue.pop();
  return page_number;
}

void Fifo::AfterNewPage(paging::PageTable &page_table, uint32_t page_number) {
  queue.push(page_number);
}
void Fifo::AfterReplace(PageTable &page_table, uint32_t page_number) {
  queue.push(page_number);
}
std::string Fifo::GetName() {
  return name_;
}
} // paging