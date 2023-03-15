#include "paging/PagingSimulator.h"
#include "paging/strategy/Aging.h"
#include "paging/strategy/Clock.h"
#include "paging/strategy/Nru.h"
#include "paging/strategy/WsClock.h"
#include <vector>

int main() {
  std::vector periods = std::vector<int>{2, 4, 8, 16, 32, 64, 128, 256};
  for (const auto &period : periods) {
    paging::PagingSimulator paging_simulator(1024, 128);
    paging_simulator.SetStrategyPeriod(period);
    paging_simulator.SetInputModifyPercent(0);
    paging_simulator.SetInputPrefix(paging::GetHotPageInputPrefix());
    paging_simulator.GenerateHotPageAccessInputIfNotExist();

    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Aging>());
    paging_simulator.Run();
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Clock>());
    paging_simulator.Run();
    paging_simulator.SetStrategy(std::make_unique<paging::strategy::Nru>());
    paging_simulator.Run();
    paging_simulator.ShowStats();
  }
  return 0;
}
