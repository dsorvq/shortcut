#include <iostream>
#include <vector>
#include <cassert>
#include <random>

#include "shortcut.hpp"
#include "timer-guard.hpp"

int main() {
#ifdef TEST
  constexpr int n = 3;
  const matrix d  = {
    { 0, 8, 2 }, 
    { 1, 0, 9 },
    { 4, 5, 0 },
  };
  assert(d.size() == n);
  assert(d[0].size() == n);
  
  auto result = shortcut(d);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << result[i][j] << " ";
    }
    std::cout << "\n";
  }
#else
  constexpr int n = 2000;
  matrix d(n, matrix_row(n));

  // Fill d with random values
  std::random_device rd;
  std::default_random_engine re(rd());
  std::uniform_real_distribution<float> ud(0.0, 1.0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      d[i][j] = ud(re);
    }
  }
 
  // Perfrom algorithm
  {
    TimerGuard tg("time:");
    auto result = baseline(d);
  }

#endif
} 

