#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Nru.h"
#include <vector>

int main() {
  std::vector modify_pct = std::vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
  for (const auto &m : modify_pct) {
    paging::PagingSimulator paging_simulator(1024, 128);
    paging_simulator.SetStrategyPeriod(100);
    paging_simulator.SetInputModifyPercent(m);
    paging_simulator.SetInput(INPUT_FILE);
    paging_simulator.GenerateInputIfNotExist();

    // only NRU take modify into account
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Nru>());
    paging_simulator.Run();
    paging_simulator.ShowStats();
  }
  return 0;
}
