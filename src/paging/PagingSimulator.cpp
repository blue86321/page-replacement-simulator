//
// Created by Chunwei Chang on 2/16/23.
//

#include "paging/PagingSimulator.h"

#include <fstream>
#include <random>
#include <sys/stat.h>
#include <string>

void paging::PagingSimulator::SetStrategy(std::unique_ptr<paging::IStrategy> &&strategy) {
  strategy_ = std::move(strategy);
}

void paging::PagingSimulator::GenerateInputIfNotExist() {
//  std::string file_name = std::string(INPUT_PAGE_REF_NAME) + "_" + std::to_string(MAX_PAGE) + ".txt";
  std::string file_name = INPUT_FILE;
  struct stat buffer{};
  bool exists = stat(file_name.c_str(), &buffer) == 0;
  if (!exists) {
    std::ofstream file;
    file.open(file_name);
    std::random_device rd;  // non-deterministic generator
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(1, PAGE_TABLE_SIZE);
    for (int i = 0; i < PAGE_REF_LINES; i++) {
      file << dist(generator) << "\n";
    }
    file.close();
  }
}

void paging::PagingSimulator::Run() {
  GenerateInputIfNotExist();

  // init
  cur_page_fault_ = 0;
  frame_.Reset();

  // read each line to reference a page
  std::ifstream input;
  input.open(INPUT_FILE);
  uint32_t line_counter = 0;
  if (input.is_open()) {
    std::string line;
    while (std::getline(input, line)) {
      int page_number = stoi(line);
      AccessMemory(page_number);
      // stats
      line_counter++;
      if (line_counter % OUTPUT_LINE_FREQUENCY == 0) {
        stats[strategy_->GetName()].push_back({line_counter, cur_page_fault_});
      }
    }
    input.close();
  }
}

void paging::PagingSimulator::AccessMemory(uint32_t page_number) {
  if (page_table_.IsValid(page_number)) {
    page_table_.Reference(page_number);
    strategy_->AfterReference(page_table_, page_number);
  } else {
    // page fault
    cur_page_fault_++;
    if (frame_.IsFull()) {
      // page replacement
      uint32_t replaced_page = strategy_->GetReplacePage(page_table_);
      Replace(replaced_page, page_number);
      strategy_->AfterReplace(page_table_, page_number);
    } else {
      uint32_t frame_no = frame_.UseOneFrame();
      SetupNewPage(page_number, frame_no);
      strategy_->AfterNewPage(page_table_, page_number);
    }
  }
}

void paging::PagingSimulator::Replace(uint32_t from_page_number, uint32_t to_page_number) {
  uint32_t frame_no = page_table_.GetFrameNumber(from_page_number);
  page_table_.Invalidate(from_page_number);
  PageEntry page_entry{true, false, true, false, frame_no};
  page_table_.Set(to_page_number, page_entry);
}

void paging::PagingSimulator::SetupNewPage(uint32_t page_number, uint32_t frame_no) {
  PageEntry page_entry{true, false, true, false, frame_no};
  page_table_.Set(page_number, page_entry);
}
void paging::PagingSimulator::ShowStats() {
  for (auto [strategy_name, line_stat] : stats) {
    for (Indicator indicator : line_stat) {
      std::cout << "Strategy: " << strategy_name
        << ", Line: " << indicator.line
        << ", Page fault: " << indicator.page_fault
        << "\n";
    }
  }
}
