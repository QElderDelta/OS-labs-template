#include "lab3.h"

#include <iostream>

int main() {
    int n, m, threadCount;
    std::cin >> n >> m >> threadCount;

    TMatrix lhs(n, std::vector<int>(m));
    TMatrix rhs(n, std::vector<int>(m));

    auto readMatrix = [n, m](TMatrix& matrix) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < m; ++j) {
                std::cin >> matrix[i][j];
            }
        }
    };

    readMatrix(lhs);
    readMatrix(rhs);

    auto result = SumMatrices(lhs, rhs, threadCount);

    for(const auto& row : result) {
        for(int i : row) {
            std::cout << i << ' ';
        }
        std::cout << '\n';
    }
}
