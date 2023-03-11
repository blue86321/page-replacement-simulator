//
// Created by Chunwei Chang on 2/17/23.
//

#pragma once

#include <string>
#include <iostream>
#include "paging/PageTable.h"
#include "paging/PhysicalMemory.h"
#include "paging/Common.h"

namespace paging::strategy {

// Base strategy for page replacement algorithms
// concrete strategy needs to implement virtual methods
class IStrategy {
 public:
  virtual ~IStrategy() = default;
 public:
  // get `page number` to be replaced
  virtual int GetReplacePage(paging::PhysicalMemory &frame, paging::PageTable &page_table) = 0;
  // after inserting a new page to an empty frame
  void AfterNewPage(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_no);
  // after referencing a page
  void AfterReference(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_no);
  // after replacing a page
  void AfterReplace(paging::PhysicalMemory &frame,
                    paging::PageTable &page_table,
                    int old_page_no,
                    int new_page_no);
  // strategy name
  virtual std::string GetName() = 0;
  void SetPeriod(int period);
  int GetPeriod();
  void Reset();
 protected:
  virtual void AfterNewPage_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_no) = 0;
  virtual void AfterReference_(paging::PhysicalMemory &frame, paging::PageTable &page_table, int page_no) = 0;
  virtual void AfterReplace_(paging::PhysicalMemory &frame,
                             paging::PageTable &page_table,
                             int old_page_no,
                             int new_page_no) = 0;
  virtual void PeriodOperation_(PhysicalMemory &frame, PageTable &page_table) = 0;
  virtual void Reset_() = 0;
 private:
  void CheckPeriod(PhysicalMemory &frame, PageTable &page_table);
  static inline int period_ = 10;
  int cur_period_ = 0;
};

} // paging
