//
// Created by Chunwei Chang on 2/17/23.
//

#pragma once

#include <array>
#include "paging/PageTable.h"
#include "paging/PhysicalMemory.h"
#include "paging/Common.h"

namespace paging::strategy {

class IStrategy {
 public:
  virtual ~IStrategy() = default;
 public:
  // get `page number` to be replaced
  virtual uint32_t GetReplacePage(paging::PhysicalMemory &frame, paging::PageTable &page_table) = 0;
  // after inserting a new page to an empty frame
  void AfterNewPage(paging::PhysicalMemory &frame, paging::PageTable &page_table, uint32_t page_number);
  // after referencing a page
  void AfterReference(paging::PhysicalMemory &frame, paging::PageTable &page_table, uint32_t page_number);
  // after replacing a page
  void AfterReplace(paging::PhysicalMemory &frame,
                             paging::PageTable &page_table,
                             uint32_t old_page_number,
                             uint32_t new_page_number);
  // strategy name
  virtual std::string GetName() = 0;
  void SetPeriod(uint32_t period) { period_ = period; };
 protected:
  virtual void AfterNewPage_(paging::PhysicalMemory &frame, paging::PageTable &page_table, uint32_t page_number) = 0;
  virtual void AfterReference_(paging::PhysicalMemory &frame, paging::PageTable &page_table, uint32_t page_number) = 0;
  virtual void AfterReplace_(paging::PhysicalMemory &frame,
                             paging::PageTable &page_table,
                             uint32_t old_page_number,
                             uint32_t new_page_number) = 0;
  virtual void PeriodOperation(PhysicalMemory &frame, PageTable &page_table) = 0;
 private:
  void CheckPeriod(PhysicalMemory &frame, PageTable &page_table);
  static inline uint32_t period_ = 5;
  uint32_t cur_period_ = 0;
};


} // paging
