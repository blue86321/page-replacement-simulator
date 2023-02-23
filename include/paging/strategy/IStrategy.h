//
// Created by Chunwei Chang on 2/17/23.
//

#pragma once

#include <array>
#include "paging/PageTable.h"
#include "paging/Common.h"

namespace paging {

class IStrategy {
 public:
  virtual ~IStrategy() = default;
  // get `page number` to be replaced
  virtual uint32_t GetReplacePage(paging::PageTable &page_table) = 0;
  // after inserting a new page to an empty frame
  virtual void AfterNewPage(paging::PageTable &page_table, uint32_t page_number) = 0;
  // after referencing a page
  virtual void AfterReference(paging::PageTable &page_table, uint32_t page_number) = 0;
  // after replacing a page
  virtual void AfterReplace(paging::PageTable &page_table, uint32_t old_page_number, uint32_t new_page_number) = 0;
  // strategy name
  virtual std::string GetName() = 0;
};

} // paging
