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
  virtual uint32_t GetReplacePage(paging::PageTable &page_table) = 0;
  virtual void PostNewPage(paging::PageTable &page_table, uint32_t page_number) = 0;
  virtual void PostReference(paging::PageTable &page_table, uint32_t page_number) = 0;
  virtual void PostReplace(paging::PageTable &page_table, uint32_t page_number) = 0;
  virtual std::string GetName() = 0;
};

} // paging
