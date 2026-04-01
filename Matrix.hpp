#pragma once
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <iostream>

namespace math787 {

class Matrix {
private:
    std::vector<double> data_;
    size_t rows_;
    size_t cols_;

public:
    // ===== Constructors & Factory Methods =====

    Matrix(size_t rows, size_t cols, std::vector<double> values) {
        if (values.size() != rows * cols) {
            throw std::invalid_argument("Data size doesn't match matrix dimension");
        }
        rows_ = rows;
        cols_ = cols;
        data_ = values;
    }

    static Matrix zeroes(size_t rows, size_t cols) {
        return Matrix(rows, cols, std::vector<double>(rows * cols));
    }

    static Matrix identity(size_t size) {
        std::vector<double> values(size * size);
        for (size_t i = 0; i < size * size; i += size + 1) {
            values[i] = 1.0;
        }
        return Matrix(size, size, values);
    }

    // ===== Accessors =====

    size_t getRows() const { return rows_; }
    size_t getCols() const { return cols_; }

    const std::vector<double>& getVector() const { return data_; }

    double getElement(size_t i, size_t j) const {
        if (i * cols_ + j >= data_.size()) {
            throw std::invalid_argument("Index outside the matrix");
        }
        return data_[i * cols_ + j];
    }

    // ===== Properties =====

    double getTrace() const {
        if (rows_ != cols_) {
            throw std::invalid_argument("Trace is defined only for square matrices");
        }
        double trace = 0;
        for (size_t i = 0; i < rows_; i++) {
            trace += data_[i * (cols_ + 1)];
        }
        return trace;
    }

    double getTraceProduct() const {
        if (rows_ != cols_) {
            throw std::invalid_argument("Trace product is defined only for square matrices");
        }
        double trace_product = 1;
        for (size_t i = 0; i < rows_; i++) {
            trace_product *= data_[i * (cols_ + 1)];
        }
        return trace_product;
    }

    // ===== Transformations =====

    Matrix transpose() const {
        std::vector<double> values;
        values.reserve(rows_ * cols_);
        for (size_t i = 0; i < cols_; i++) {
            for (size_t j = 0; j < rows_; j++) {
                values.push_back(data_[j * cols_ + i]);
            }
        }
        return Matrix(cols_, rows_, values);
    }

    Matrix reverse() const {

    }

    // ===== Determinant =====

    double determinantLeibnitz() {


    }

    double determinantGauss() const {
        if (cols_ != rows_) {
            throw std::invalid_argument("Determinant is defined only for square matrices");
        }

        std::vector<double> temp = data_;
        for (size_t col = 0; col < rows_; col++) {
            double diagonal = temp[col * cols_ + col];
            if (diagonal == 0) {
                return 0.0;
            }
            for (size_t row = col + 1; row < rows_; row++) {
                double alpha = temp[row * cols_ + col] / diagonal;
                for (size_t j = 0; j < cols_; j++) {
                    temp[row * cols_ + j] -= temp[col * cols_ + j] * alpha;
                }
            }
        }

        double det = 1.0;
        for (size_t i = 0; i < rows_; i++) {
            det *= temp[i * cols_ + i];
        }
        return det;
    }

    // ===== Operators =====

    Matrix operator+(const Matrix& other) const {
        if (other.rows_ != rows_ || other.cols_ != cols_) {
            throw std::invalid_argument("Matrix sizes don't match for addition");
        }
        std::vector<double> values;
        values.reserve(rows_ * cols_);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                values.push_back(getElement(i, j) + other.getElement(i, j));
            }
        }
        return Matrix(rows_, cols_, values);
    }

    Matrix operator-(const Matrix& other) const {
        if (other.rows_ != rows_ || other.cols_ != cols_) {
            throw std::invalid_argument("Matrix sizes don't match for subtraction");
        }
        std::vector<double> values;
        values.reserve(rows_ * cols_);
        for (size_t i = 0; i < rows_; i++) {
            for (size_t j = 0; j < cols_; j++) {
                values.push_back(getElement(i, j) - other.getElement(i, j));
            }
        }
        return Matrix(rows_, cols_, values);
    }

    Matrix operator*(const Matrix& other) const {
        if (cols_ != other.rows_) {
            throw std::invalid_argument("Matrix sizes don't match for multiplication");
        }
        size_t rows = rows_;
        size_t cols = other.cols_;
        std::vector<double> values;
        values.reserve(rows * cols);
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                double sum = 0;
                for (size_t k = 0; k < cols_; k++) {
                    sum += getElement(i, k) * other.getElement(k, j);
                }
                values.push_back(sum);
            }
        }
        return Matrix(rows, cols, values);
    }

    // ===== Utility =====

    static int factorial(int n) {
        if (n < 0) {
            throw std::invalid_argument("Argument of factorial < 0");
        }
        int result = 1;
        for (int i = 2; i <= n; i++) {
            result *= i;
        }
        return result;
    }

};

// ===== Stream Output =====

inline std::ostream& operator<<(std::ostream& os, const Matrix& m) {
    for (size_t i = 0; i < m.getRows(); i++) {
        for (size_t j = 0; j < m.getCols(); j++) {
            os << m.getElement(i, j) << " ";
        }
        os << "\n";
    }
    return os;
}

} // namespace math787