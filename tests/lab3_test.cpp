#include <gtest/gtest.h>

#include <lab3.h>
#include <utils.h>

#include <chrono>


namespace {
    TMatrix GenerateMatrix(int n, int m) {
        TMatrix result(n, std::vector<int>(m));

        std::srand(std::time(nullptr));

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                result[i][j] = std::rand() % 100;
            }
        }

        return result;
    }
}


bool operator==(const TMatrix& lhs, const TMatrix& rhs) {
    if(lhs.size() != rhs.size()) {
        return false;
    }

    for(int i = 0; i < isize(lhs); ++i) {
        if(lhs[i].size() != rhs[i].size()) {
            return false;
        }

        for(int j = 0; j < isize(lhs); ++j) {
            if(lhs[i][j] != rhs[i][j]) {
                return false;
            }
        }
    }

    return true;
}

TEST(ThirdLabTests, SingleThreadYieldsCorrectResults) {
    EXPECT_EQ(SumMatrices(TMatrix{{1}}, TMatrix{{2}}, 1), TMatrix{{3}});

    EXPECT_EQ(SumMatrices(TMatrix{{1, 2}, {1, 2}}, TMatrix{{1, 3}, {4, 5}}, 1), (TMatrix{{2, 5}, {5, 7}}));

    EXPECT_EQ(SumMatrices(TMatrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},TMatrix{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 1),
              (TMatrix{{2, 4, 6}, {8, 10, 12}, {14, 16, 18}}));
}

TEST(ThirdLabTest, ThreadConfigurations) {
    auto performTestForGivenSize = [](int n, int m, int maxThreadCount) {
        auto m1 = GenerateMatrix(n, m);
        auto m2 = GenerateMatrix(n, m);
        auto result = SumMatrices(m1, m2, 1);

        for(int i = 2; i < maxThreadCount; ++i) {
            EXPECT_EQ(SumMatrices(m1, m2, i), result);
        }
    };

    performTestForGivenSize(3, 3, 10);
    performTestForGivenSize(10, 10, 10);
    performTestForGivenSize(100, 100, 15);
}

TEST(ThirdLabTest, PerfomanceTest) {
    auto getAvgTime = [](int threadCount) {
        auto m1 = GenerateMatrix(3000, 3000);
        auto m2 = GenerateMatrix(3000, 3000);

        constexpr int runsCount = 10;

        double avg = 0;

        for(int i = 0; i < runsCount; ++i) {
            auto begin = std::chrono::high_resolution_clock::now();
            SumMatrices(m1, m2, threadCount);
            auto end = std::chrono::high_resolution_clock::now();
            avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        }

        return avg / runsCount;
    };

    auto singleThread = getAvgTime(1);
    auto multiThread = getAvgTime(4);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for 4 threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}