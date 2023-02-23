//
// Created by Chunwei Chang on 2/20/23.
//

#pragma once

#include <string>
#include <queue>

#include "IStrategy.h"

namespace paging::strategy {

struct PageAge {
  uint32_t page_number;
  uint32_t age;
  PageAge(uint32_t t_pn, uint32_t t_age): page_number(t_pn), age(t_age) {};
};

class Comparator {
 public:
  bool operator()(PageAge a, PageAge b) {
    return a.age > b.age;
  }
};

class CustomPq : public std::priority_queue<PageAge, std::vector<PageAge>, Comparator> {
 public:
  void UpdateAge(uint32_t key);
};

class Aging : public IStrategy {
 public:
  uint32_t GetReplacePage(PageTable &page_table) override;
  void AfterNewPage(PageTable &page_table, uint32_t page_number) override;
  void AfterReference(PageTable &page_table, uint32_t page_number) override;
  void AfterReplace(PageTable &page_table, uint32_t old_page_number, uint32_t new_page_number) override;
  std::string GetName() override;
 private:
  CustomPq priority_queue_;
  std::string name_ = "Aging";
};

} // paging

