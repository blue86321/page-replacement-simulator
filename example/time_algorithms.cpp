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


void TimeAlgo(std::string_view strategy_str) {
  paging::PagingSimulator paging_simulator(PAGE, FRAME);
  paging_simulator.SetStrategyPeriod(100);
  paging_simulator.SetInputModifyPercent(0);
  paging_simulator.SetInput(INPUT_FILE);
  paging_simulator.GenerateInputIfNotExist();

  double seconds = 0;
  if (strategy_str == "FIFO") {
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Fifo>());
  } else if (strategy_str == "LRU") {
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Lru>());
  } else if (strategy_str == "Aging") {
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Aging>());
  } else if (strategy_str == "Clock") {
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Clock>());
  } else if (strategy_str == "NRU") {
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Nru>());
  }
  for (int i = 0; i < LOOP; i ++) {
    paging_simulator.Run();
    auto stats = paging_simulator.GetStats();
    seconds += stats[stats.size() - 1].time_lapse.count();
  }
  std::cout
    << "Page: " << PAGE
    << ", Frame: " << FRAME
    << ", Strategy: " << strategy_str
    << ", Loop: " << LOOP
    << ", Time: " << seconds << "\n";
}


int main() {
  TimeAlgo("FIFO");
  TimeAlgo("LRU");
  TimeAlgo("Aging");
  TimeAlgo("Clock");
  TimeAlgo("NRU");
  return 0;
}
