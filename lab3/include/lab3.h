#ifndef OS_LABS_LAB3_H
#define OS_LABS_LAB3_H

#include <vector>

using TMatrix = std::vector<std::vector<int>>;

TMatrix SumMatrices(const TMatrix& lhs, const TMatrix& rhs, int threadCount);

#endif //OS_LABS_LAB3_H
