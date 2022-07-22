// MIT License

// Copyright (c) 2022 CLECIO JUNG <clecio.jung@gmail.com>

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __MATRIX_CPP
#define __MATRIX_CPP

#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "scalar.hpp"
#include "vector.hpp"

constexpr uint64_t matrix_iterations = 10000;
constexpr double matrix_precision = 1e-9;

template <typename Floating>
class Matrix {
   private:
    Floating *data;
    size_t _rows;
    size_t _cols;

   public:
    Matrix(void) : data(nullptr), _rows(0), _cols(0){};
    Matrix(const size_t rows, const size_t cols);
    Matrix(const Matrix &matrix);
    ~Matrix(void);
    size_t rows(void) const { return _rows; }
    size_t cols(void) const { return _cols; }
    Floating &operator()(const size_t row, const size_t col) const;
    Matrix operator+(const Matrix &matrix) const;
    Matrix operator-(const Matrix &matrix) const;
    Matrix operator*(const Floating scalar) const;
    Vector<Floating> operator*(const Vector<Floating> &vector) const;
    Matrix operator*(const Matrix &matrix) const;
    Matrix &operator*=(const Floating scalar);
    Matrix &operator=(const Floating value);
    Matrix &operator=(const Matrix &to_copy);
    bool operator==(const Matrix &matrix) const;
    bool operator!=(const Matrix &matrix) const;
    void resize(const size_t rows, const size_t cols);
    Matrix &random(const Floating min, const Floating max);
    std::string to_string(void) const;
    bool is_squared(void) const;
    bool is_symmetric(void) const;
    bool is_skew_symmetric(void) const;
    Floating trace(void) const;
    Floating determinant(void) const;
    Matrix transpose(void) const;
    Matrix symmetric(void) const;
    Matrix skew_symmetric(void) const;
    Matrix inverse(void) const;
    static Matrix identity(const size_t rows);
};

template <typename Floating>
Matrix<Floating>::Matrix(const size_t rows, const size_t cols) : data(nullptr), _rows(rows), _cols(cols) {
    if ((_rows != 0) && (_cols != 0)) {
        data = new Floating[_rows * _cols];
    }
}

template <typename Floating>
Matrix<Floating>::Matrix(const Matrix<Floating> &matrix) : data(nullptr), _rows(matrix._rows), _cols(matrix._cols) {
    if ((_rows != 0) && (_cols != 0)) {
        data = new Floating[_rows * _cols];
        for (size_t i = 0; i < _rows * _cols; i++) {
            data[i] = matrix.data[i];
        }
    }
}

template <typename Floating>
Matrix<Floating>::~Matrix(void) {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    _rows = 0;
    _cols = 0;
}

