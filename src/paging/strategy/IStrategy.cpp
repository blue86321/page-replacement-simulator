//
// Created by Chunwei Chang on 2/24/23.
//

#include "paging/strategy/IStrategy.h"

namespace paging::strategy {
void IStrategy::AfterNewPage(PhysicalMemory &frame, PageTable &page_table, uint32_t page_number) {
  CheckPeriod(frame, page_table);
  AfterNewPage_(frame, page_table, page_number);
}
void IStrategy::AfterReference(PhysicalMemory &frame, PageTable &page_table, uint32_t page_number) {
  CheckPeriod(frame, page_table);
  AfterReference_(frame, page_table, page_number);
}
void IStrategy::AfterReplace(PhysicalMemory &frame,
                             PageTable &page_table,
                             uint32_t old_page_number,
                             uint32_t new_page_number) {
  CheckPeriod(frame, page_table);
  AfterReplace_(frame, page_table, old_page_number, new_page_number);
}
void IStrategy::CheckPeriod(PhysicalMemory &frame, PageTable &page_table) {
  if (cur_period_++ == period_) {
    cur_period_ = 0;
    PeriodOperation(frame, page_table);
  }
}
}
