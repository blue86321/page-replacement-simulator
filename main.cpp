#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Fifo.h"
#include "paging/strategy/Lru.h"

int main() {
  paging::PagingSimulator paging_simulator;
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Fifo>());
  paging_simulator.Run();
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Lru>());
  paging_simulator.Run();
  paging_simulator.ShowStats();
  return 0;
}
