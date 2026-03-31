#include "Matrix.hpp"
#include <iostream>

int main() {


    std::cout << "Enter rows and cols: ";
    size_t rows, cols;
    std::cin >> rows >> cols;

    std::cout << "Enter " << rows * cols << " elements (row by row):" << std::endl;
    std::vector<double> values(rows * cols);
    for (size_t i = 0; i < rows * cols; i++) {
        std::cin >> values[i];
    }

    math787::Matrix m(rows, cols, values);

    std::cout << "\nYour matrix:" << std::endl;
    std::cout << m << std::endl;

    std::cout << "Transpose:" << std::endl;
    std::cout << m.transpose() << std::endl;

    if (rows == cols) {
        std::cout << "Identity " << rows << "x" << rows << ":" << std::endl;
        std::cout << math787::Matrix::identity(rows) << std::endl;

        std::cout << "M * Identity:" << std::endl;
        std::cout << m * math787::Matrix::identity(rows) << std::endl;

        std::cout << "Determinant: " << m.determinant() << std::endl;
    }

    return 0;
}