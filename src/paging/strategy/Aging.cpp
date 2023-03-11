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
void Aging::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_no) {
  age_map[page_no] = 1 << 31;
}
void Aging::AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_no) {
  // insert 1 to the highest bit in current period
  if (ref_page_cur_period.find(page_no) == ref_page_cur_period.end()) {
    ref_page_cur_period.insert(page_no);
    age_map[page_no] = (age_map[page_no] >> 1) | (1 << 31);
  }

}
void Aging::AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) {
  age_map.erase(old_page_no);
  AfterNewPage_(frame, page_table, new_page_no);
}

void Aging::PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) {
  // reset all reference bit in the frame
  // insert 1 to the highest bit (aging) if the frame is not referenced in current period
  for (auto &element : age_map) {
    if (page_table.IsReferenced(element.first)) {
      page_table.SetReference(element.first, false);
    } else {
      element.second = (element.second >> 1);
    }
  }
  ref_page_cur_period.clear();
}

void Aging::Reset_() {
  age_map.clear();
  ref_page_cur_period.clear();
}

std::string Aging::GetName() {
  return name_;
}
} // paging