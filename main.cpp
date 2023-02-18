#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Fifo.h"

int main() {
  paging::PagingSimulator paging_simulator;
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Fifo>());
  paging_simulator.Run();
  return 0;
}
