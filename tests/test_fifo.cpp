#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Fifo.h"
#include "paging/strategy/Lru.h"
#include "paging/strategy/Aging.h"
#include "paging/strategy/Clock.h"
#include "paging/strategy/Nru.h"


#define TEST_INPUT_FILE "tests/test_page_reference.txt"

int main() {
  paging::PagingSimulator paging_simulator(8, 4);
  paging_simulator.SetInput(TEST_INPUT_FILE);
  paging_simulator.SetOutputLineFrequency(20);
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Fifo>());
  paging_simulator.Run();
  paging_simulator.ShowStats();
  return 0;
}
