//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "IStrategy.h"

namespace paging::strategy {
struct PageAge {
  int page_no;
  uint32_t age;
  PageAge(int t_pn, int t_age): page_no(t_pn), age(t_age) {};
};

class Comparator {
 public:
  bool operator()(PageAge a, PageAge b) {
    return a.age > b.age;
  }
};

class CustomPq : public std::priority_queue<PageAge, std::vector<PageAge>, Comparator> {
 public:
  void UpdateAge(int key);
  void Aging(PageTable& page_table);
};

class AgingHeap : public IStrategy {
 protected:
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_no) override;
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_no) override;
  void AfterReplace_(PhysicalMemory &frame, PageTable &page_table, int old_page_no, int new_page_no) override;
  void PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) override;
  void Reset_() override;
 public:
  int GetReplacePage(PhysicalMemory &a, paging::PageTable &b) override;
  std::string GetName() override;
 private:
  CustomPq priority_queue_;
  std::unordered_map<int, unsigned int> age_map_{};
  std::unordered_set<int> ref_page_cur_period_{};
  std::string name_ = "AgingHeap";
};

} // paging

