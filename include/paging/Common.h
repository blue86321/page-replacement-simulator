//
// Created by Chunwei Chang on 2/17/23.
//

#pragma once

#include <string>

namespace paging {

#define PAGE_REF_LINES 50000
#define OUTPUT_LINE_FREQUENCY 50000
#define INPUT_PREFIX "input/page_ref_"

#define SMALL_BLOCK_CNT 3
#define PAGE_PER_BLOCK 10
#define INTERVAL 50

static std::string GetHotPageInputPrefix(int small_block_cnt = SMALL_BLOCK_CNT,
                                         int page_per_block = PAGE_PER_BLOCK,
                                         int interval = INTERVAL) {
  return INPUT_PREFIX + std::to_string(small_block_cnt) + "_block_" + std::to_string(page_per_block) + "_page_"
      + std::to_string(interval) + "_itv_";
}

} // paging

