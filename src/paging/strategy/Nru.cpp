//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Nru.h"

namespace paging::strategy {
uint32_t Nru::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  int64_t default_idx = INT64_MAX;
  int64_t not_reference_modified = default_idx;
  int64_t reference_not_modified = default_idx;
  int64_t reference_modified = default_idx;
  for (auto& cur_page_no : frame_pn) {
    if (page_table.IsValid(cur_page_no)) {
      if (!page_table.IsReferenced(cur_page_no) && !page_table.IsModified(cur_page_no)) {
        // not referenced, not modified
        return cur_page_no;
      } else if (!page_table.IsReferenced(cur_page_no) && page_table.IsModified(cur_page_no)) {
        // not referenced, modified
        not_reference_modified = not_reference_modified < cur_page_no ? not_reference_modified : cur_page_no;
      } else if (page_table.IsReferenced(cur_page_no) && !page_table.IsModified(cur_page_no)) {
        // referenced, not modified
        reference_not_modified = reference_not_modified < cur_page_no ? reference_not_modified : cur_page_no;
      } else {
        // referenced, modified
        reference_modified = reference_modified < cur_page_no ? reference_modified : cur_page_no;
      }
    }
  }
  if (not_reference_modified != default_idx) return not_reference_modified;
  if (reference_not_modified != default_idx) return reference_not_modified;
  if (reference_modified != default_idx) return reference_modified;
  return *frame_pn.begin();
}
void Nru::AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, uint32_t page_number) {
  frame_pn.push_back(page_number);
}
void Nru::AfterReplace_(PhysicalMemory &frame,
                        PageTable &page_table,
                        uint32_t old_page_number,
                        uint32_t new_page_number) {
  for (auto& pn : frame_pn) {
    if (pn == old_page_number) {
      pn = new_page_number;
      break;
    }
  }
}
std::string Nru::GetName() {
  return name_;
}
void Nru::PeriodOperation(PhysicalMemory &frame, PageTable &page_table) {
  for (int i = 0; i < frame.Size(); i ++) {
    page_table.SetReference(frame.GetPage(i), false);
  }
}
}