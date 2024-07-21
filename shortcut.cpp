#include <limits>

#include "shortcut.hpp"

matrix shortcut(const matrix& distances) {
  const int n = distances.size();
  constexpr int multiple = 20;
  constexpr auto infty = std::numeric_limits<float>::infinity();

  int npadded = ((n + multiple + 1) / multiple) * multiple;

  matrix trasnposed_padded(n, matrix_row(npadded, infty));
  matrix distances_padded(n, matrix_row(npadded, infty));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      trasnposed_padded[j][i] = distances[i][j];
      distances_padded[i][j] = distances[i][j];
    }
  }
  
  matrix result(n, matrix_row(n));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {

      float path_ij[multiple];
      for (int p = 0; p < multiple; ++p) {
        path_ij[p] = infty;
      }

      for (int k = 0; k < npadded; k += multiple) {
        for (int p = 0; p < multiple; ++p) {
          auto x = distances_padded[i][k + p];
          auto y = trasnposed_padded[j][k + p];
          auto z = x + y;
          path_ij[p] = std::min(path_ij[p], z);
        }
      }

      float v = infty;
      for (int p = 0; p < multiple; ++p) {
        v = std::min(v, path_ij[p]);
      }
      result[i][j] = v;
    }
  }

  return result;
}
