//
// Created by Chunwei Chang on 2/16/23.
//

#include "paging/PagingSimulator.h"

#include <fstream>
#include <random>
#include <sys/stat.h>
#include <string>

namespace paging {
void PagingSimulator::SetStrategy(std::unique_ptr<strategy::IStrategy> &&strategy) {
  // because `strategy` is a rvalue, we can "steal" memory from it
  strategy_ = std::move(strategy);
}

void PagingSimulator::GenerateInputIfNotExist() {
//  std::string file_name = std::string(INPUT_PAGE_REF_NAME) + "_" + std::to_string(MAX_PAGE) + ".txt";
  std::string file_name = input_file_;
  struct stat buffer{};
  bool exists = stat(file_name.c_str(), &buffer) == 0;
  if (!exists) {
    std::ofstream file;
    file.open(file_name);
    std::random_device rd;  // non-deterministic generator
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(1, (int) page_table_.Size());
    for (int i = 0; i < PAGE_REF_LINES; i++) {
      file << dist(generator) << "\n";
    }
    file.close();
  }
}

void PagingSimulator::Run() {
  GenerateInputIfNotExist();

  Reset();

  // read each line to reference a page
  std::ifstream input;
  input.open(input_file_);
  uint32_t line_counter = 0;
  if (input.is_open()) {
    std::string line;
    while (std::getline(input, line)) {
      int page_number = stoi(line);
      AccessMemory(page_number);
      // stats
      line_counter++;
      if (line_counter % output_line_frequency_ == 0) {
        auto now = std::chrono::system_clock::now();
        stats.emplace_back(page_table_.Size(),
                           frame_.Size(),
                           strategy_->GetName(),
                           line_counter,
                           cur_page_fault_,
                           now - start_time);
      }
    }
    input.close();
  }
}

void PagingSimulator::AccessMemory(uint32_t page_number) {
  if (page_table_.IsValid(page_number)) {
    page_table_.Reference(page_number);
    strategy_->AfterReference(frame_, page_table_, page_number);
  } else {
    // page fault
    cur_page_fault_++;
    if (frame_.IsFull()) {
      // page replacement
      uint32_t old_page_number = strategy_->GetReplacePage(frame_, page_table_);
      Replace(old_page_number, page_number);
      strategy_->AfterReplace(frame_, page_table_, old_page_number, page_number);
    } else {
      uint32_t frame_no = frame_.UseOneFrame(page_number);
      SetupNewPage(page_number, frame_no);
      strategy_->AfterNewPage(frame_, page_table_, page_number);
    }
  }
}

void PagingSimulator::Replace(uint32_t old_page_number, uint32_t new_page_number) {
  uint32_t frame_no = page_table_.GetFrameNumber(old_page_number);
  page_table_.Invalidate(old_page_number);
  PageEntry page_entry(frame_no);
  page_table_.Set(new_page_number, page_entry);
}

void PagingSimulator::SetupNewPage(uint32_t page_number, uint32_t frame_no) {
  PageEntry page_entry(frame_no);
  page_table_.Set(page_number, page_entry);
}

bool IndicatorComparator(const Indicator &a, const Indicator &b) {
  if (a.frame_size != b.frame_size) return a.frame_size < b.frame_size;
  if (a.page_size != b.page_size) return a.page_size < b.page_size;
  if (a.strategy_name != b.strategy_name) return a.strategy_name < b.strategy_name;
  if (a.line != b.line) return a.line < b.line;
  return false;
}

void PagingSimulator::ShowStats() {
  std::sort(stats.begin(), stats.end(), IndicatorComparator);
  for (const auto &indicator : stats) {
    std::cout << "Frame: " << indicator.frame_size << ", Page: " << indicator.page_size << ", Strategy: "
              << indicator.strategy_name << ", Line: " << indicator.line << ", Page fault: " << indicator.page_fault
              << "\n";
  }
}
void PagingSimulator::Reset() {
  cur_page_fault_ = 0;
  frame_.Reset();
  page_table_.Reset();
  start_time = std::chrono::system_clock::now();
}
void PagingSimulator::SetFrameSize(uint32_t size) {
  frame_.SetFrameSize(size);
}
void PagingSimulator::SetPageTableSize(uint32_t size) {
  page_table_.SetPageTableSize(size);
}
void PagingSimulator::SetInput(std::string &&file_name) {
  input_file_ = std::move(file_name);
}
void PagingSimulator::SetOutputLineFrequency(uint32_t freq) {
  output_line_frequency_ = freq;
}
std::vector<Indicator> PagingSimulator::GetStats() {
  std::sort(stats.begin(), stats.end(), IndicatorComparator);
  return stats;
}
void PagingSimulator::SetStrategyPeriod(uint32_t period) {
  strategy_->SetPeriod(period);
}

}

