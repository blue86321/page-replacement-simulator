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

struct Params {
  int small_block_cnt;
  int page_per_block;
  int interval;
};

int main() {
  paging::PagingSimulator paging_simulator(1024, 64);
  paging_simulator.SetStrategyPeriod(100);
  paging_simulator.SetInputModifyPercent(0);

  std::vector<Params> params;
  params.push_back({1, 20, 10});
  params.push_back({1, 20, 20});
  params.push_back({1, 20, 30});
  params.push_back({1, 20, 40});
  params.push_back({1, 20, 50});
  for (Params &p : params) {
    std::cout
      << "\n\n\n"
      << "================"
      << "Blocks: " << p.small_block_cnt
      << ", Page per block: " << p.page_per_block
      << ", Interval: " << p.interval
      << "================"
      << "\n";
    paging_simulator.SetInputPrefix(paging::GetHotPageInputPrefix(p.small_block_cnt, p.page_per_block, p.interval));
    paging_simulator.GenerateHotPageAccessInputIfNotExist(p.small_block_cnt, p.page_per_block, p.interval);

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
    paging_simulator.ClearStats();
  }
  return 0;
}