template <typename Floating>
Floating &Matrix<Floating>::operator()(const size_t row, const size_t col) const {
    if (row >= _rows) {
        throw std::runtime_error("Trying to access matrix in invalid row index!");
    }
    if (col >= _cols) {
        throw std::runtime_error("Trying to access matrix in invalid column index!");
    }
    return data[row * _cols + col];
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::operator+(const Matrix<Floating> &matrix) const {
    if ((_rows != matrix._rows) || (_cols != matrix._cols)) {
        throw std::runtime_error("Trying to sum matrices with different sizes!");
    }
    Matrix<Floating> result(_rows, _cols);
    for (size_t i = 0; i < (_rows * _cols); i++) {
        result.data[i] = data[i] + matrix.data[i];
    }
    return result;
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::operator-(const Matrix<Floating> &matrix) const {
    if ((_rows != matrix._rows) || (_cols != matrix._cols)) {
        throw std::runtime_error("Trying to subtract matrices with different sizes!");
    }
    Matrix<Floating> result(_rows, _cols);
    for (size_t i = 0; i < (_rows * _cols); i++) {
        result.data[i] = data[i] - matrix.data[i];
    }
    return result;
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::operator*(const Floating scalar) const {
    Matrix result(_rows, _cols);
    for (size_t i = 0; i < (_rows * _cols); i++) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

template <typename Floating>
Matrix<Floating> operator*(const Floating scalar, const Matrix<Floating> &matrix) {
    return (matrix * scalar);
}

template <typename Floating>
Vector<Floating> Matrix<Floating>::operator*(const Vector<Floating> &vector) const {
    if (_cols != vector.length()) {
        throw std::runtime_error("Multiplication of matrix and vector with incompatible lengths!");
    }
    Vector<Floating> result(_rows);
    result = static_cast<Floating>(0.0);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t k = 0; k < _cols; k++) {
            result[i] += this->operator()(i, k) * vector[k];
        }
    }
    return result;
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::operator*(const Matrix &matrix) const {
    if (_cols != matrix._rows) {
        throw std::runtime_error("Trying to multiply matrices with incompatible sizes!");
    }
    Matrix<Floating> result(_rows, matrix._cols);
    result = static_cast<Floating>(0.0);
    for (size_t i = 0; i < result._rows; i++) {
        for (size_t j = 0; j < result._cols; j++) {
            for (size_t k = 0; k < _cols; k++) {
                result(i, j) += this->operator()(i, k) * matrix(k, j);
            }
        }
    }
    return result;
}

template <typename Floating>
Matrix<Floating> &Matrix<Floating>::operator*=(const Floating scalar) {
    for (size_t i = 0; i < (_rows * _cols); i++) {
        data[i] *= scalar;
    }
    return *this;
}

template <typename Floating>
Matrix<Floating> &Matrix<Floating>::operator=(const Floating value) {
    for (size_t i = 0; i < (_rows * _cols); i++) {
        data[i] = value;
    }
    return *this;
}

template <typename Floating>
Matrix<Floating> &Matrix<Floating>::operator=(const Matrix<Floating> &to_copy) {
    if ((_rows != to_copy._rows) || (_cols != to_copy._cols)) {
        resize(to_copy._rows, to_copy._cols);
    }
    for (size_t i = 0; i < (_rows * _cols); i++) {
        data[i] = to_copy.data[i];
    }
    return *this;
}

template <typename Floating>
bool Matrix<Floating>::operator==(const Matrix &matrix) const {
    if ((_rows != matrix._rows) || (_cols != matrix._cols)) {
        return false;
    }
    for (size_t i = 0; i < (_rows * _cols); i++) {
        if (!are_close(data[i], matrix.data[i], static_cast<Floating>(matrix_precision))) {
            return false;
        }
    }
    return true;
}

template <typename Floating>
bool Matrix<Floating>::operator!=(const Matrix &matrix) const {
    return !(this->operator==(matrix));
}

template <typename Floating>
void Matrix<Floating>::resize(const size_t rows, const size_t cols) {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    _rows = 0;
    _cols = 0;
    if ((rows != 0) && (cols != 0)) {
        data = new Floating[rows * cols];
        _rows = rows;
        _cols = cols;
    }
}

template <typename Floating>
Matrix<Floating> &Matrix<Floating>::random(const Floating min, const Floating max) {
    srand(time(NULL));
    for (size_t i = 0; i < (_rows * _cols); i++) {
        data[i] = random_number<Floating>(min, max);
    }
    return *this;
}

template <typename Floating>
std::ostream &operator<<(std::ostream &os, const Matrix<Floating> &matrix) {
    return os << matrix.to_string();
}

template <typename Floating>
std::string Matrix<Floating>::to_string(void) const {
    std::ostringstream strs;
    strs << "       ";
    for (size_t j = 0; j < _cols; j++) {
        strs << "[" << std::setw(3) << j << "]      ";
    }
    strs << std::endl;
    for (size_t i = 0; i < _rows; i++) {
        strs << "[" << std::setw(3) << i << "]: ";
        for (size_t j = 0; j < _cols; j++) {
            strs << std::left << std::setw(10) << this->operator()(i, j) << " ";
        }
        strs << std::endl;
    }
    return strs.str();
}

template <typename Floating>
bool Matrix<Floating>::is_squared(void) const {
    return (_rows == _cols);
}

template <typename Floating>
bool Matrix<Floating>::is_symmetric(void) const {
    if (!is_squared()) {
        return false;
    }
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < i; j++) {
            if (!are_close(this->operator()(i, j), this->operator()(j, i), static_cast<Floating>(matrix_precision))) {
                return false;
            }
        }
    }
    return true;
}

template <typename Floating>
bool Matrix<Floating>::is_skew_symmetric(void) const {
    if (!is_squared()) {
        return false;
    }
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j <= i; j++) {
            if (!are_close(this->operator()(i, j), -this->operator()(j, i), static_cast<Floating>(matrix_precision))) {
                return false;
            }
        }
    }
    return true;
}

