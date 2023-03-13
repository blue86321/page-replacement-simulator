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
  paging::PagingSimulator paging_simulator(1024, 128);
  paging_simulator.SetStrategyPeriod(100);
  paging_simulator.SetInputModifyPercent(0);
  paging_simulator.SetInputPrefix("input/page_ref_sequence_");
  paging_simulator.GenerateSequenceInputIfNotExist();

  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Fifo>());
  paging_simulator.Run();
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Lru>());
  paging_simulator.Run();
  // if `period` > `frame_size`, all elements in priority queue with same `age`
  // cannot guarantee which page to be swapped out, so it could lead to page hit.
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Aging>());
  paging_simulator.Run();
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Clock>());
  paging_simulator.Run();
  // if `period` < `frame_size`, all elements `reference` will be reset on period, the rest will not (`frame_size` - `period`)
  // so it could lead to page hit because replacement care about not referenced data.
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Nru>());
  paging_simulator.Run();
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::WsClock>());
  paging_simulator.Run();
  paging_simulator.ShowStats();
  return 0;
}
