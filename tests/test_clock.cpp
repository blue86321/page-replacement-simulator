#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Clock.h"
#include "Config.h"


int main() {
  paging::PagingSimulator paging_simulator(PAGE_SIZE, FRAME_SIZE);
  paging_simulator.SetInput(TEST_INPUT_FILE);
  paging_simulator.SetOutputLineFrequency(TEST_OUTPUT_LINE_FREQUENCY);
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Clock>());
  paging_simulator.Run();
  paging_simulator.ShowStats();
  auto stats = paging_simulator.GetStats();
  if (stats[0].page_fault == 13) {
    std::cout << testing::PassMsg << "\n";
  } else {
    std::cout << testing::FailMsg << "\n";
  }
}
