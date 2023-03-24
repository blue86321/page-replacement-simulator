#include <iostream>
#include <fstream>
#include "paging/PagingSimulator.h"
#include "paging/strategy/Aging.h"
#include "Config.h"
#include "paging/strategy/Fifo.h"
#include "paging/strategy/Lru.h"
#include "paging/strategy/Clock.h"
#include "paging/strategy/Nru.h"
#include "paging/strategy/WsClock.h"

int main() {
  paging::PagingSimulator paging_simulator(PAGE_SIZE, FRAME_SIZE);
  paging_simulator.SetInputPrefix(TEST_INPUT_FILE);
  paging_simulator.SetOutputLineFrequency(TEST_OUTPUT_LINE_FREQUENCY);
  paging_simulator.SetStrategyPeriod(100);
  paging_simulator.GenerateUniformDistInputIfNotExist();
  paging_simulator.SetStrategyVerbose(true);
  std::cout << "========================= FIFO =========================\n";
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Fifo>());
  paging_simulator.Run();
  std:: cout << "----------- Page fault: " << paging_simulator.GetPageFault() << " -----------\n";
  std::cout << "\n\n\n\n\n";
  std::cout << "========================= LRU =========================\n";
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Lru>());
  paging_simulator.Run();
  std:: cout << "----------- Page fault: " << paging_simulator.GetPageFault() << " -----------\n";
  std::cout << "\n\n\n\n\n";
  std::cout << "========================= Clock =========================\n";
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Clock>());
  paging_simulator.Run();
  std:: cout << "----------- Page fault: " << paging_simulator.GetPageFault() << " -----------\n";
  std::cout << "\n\n\n\n\n";
  std::cout << "========================= Aging =========================\n";
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Aging>());
  paging_simulator.SetStrategyPeriod(1);
  paging_simulator.Run();
  std:: cout << "----------- Page fault: " << paging_simulator.GetPageFault() << " -----------\n";
  paging_simulator.SetStrategyPeriod(100);
  std::cout << "\n\n\n\n\n";
  std::cout << "========================= NRU =========================\n";
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::Nru>());
  paging_simulator.Run();
  std:: cout << "----------- Page fault: " << paging_simulator.GetPageFault() << " -----------\n";
  std::cout << "\n\n\n\n\n";
  std::cout << "========================= WSClock =========================\n";
  paging_simulator.SetStrategy(std::make_unique<paging::strategy::WsClock>());
  paging_simulator.Run();
  std:: cout << "----------- Page fault: " << paging_simulator.GetPageFault() << " -----------\n";
}
