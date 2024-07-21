#pragma once

#include <random>
#include <string>
#include <iostream>
#include <chrono>

class TimerGuard {
public:
  TimerGuard(std::string_view message = "", std::ostream& out = std::cout)
    : start(std::chrono::high_resolution_clock::now())
    , outMessage(message)
    , outStream(out)
  { }

  ~TimerGuard() {
    auto end = std::chrono::high_resolution_clock::now();  // конец - вызов деструктора
    std::chrono::duration<double> diff = end - start;
    // auto diffns = std::chrono::duration_cast<std::chrono::nanoseconds> (diff);
    auto diffms = std::chrono::duration_cast<std::chrono::milliseconds> (diff);
    outStream << outMessage << " " 
      // << diffns.count() << "ns" << " == "
      << diffms.count() << "ms" << " == "
      << diff.count() << "s" << "\n";
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> start;
  std::string_view outMessage;
  std::ostream& outStream;
};