template <typename Floating>
Floating Matrix<Floating>::trace(void) const {
    if (!is_squared()) {
        throw std::runtime_error("Trying to calculate the trace of a non squared matrix!");
    }
    Floating trace = static_cast<Floating>(0.0);
    for (size_t i = 0; i < _rows; i++) {
        trace += this->operator()(i, i);
    }
    return trace;
}

template <typename Floating>
Floating Matrix<Floating>::determinant(void) const {
    if (!is_squared()) {
        throw std::runtime_error("Trying to calculate the determinant of a non squared matrix!");
    }
    auto matrix = *this;
    // Forward elimination (Gauss)
    for (size_t k = 0; (k + 1) < matrix._rows; k++) {
        for (size_t i = (k + 1); i < matrix._rows; i++) {
            const double m = matrix(i, k) / matrix(k, k);
            for (size_t j = (k + 1); j < matrix._rows; j++) {
                matrix(i, j) -= m * matrix(k, j);
            }
        }
    }
    Floating det = static_cast<Floating>(1.0);
    for (size_t k = 0; k < matrix._rows; k++) {
        det *= matrix(k, k);
    }
    return det;
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::transpose(void) const {
    Matrix<Floating> transpose(_cols, _rows);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            transpose(j, i) = this->operator()(i, j);
        }
    }
    return transpose;
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::symmetric(void) const {
    if (!is_squared()) {
        throw std::runtime_error("Trying to calculate the symmetric part of a non squared matrix!");
    }
    Matrix<Floating> sym(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            sym(i, j) = (this->operator()(i, j) + this->operator()(j, i)) / static_cast<Floating>(2.0);
        }
    }
    return sym;
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::skew_symmetric(void) const {
    if (!is_squared()) {
        throw std::runtime_error("Trying to calculate the skew-symmetric part of a non squared matrix!");
    }
    Matrix<Floating> skew(_rows, _cols);
    for (size_t i = 0; i < _rows; i++) {
        for (size_t j = 0; j < _cols; j++) {
            skew(i, j) = (this->operator()(i, j) - this->operator()(j, i)) / static_cast<Floating>(2.0);
        }
    }
    return skew;
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::inverse(void) const {
    if (!is_squared()) {
        throw std::runtime_error("Trying to calculate the inverse matrix of a non squared matrix!");
    }
    Matrix<Floating> matrix = *this;
    Matrix<Floating> inv(_rows, _cols);
    Vector<Floating> b(_rows);
    // LU decomposition
    for (size_t k = 0; (k + 1) < matrix._rows; k++) {
        for (size_t i = (k + 1); i < matrix._rows; i++) {
            matrix(i, k) /= matrix(k, k);
            for (size_t j = (k + 1); j < matrix._rows; j++) {
                matrix(i, j) -= matrix(i, k) * matrix(k, j);
            }
        }
    }
    // Computes inverse matrix
    for (size_t i = 0; i < matrix._rows; i++) {
        for (size_t j = 0; j < matrix._rows; j++) {
            b[j] = static_cast<Floating>((j == i) ? 1.0 : 0.0);
        }
        // Foward substitution
        for (size_t i = 0; i < matrix._rows; i++) {
            for (size_t j = 0; j < i; j++) {
                b[i] -= matrix(i, j) * b[j];
            }
        }
        // Back substitution
        for (size_t i = (matrix._rows - 1); i < matrix._rows; i--) {
            for (size_t j = (i + 1); j < matrix._rows; j++) {
                b[i] -= matrix(i, j) * b[j];
            }
            b[i] /= matrix(i, i);
        }
        for (size_t j = 0; j < matrix._rows; j++) {
            inv(j, i) = b[j];
        }
    }
    return inv;
}

template <typename Floating>
Matrix<Floating> Matrix<Floating>::identity(const size_t rows) {
    Matrix<Floating> matrix(rows, rows);
    for (size_t i = 0; i < matrix._rows; i++) {
        for (size_t j = 0; j < matrix._rows; j++) {
            matrix(i, j) = static_cast<Floating>(i == j ? 1.0 : 0.0);
        }
    }
    return matrix;
}

#endif  // __MATRIX_CPP

//------------------------------------------------------------------------------
// END
//------------------------------------------------------------------------------

// MIT License

// Copyright (c) 2022 CLECIO JUNG <clecio.jung@gmail.com>

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.