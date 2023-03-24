//
// Created by Chunwei Chang on 2/16/23.
//

#include "paging/PagingSimulator.h"

#include "paging/util/InputGenerator.h"

namespace paging {
void PagingSimulator::SetStrategy(std::unique_ptr<strategy::IStrategy> &&strategy) {
  // because `strategy` is a rvalue, we can "steal" memory from it
  strategy_ = std::move(strategy);
  strategy_->SetVerbose(strategy_verbose_);
}

std::string PagingSimulator::GetFileName() {
  return input_prefix_ + std::to_string(page_table_.Size()) + "p_" + std::to_string(modify_percent_) + "m.txt";
}

void PagingSimulator::GenerateUniformDistInputIfNotExist() {
  util::InputGenerator::GenerateUniformDistInputIfNotExist(GetFileName(),
                                                           page_table_.Size(),
                                                           modify_percent_,
                                                           PAGE_REF_LINES);
}

void PagingSimulator::GenerateHotPageAccessInputIfNotExist(int small_block_cnt, int page_per_block, int interval) {
  util::InputGenerator::GenerateHotPageAccessInputIfNotExist(GetFileName(),
                                                             page_table_.Size(),
                                                             modify_percent_,
                                                             PAGE_REF_LINES,
                                                             small_block_cnt,
                                                             page_per_block,
                                                             interval);
}

void PagingSimulator::GenerateSequenceInputIfNotExist() {
  util::InputGenerator::GenerateSequenceInputIfNotExist(GetFileName(),
                                                        page_table_.Size(),
                                                        modify_percent_,
                                                        PAGE_REF_LINES);
}

void PagingSimulator::Run() {
  // 1.Reset all data
  Reset();

  // 2.Read each line
  std::ifstream input;
  input.open(GetFileName());
  size_t line_counter = 0;
  if (input.is_open()) {
    std::string line;
    std::getline(input, line);  // discard header
    while (std::getline(input, line)) {
      size_t delimiterIdx = line.find(' ');
      int page_no = stoi(line.substr(0, delimiterIdx));
      bool is_modify = stoi(line.substr(delimiterIdx));
      // 3.AccessMemory by page number
      AccessMemory(page_no, is_modify);
      // 4.Keep the stats
      line_counter++;
      if (line_counter % output_line_frequency_ == 0) {
        auto now = std::chrono::system_clock::now();
        stats_.emplace_back(page_table_.Size(),
                            frame_.Capacity(),
                            strategy_->GetName(),
                            line_counter,
                            cur_page_fault_,
                            now - start_time_);
      }
    }
    input.close();
  }
}

void PagingSimulator::AccessMemory(int page_no, bool is_modify) {
  if (page_table_.IsValid(page_no)) {
    // page hit
    if (is_modify) {
      page_table_.Modify(page_no);
    }
    // reference the page no matter it is a modify command or not
    page_table_.Reference(page_no);
    strategy_->AfterReference(frame_, page_table_, page_no);
  } else {
    // page fault
    cur_page_fault_++;
    if (frame_.IsFull()) {
      // page replacement
      int old_page_no = strategy_->GetReplacePage(frame_, page_table_);
      Replace(old_page_no, page_no, is_modify);
      strategy_->AfterReplace(frame_, page_table_, old_page_no, page_no);
    } else {
      // frame is not full, spot a place in the frame
      int frame_no = frame_.UseOneFrame(page_no);
      SetupNewPage(page_no, frame_no, is_modify);
      strategy_->AfterNewPage(frame_, page_table_, page_no);
    }
  }
}

void PagingSimulator::Replace(int old_page_no, int new_page_no, bool is_modify) {
  // only operate `PageTable` and `FrameTable`, `Strategy` will call later
  page_table_.Invalidate(old_page_no);
  int frame_no = page_table_.GetFrameNumber(old_page_no);
  PageEntry page_entry(frame_no, is_modify);
  page_table_.Set(new_page_no, page_entry);
  frame_.SetFrame(frame_no, new_page_no);
}

void PagingSimulator::SetupNewPage(int page_no, int frame_no, bool is_modify) {
  // only operate `PageTable` and `FrameTable`, `Strategy` will call later
  PageEntry page_entry(frame_no, is_modify);
  page_table_.Set(page_no, page_entry);
}

bool IndicatorComparator(const Indicator &a, const Indicator &b) {
  // use to sort stats
  if (a.frame_size != b.frame_size) return a.frame_size < b.frame_size;
  if (a.page_size != b.page_size) return a.page_size < b.page_size;
  if (a.strategy_name != b.strategy_name) return a.strategy_name < b.strategy_name;
  if (a.line != b.line) return a.line < b.line;
  return false;
}

void PagingSimulator::ShowStats() {
  std::sort(stats_.begin(), stats_.end(), IndicatorComparator);
  for (const auto &indicator : stats_) {
    std::cout << "Frame: " << indicator.frame_size << ", Page: " << indicator.page_size << ", Strategy: "
              << indicator.strategy_name << ", Modify Pct: " << modify_percent_ << "%" << ", Period: "
              << strategy_->GetPeriod() << ", Line: " << indicator.line << ", Page fault: " << indicator.page_fault
              << ", Time: " << indicator.time_lapse.count() << "\n";
  }
}

void PagingSimulator::Reset() {
  cur_page_fault_ = 0;
  frame_.Reset();
  page_table_.Reset();
  strategy_->Reset();
  start_time_ = std::chrono::system_clock::now();
}

void PagingSimulator::SetFrameSize(int size) {
  frame_.SetFrameSize(size);
}

void PagingSimulator::SetPageTableSize(int size) {
  page_table_.SetPageTableSize(size);
}

void PagingSimulator::SetInputPrefix(std::string &&prefix) {
  input_prefix_ = std::move(prefix);
}

void PagingSimulator::SetOutputLineFrequency(int freq) {
  output_line_frequency_ = freq;
}
std::vector<Indicator> PagingSimulator::GetStats() {
  std::sort(stats_.begin(), stats_.end(), IndicatorComparator);
  return stats_;
}

void PagingSimulator::SetStrategyPeriod(int period) {
  strategy_->SetPeriod(period);
}

void PagingSimulator::SetInputModifyPercent(int modify_percent) {
  modify_percent_ = modify_percent;
}
void PagingSimulator::ClearStats() {
  std::vector<Indicator>().swap(stats_);
}
void PagingSimulator::SetStrategyVerbose(bool verbose) {
  strategy_verbose_ = verbose;
  strategy_->SetVerbose(strategy_verbose_);
}
int PagingSimulator::GetPageFault() {
  return cur_page_fault_;
}
}

