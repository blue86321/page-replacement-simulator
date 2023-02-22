#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Fifo.h"
#include "paging/strategy/Lru.h"
#include "paging/strategy/Aging.h"
#include "paging/strategy/Clock.h"
#include "paging/strategy/Nru.h"

int main() {
  paging::PagingSimulator paging_simulator(1024, 128);
  paging_simulator.SetInput(INPUT_FILE);
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
  paging_simulator.SetFrameSize(8);
  paging_simulator.SetPageTableSize(64);
  paging_simulator.Run();
  paging_simulator.ShowStats();
  return 0;
}
