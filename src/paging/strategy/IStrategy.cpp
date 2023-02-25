//
// Created by Chunwei Chang on 2/24/23.
//

#include "paging/strategy/IStrategy.h"

namespace paging::strategy {
void IStrategy::AfterNewPage(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_number) {
  AfterNewPage_(frame, page_table, page_number);
  CheckPeriod(frame, page_table);
}
void IStrategy::AfterReference(PhysicalMemory &frame, PageTable &page_table, int page_number) {
  AfterReference_(frame, page_table, page_number);
  CheckPeriod(frame, page_table);
}
void IStrategy::AfterReplace(PhysicalMemory &frame, PageTable &page_table, int old_page_number, int new_page_number) {
  AfterReplace_(frame, page_table, old_page_number, new_page_number);
  CheckPeriod(frame, page_table);
}
void IStrategy::CheckPeriod(PhysicalMemory &frame, PageTable &page_table) {
  if (++cur_period_ >= period_) {
    cur_period_ = 0;
    PeriodOperation(frame, page_table);
  }
}
void IStrategy::SetPeriod(int period) {
  period_ = period;
}
}
