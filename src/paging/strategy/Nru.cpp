//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Nru.h"

namespace paging::strategy {
int Nru::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  int default_idx = INT_MAX;
  int not_reference_modified = default_idx;
  int reference_not_modified = default_idx;
  int reference_modified = default_idx;
  for (int i = 0; i < frame.Size(); i ++) {
    auto cur_page_no = frame.GetPage(i);
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
  return frame.GetPage(0);
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