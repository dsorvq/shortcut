#include <vector>

using matrix = std::vector<std::vector<float>>;
using matrix_row = std::vector<float>;

matrix shortcut(const matrix& distances);
matrix baseline(const matrix& distances);
