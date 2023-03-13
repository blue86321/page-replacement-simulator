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
  std::vector frames = std::vector<int>{2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};
  for (const auto &frame_size : frames) {
    paging::PagingSimulator paging_simulator(1024, frame_size);
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
