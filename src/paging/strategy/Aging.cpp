//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Aging.h"

namespace paging::strategy {
int Aging::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  // min age
  auto min_element = std::min_element(age_map.begin(),
                                      age_map.end(),
                                      [](const auto &a, const auto &b) { return a.second < b.second; });
  return (*min_element).first;
}
void Aging::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_number) {
  age_map[page_number] = 1 << 31;
}
void Aging::AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_number) {
  // has not referenced in this period
  if (ref_page_this_period.find(page_number) == ref_page_this_period.end()) {
    ref_page_this_period.insert(page_number);
    age_map[page_number] = (age_map[page_number] >> 1) | (1 << 31);
  }

}
void Aging::AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_number, int new_page_number) {
  age_map.erase(old_page_number);
  AfterNewPage_(frame, page_table, new_page_number);
}
std::string Aging::GetName() {
  return name_;
}
void Aging::PeriodOperation(PhysicalMemory &frame, PageTable &page_table) {
  for (auto &element : age_map) {
    if (page_table.IsReferenced(element.first)) {
      page_table.SetReference(element.first, false);
    } else {
      element.second = (element.second >> 1);
    }
  }
  ref_page_this_period.clear();
}
void Aging::Reset_() {
  age_map.clear();
  ref_page_this_period.clear();
}
} // paging