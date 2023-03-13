#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Fifo.h"
#include "paging/strategy/Lru.h"
#include "paging/strategy/Aging.h"
#include "paging/strategy/Clock.h"
#include "paging/strategy/Nru.h"
#include "paging/strategy/WsClock.h"
#include <vector>

int main() {
  std::vector pages = std::vector<int>{128, 256, 512, 1024, 2048};
  for (const auto &page_size : pages) {
    paging::PagingSimulator paging_simulator(page_size, 128);
    paging_simulator.SetStrategyPeriod(100);
    paging_simulator.SetInputModifyPercent(0);
    paging_simulator.SetInputPrefix(paging::GetHotPageInputPrefix());
    paging_simulator.GenerateHotPageAccessInputIfNotExist();

    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Fifo>());
    paging_simulator.Run();
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Lru>());
    paging_simulator.Run();
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Aging>());
    paging_simulator.Run();
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Clock>());
    paging_simulator.Run();
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Nru>());
    paging_simulator.Run();
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::WsClock>());
    paging_simulator.Run();
    paging_simulator.ShowStats();
  }
  return 0;
}
