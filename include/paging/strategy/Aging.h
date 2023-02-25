//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include <queue>

#include "IStrategy.h"

namespace paging::strategy {

struct PageAge {
  int page_number;
  uint32_t age;
  PageAge(int t_pn, int t_age): page_number(t_pn), age(t_age) {};
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

class Aging : public IStrategy {
 protected:
  void AfterNewPage_(PhysicalMemory &frame, PageTable &page_table, int page_number) override;
  void AfterReference_(PhysicalMemory &frame, PageTable &page_table, int page_number) override;
  void AfterReplace_(PhysicalMemory &frame,
                     PageTable &page_table,
                     int old_page_number,
                     int new_page_number) override;
  void PeriodOperation(PhysicalMemory &frame, PageTable &page_table) override;
 public:
  int GetReplacePage(PhysicalMemory &frame, paging::PageTable &page_table) override;
  std::string GetName() override;
 private:
  CustomPq priority_queue_;
  std::string name_ = "Aging";
};

} // paging

