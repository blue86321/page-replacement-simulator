//
// Created by Chunwei Chang on 2/20/23.
//

#include "paging/strategy/Nru.h"
#include <iomanip>

namespace paging::strategy {
int Nru::GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) {
  // search a frame to replace based on the rule
  // Ps. If multiple frames are in the same level
  //     we need to choose a random frame at that level in theory, but here we choose the smaller index for simplicity.
  int victim = -1;
  int default_idx = INT_MAX;
  int not_reference_modified = default_idx;
  int reference_not_modified = default_idx;
  int reference_modified = default_idx;
  for (int i = 0; i < frame.Size(); i++) {
    auto cur_page_no = frame.GetPage(i);
    if (page_table.IsValid(cur_page_no)) {
      if (!page_table.IsReferenced(cur_page_no) && !page_table.IsModified(cur_page_no)) {
        // 1.not referenced, not modified
        victim = cur_page_no;
        break;
      } else if (!page_table.IsReferenced(cur_page_no) && page_table.IsModified(cur_page_no)) {
        // 2.not referenced, modified
        not_reference_modified = not_reference_modified < cur_page_no ? not_reference_modified : cur_page_no;
      } else if (page_table.IsReferenced(cur_page_no) && !page_table.IsModified(cur_page_no)) {
        // 3.referenced, not modified
        reference_not_modified = reference_not_modified < cur_page_no ? reference_not_modified : cur_page_no;
      } else {
        // 4.referenced, modified
        reference_modified = reference_modified < cur_page_no ? reference_modified : cur_page_no;
      }
    }
  }

  if (victim == -1 && not_reference_modified != default_idx) victim = not_reference_modified;
  if (victim == -1 && reference_not_modified != default_idx) victim = reference_not_modified;
  if (victim == -1 && reference_modified != default_idx) victim = reference_modified;
  if (victim == -1) victim = frame.GetPage(0);

  if (verbose_) {
    std::cout << std::setw(10) << "Page" << std::setw(10) << "Ref" << std::setw(10) << "Modify" << "\n";
    for (auto &page_no : frame.GetFrames()) {
      std::cout
        << std::setw(10) << page_no
        << std::setw(10) << page_table.IsReferenced(page_no)
        << std::setw(10) << page_table.IsModified(page_no);
      if (page_no == victim) {
        std::cout << " --- victim (get smallest page when tie)";
      }
      std::cout << "\n";
    }
  }
  return victim;
}

void Nru::PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) {
  // reset all frames' reference bit to 0
  for (int i = 0; i < frame.Size(); i++) {
    page_table.SetReference(frame.GetPage(i), false);
  }
}

std::string Nru::GetName() {
  return name_;
}
}