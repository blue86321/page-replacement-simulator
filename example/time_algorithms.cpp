#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Fifo.h"
#include "paging/strategy/Lru.h"
#include "paging/strategy/Aging.h"
#include "paging/strategy/Clock.h"
#include "paging/strategy/Nru.h"
#include <unordered_map>
#include <string>

#define LOOP 100
#define PAGE 1024
#define FRAME 128

void TimeAlgo(std::unique_ptr<paging::strategy::IStrategy> strategy_ptr) {
  double seconds = 0;
  uint32_t page_faults = 0;
  std::string strategy_str = strategy_ptr->GetName();

  paging::PagingSimulator paging_simulator(PAGE, FRAME);
  paging_simulator.SetStrategyPeriod(100);
  paging_simulator.SetInputModifyPercent(0);
  paging_simulator.SetInput(INPUT_FILE);
  paging_simulator.GenerateInputIfNotExist();
  paging_simulator.SetStrategy(std::move(strategy_ptr));
  for (int i = 0; i < LOOP; i++) {
    paging_simulator.Run();
    auto stats = paging_simulator.GetStats();
    seconds += stats[stats.size() - 1].time_lapse.count();
    page_faults = stats[stats.size() - 1].page_fault;
  }

  std::cout
      << "Page: " << PAGE
      << ", Frame: " << FRAME
      << ", Strategy: " << strategy_str
      << ", Loop: " << LOOP
      << ", Time: " << seconds
      << ", each page fault: " << page_faults
      << "\n";
}

int main() {
  TimeAlgo(std::move(std::make_unique<paging::strategy::Fifo>()));
  TimeAlgo(std::move(std::make_unique<paging::strategy::Lru>()));
  TimeAlgo(std::move(std::make_unique<paging::strategy::Aging>()));
  TimeAlgo(std::move(std::make_unique<paging::strategy::Clock>()));
  TimeAlgo(std::move(std::make_unique<paging::strategy::Nru>()));
  return 0;
}
