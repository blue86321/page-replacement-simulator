//
// Created by Chunwei Chang on 2/16/23.
//

#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_map>
#include <array>
#include <map>
#include "strategy/IStrategy.h"
#include "PageTable.h"
#include "Common.h"
#include "PhysicalMemory.h"

namespace paging {

struct Indicator {
  uint32_t page_size;
  uint32_t frame_size;
  std::string strategy_name;
  uint32_t line;
  uint32_t page_fault;
  std::chrono::duration<double> time_lapse;

  Indicator(uint32_t page_size,
            uint32_t frame_size,
            const std::string &strategy_name,
            uint32_t line,
            uint32_t page_fault,
            const std::chrono::duration<double> &time_lapse)
      : page_size(page_size),
        frame_size(frame_size),
        strategy_name(strategy_name),
        line(line),
        page_fault(page_fault),
        time_lapse(time_lapse) {};
};

class PagingSimulator {
 public:
  PagingSimulator(uint32_t page_size, uint32_t frame_size)
      : page_table_(page_size), frame_(frame_size), output_line_frequency_(OUTPUT_LINE_FREQUENCY) {};
 public:
  // rvalue reference, so that value is temporary, we can do std::move
  void SetStrategy(std::unique_ptr<paging::IStrategy> &&strategy);
  void SetInput(std::string &&file_name);
  void SetOutputLineFrequency(uint32_t freq);
  void Run();
  std::vector<Indicator> GetStats();
  void ShowStats();
  void SetFrameSize(uint32_t size);
  void SetPageTableSize(uint32_t size);
 private:
  void Reset();
  // generate input file
  void GenerateInputIfNotExist();
  void AccessMemory(uint32_t page_number);
  void Replace(uint32_t from_page_number, uint32_t to_page_number);
  void SetupNewPage(uint32_t page_number, uint32_t frame_no);
 private:
  // physical frames, each frame stores the page number
  paging::PhysicalMemory frame_;
  paging::PageTable page_table_;
  // stats: strategy_name -> indicators
  std::vector<Indicator> stats;
  uint32_t cur_page_fault_{0};
  std::unique_ptr<paging::IStrategy> strategy_;
  std::string input_file_;
  uint32_t output_line_frequency_;
  std::chrono::time_point<std::chrono::system_clock> start_time;
};

}
