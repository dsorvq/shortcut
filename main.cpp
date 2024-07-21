#include <iostream>
#include <vector>
#include <cassert>
#include <random>

#include "shortcut.hpp"
#include "timer-guard.hpp"

void test_correctness();
void test_performance(auto alorithm, int n);

int main() {
#ifdef TEST
  test_correctness();
#else
  test_performance(shortcut, 2000);
#endif
} 

matrix get_random_square_matrix(int n) {
  matrix mat(n, matrix_row(n));

  std::random_device rd;
  std::default_random_engine re(rd());
  std::uniform_real_distribution<float> ud(0.0, 1.0);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      mat[i][j] = ud(re);
    }
  }

  return mat; 
}

void test_correctness() {
  // just some sanity checks

  {
    constexpr int n = 3;
    const matrix d  = {
      { 0, 8, 2 }, 
      { 1, 0, 9 },
      { 4, 5, 0 },
    };
    assert(d.size() == n);
    assert(d[0].size() == n);
    
    assert(baseline(d) == baseline(d)); 
  }
 
  auto test_for_n = [](int n, int iterations=10) {
    for (int i = 0; i < iterations; ++i) {
      auto mat = get_random_square_matrix(n);
      auto a = shortcut(mat);
      auto b = baseline(mat);
      assert(a == b);
    }
  };

  test_for_n(3);
  test_for_n(4);
}

void test_performance(auto alorithm, int n) {
  auto mat = get_random_square_matrix(n);

  {
    TimerGuard tg("time:");
    auto result = alorithm(mat);
  }
}
