//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Nru.h"

namespace paging::strategy {
uint32_t Nru::GetReplacePage(PageTable &page_table) {
  uint32_t idx = 0;
  int64_t not_reference_modified = -1;
  int64_t reference_not_modified = -1;
  int64_t reference_modified = -1;
  while (page_table.IsValid(idx) && idx < PAGE_TABLE_SIZE) {
    if (!page_table.IsReferenced(idx) && !page_table.IsModified(idx)) {
      // not referenced, not modified
      return idx;
    } else if (!page_table.IsReferenced(idx) && page_table.IsModified(idx)) {
      // not referenced, modified
      not_reference_modified = idx;
    } else if (page_table.IsReferenced(idx) && !page_table.IsModified(idx)) {
      // referenced, not modified
      reference_not_modified = idx;
    } else {
      // referenced, modified
      reference_modified = idx;
    }
    idx++;
  }
  if (not_reference_modified != -1) return not_reference_modified;
  if (reference_not_modified != -1) return reference_not_modified;
  if (reference_modified != -1) return reference_modified;
  return idx;
}
std::string Nru::GetName() {
  return name_;
}
}