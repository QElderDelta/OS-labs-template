#include "lab3.h"
#include "utils.h"

#include <thread>


namespace {
    void SumGivenRows(const TMatrix& lhs, const TMatrix& rhs, TMatrix& result, int firstRow, int lastRow) {
        int m = isize(lhs);
        for(int i = firstRow; i < lastRow; ++i) {
            for(int j = 0; j < m; ++j) {
                result[i][j] = lhs[i][j] + rhs[i][j];
            }
        }
    }
}

TMatrix SumMatrices(const TMatrix& lhs, const TMatrix& rhs, int threadCount) {
    TMatrix result(lhs.size(), std::vector<int>(lhs[0].size()));

    if(threadCount > 1) {
        int actualThreads = std::min(threadCount, isize(result));

        std::vector<std::thread> threads;
        threads.reserve(actualThreads);

        int rowsPerThread = isize(result) / actualThreads;

        for(int i = 0; i < isize(result); i += rowsPerThread) {
            if(i + rowsPerThread >= isize(result)) {
                threads.emplace_back(SumGivenRows, std::ref(lhs), std::ref(rhs), std::ref(result), i, isize(result));
            } else {
                threads.emplace_back(SumGivenRows, std::ref(lhs), std::ref(rhs), std::ref(result),
                                     i, i + rowsPerThread);
            }
        }

        for(auto& thread : threads) {
            thread.join();
        }
    } else {
        SumGivenRows(lhs, rhs, result, 0, lhs.size());
    }


    return result;
}

