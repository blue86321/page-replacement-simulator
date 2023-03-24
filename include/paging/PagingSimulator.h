//
// Created by Chunwei Chang on 2/16/23.
//

#pragma once

#include <iostream>
#include <chrono>
#include <vector>
#include <fstream>
#include <random>
#include <sys/stat.h>
#include <string>

#include "strategy/IStrategy.h"
#include "PageTable.h"
#include "Common.h"
#include "PhysicalMemory.h"
#include "paging/strategy/Fifo.h"

namespace paging {

struct Indicator {
  int page_size;
  int frame_size;
  std::string strategy_name;
  size_t line;
  size_t page_fault;
  std::chrono::duration<double> time_lapse;

  Indicator(int page_size,
            int frame_size,
            const std::string_view &strategy_name,
            size_t line,
            size_t page_fault,
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
  PagingSimulator(int page_size, int frame_size)
      : page_table_(page_size), frame_(frame_size), output_line_frequency_(OUTPUT_LINE_FREQUENCY) {};
 public:
  // rvalue reference, so that value is temporary, we can do std::move
  void SetStrategy(std::unique_ptr<strategy::IStrategy> &&strategy);
  // set input file location
  void SetInputPrefix(std::string &&prefix);
  // stat is collected every `freq` line
  void SetOutputLineFrequency(int freq);
  // show each memory access procedure. e.g., GetReplacePage
  void SetStrategyVerbose(bool verbose);
  // Run the simulator
  void Run();
  std::vector<Indicator> GetStats();
  void ShowStats();
  void ClearStats();
  void SetFrameSize(int size);
  void SetPageTableSize(int size);
  void SetStrategyPeriod(int period);
  void SetInputModifyPercent(int modify_percent);
  // generate input file
  void GenerateUniformDistInputIfNotExist();
  void GenerateHotPageAccessInputIfNotExist(int small_block_cnt = SMALL_BLOCK_CNT,
                                            int page_per_block = PAGE_PER_BLOCK,
                                            int interval = INTERVAL);
  void GenerateSequenceInputIfNotExist();
  int GetPageFault();
 private:
  std::string GetFileName();
  void Reset();
  void AccessMemory(int page_no, bool is_write);
  void Replace(int from_page_no, int to_page_no, bool is_write);
  void SetupNewPage(int page_no, int frame_no, bool is_write);
 private:
  // physical frames, each frame stores the page number
  paging::PhysicalMemory frame_;
  paging::PageTable page_table_;
  // stats_: strategy_name -> indicators
  std::vector<Indicator> stats_;
  int cur_page_fault_{0};
  std::unique_ptr<strategy::IStrategy> strategy_ = std::make_unique<strategy::Fifo>();
  std::string input_prefix_;
  int output_line_frequency_;
  std::chrono::time_point<std::chrono::system_clock> start_time_;
  int modify_percent_ = 50;
  int strategy_verbose_ = false;
};

}
