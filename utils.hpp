#pragma once
#include <stdexcept>

namespace math787 {

    inline int factorial(int n) {
        if (n < 0) {
            throw std::invalid_argument("Argument of factorial < 0");
        }
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

} // namespace math787