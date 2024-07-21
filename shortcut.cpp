#include <limits>

#include "shortcut.hpp"

matrix shortcut(const matrix& distances) {
  const int n = distances.size();

  matrix trasnposed(n, matrix_row(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      trasnposed[j][i] = distances[i][j];
    }
  }
  
  matrix result(n, matrix_row(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      auto path_ij = std::numeric_limits<float>::infinity();
      for (int k = 0; k < n; ++k) {
        auto x = distances[i][k];
        auto y = trasnposed[j][k];
        auto z = x + y;
        path_ij = std::min(path_ij, z);
      }
      result[i][j] = path_ij;
    }
  }

  return result;
}
