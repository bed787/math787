#include "Matrix.hpp"
#include <iostream>
#include "Permutations.hpp"

using namespace math787;

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> result = getPermutations(n);
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[i].size(); j++) {
            std::cout << result[i][j] << " ";
        }
        std::cout << "\n";
    }
    return 0;
}