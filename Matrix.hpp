#pragma once
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

        size_t getRows() const {
            return rows_;
        }

        size_t getCols() const {
            return cols_;
        }

        std::vector<double> getVector() {
            return data_;
        }

        double getTraceProduct() const {
            double trace_product = 0;
            for (size_t i = 0; i < rows_; i++) {
                trace_product *= data_[i * (cols_ + 1)];
            }

            return trace_product;
        }

        double getTrace() const {
            double trace = 0;
            for (size_t i = 0; i < rows_; i++) {
                trace += data_[i * (cols_ + 1)];
            }

            return trace;
        }

        double determinant() const {

            if (cols_ != rows_) {
                throw std::invalid_argument("There is no determinant for non-sqare matrix");
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

        Matrix reverse() const {

        }

        Matrix transpose() const {
            std::vector<double> values;
            for (size_t i = 0; i < cols_; i++) {
                for (size_t j = 0; j < rows_; j++) {
                    values.push_back(data_[j * cols_ + i]);
                }
            }
            return Matrix(cols_, rows_, values);
        }

        double getElement(size_t i, size_t j) const {
            if ((i * cols_ + j) >= data_.size()) {
                throw std::invalid_argument("Index outside the matrix");
            }
            return data_[i * cols_ + j];
        }

        static Matrix zeroes(size_t rows, size_t cols) {
            return Matrix(rows, cols, std::vector<double>(rows*cols));
        }

        static Matrix identity(size_t size) {
            std::vector<double> values(size * size);
            for (size_t i = 0; i < size * size; i += size + 1) {
                values[i]= 1.0;
            }
            return Matrix(size, size, values);
        }

        Matrix(size_t rows, size_t cols, std::vector<double> values) {
            if (values.size() != rows * cols) {
                throw std::invalid_argument("Data size doesn't  match matrix dimension");
            }

            rows_ = rows;
            cols_ = cols;
            data_ = values;

        }

        Matrix operator+(const Matrix& other) const {
            if (other.rows_ != rows_ || other.cols_ != cols_) {
                throw std::invalid_argument("The matrix sizes don't matches");
            }
            std::vector<double> values;
            for (size_t i = 0; i < rows_; i++) {
                for (size_t j = 0; j < cols_; j++) {
                    values.push_back(getElement(i, j) + other.getElement(i, j));
                }
            }
            return Matrix(rows_, cols_, values);
        }

        Matrix operator-(const Matrix& other) const {
            if (other.rows_ != rows_ || other.cols_ != cols_) {
                throw std::invalid_argument("The matrix sizes don't matches");
            }
            std::vector<double> values;
            for (size_t i = 0; i < rows_; i++) {
                for (size_t j = 0; j < cols_; j++) {
                    values.push_back(getElement(i, j) - other.getElement(i, j));
                }
            }
            return Matrix(rows_, cols_, values);
        }

        Matrix operator*(const Matrix& other) const {
            if (cols_ != other.rows_) {
                throw std::invalid_argument("The matrix sizes don't matches");
            }

            int rows = rows_;
            int cols = other.cols_;
            std::vector<double> values;

            for (size_t i = 0; i < rows; i++) {
                for (size_t j = 0; j < cols; j++) {
                    double current_element = 0;
                    for (size_t element = 0; element < cols_; element++) {
                        current_element += getElement(i, element) * other.getElement(element, j);
                    }
                    values.push_back(current_element);
                }
            }

            return Matrix(rows, cols, values);


        }
    };

    std::ostream& operator<<(std::ostream& os, const Matrix& m) {
        size_t rows = m.getRows();
        size_t cols = m.getCols();
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                os << m.getElement(i, j) << " ";
            }
            os << "\n";
        }
        return os;
    }



}