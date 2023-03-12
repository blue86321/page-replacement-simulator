#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Fifo.h"
#include "paging/strategy/Lru.h"
#include "paging/strategy/Aging.h"
#include "paging/strategy/Clock.h"
#include "paging/strategy/Nru.h"
#include <vector>

struct Params {
  int small_block_cnt;
  int page_per_block;
  int interval;
};

static std::string GetInputFileName(int small_block_cnt, int page_per_block, int interval) {
  return "input/page_reference_" + std::to_string(small_block_cnt) + "_block_" + std::to_string(page_per_block)
      + "_page_" + std::to_string(interval) + "_ref";
}

int main() {
  paging::PagingSimulator paging_simulator(1024, 64);
  paging_simulator.SetStrategyPeriod(100);
  paging_simulator.SetInputModifyPercent(0);

  std::vector<Params> params;
  params.push_back({1, 5, 20});
  params.push_back({5, 5, 20});
  params.push_back({10, 5, 20});
  params.push_back({20, 5, 20});
  params.push_back({50, 5, 20});
  for (Params &p : params) {
    std::cout
      << "\n\n\n"
      << "================"
      << "Blocks: " << p.small_block_cnt
      << ", Page per block: " << p.page_per_block
      << ", Interval: " << p.interval
      << "================"
      << "\n";
    paging_simulator.SetInput(GetInputFileName(p.small_block_cnt, p.page_per_block, p.interval));
    paging_simulator.GenerateSmallPageFrequentAccessInputIfNotExist(p.small_block_cnt, p.page_per_block, p.interval);

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
    paging_simulator.ShowStats();
    paging_simulator.ClearStats();
  }
  return 0;
}
