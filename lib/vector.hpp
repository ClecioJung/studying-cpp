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

#ifndef __VECTOR_CPP
#define __VECTOR_CPP

#include <cstdint>
#include <iostream>
#include <sstream>

#include "scalar.hpp"

constexpr uint64_t vecto_iterations = 10000;
constexpr double vector_precision = 1e-8;

template <typename Floating>
class Vector {
   private:
    Floating *data;
    size_t len;

   public:
    Vector(void) : data(nullptr), len(0){};
    Vector(const size_t len);
    Vector(const Vector &vector);
    ~Vector(void);
    void resize(const size_t length);
    Floating &operator[](const size_t index) const;
    Vector &random(const Floating min, const Floating max);
    std::string to_string(void) const;
    Vector &operator=(const Floating value);
    Vector &operator=(const Vector &to_copy);
    Vector operator*(const Floating scalar) const;
    Vector &operator*=(const Floating scalar);
    Floating operator*(const Vector &vector) const;  // Dot product
    Vector cross_product(const Vector &vector) const;
    Floating norm(void) const;
    Floating max(void) const;
    Floating min(void) const;
    Floating max_abs(void) const;
    Floating mean(void) const;
    Vector operator+(const Vector &vector) const;
    Vector operator-(const Vector &vector) const;
    Floating max_diff(const Vector &vector) const;
    bool operator==(const Vector &vector) const;
    bool is_orthogonal(const Vector &vector) const;
    bool is_sorted(void) const;
    void sort(void);
    size_t search(const double value) const;
    size_t binary_search(const double value) const;

    // Iterators
    Floating *begin(void) { return &data[0]; }
    const Floating *begin(void) const { return &data[0]; }
    Floating *end(void) { return &data[len]; }
    const Floating *end(void) const { return &data[len]; }
};

template <typename Floating>
Vector<Floating>::Vector(const size_t length) : data(nullptr), len(length) {
    if (len != 0) {
        data = new Floating[len];
    }
}

template <typename Floating>
Vector<Floating>::Vector(const Vector<Floating> &vector) : data(nullptr), len(vector.len) {
    if (len != 0) {
        data = new Floating[vector.len];
        for (size_t i = 0; i < len; i++) {
            data[i] = vector.data[i];
        }
    }
}

template <typename Floating>
Vector<Floating>::~Vector(void) {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    len = 0;
}

template <typename Floating>
void Vector<Floating>::resize(const size_t length) {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
    len = 0;
    if (length != 0) {
        data = new Floating[length];
        len = length;
    }
}

template <typename Floating>
Floating &Vector<Floating>::operator[](const size_t index) const {
    if (index >= len) {
        throw std::runtime_error("Trying to access vector in invalid range!");
    }
    return data[index];
}

template <typename Floating>
Vector<Floating> &Vector<Floating>::random(const Floating min, const Floating max) {
    srand(time(NULL));
    for (size_t i = 0; i < len; i++) {
        data[i] = random_number<Floating>(min, max);
    }
    return *this;
}

template <typename Floating>
std::ostream &operator<<(std::ostream &os, const Vector<Floating> &vector) {
    return os << vector.to_string();
}

template <typename Floating>
std::string Vector<Floating>::to_string(void) const {
    std::ostringstream strs;
    for (size_t i = 0; i < len; i++) {
        strs << "[" << i << "]: " << data[i] << std::endl;
    }
    return strs.str();
}

template <typename Floating>
Vector<Floating> &Vector<Floating>::operator=(const Floating value) {
    for (size_t i = 0; i < len; i++) {
        data[i] = value;
    }
    return *this;
}

template <typename Floating>
Vector<Floating> &Vector<Floating>::operator=(const Vector<Floating> &to_copy) {
    if (len != to_copy.len) {
        resize(to_copy.len);
    }
    for (size_t i = 0; i < len; i++) {
        data[i] = to_copy.data[i];
    }
    return *this;
}

template <typename Floating>
Vector<Floating> Vector<Floating>::operator*(const Floating scalar) const {
    Vector result(len);
    for (size_t i = 0; i < len; i++) {
        result.data[i] = data[i] * scalar;
    }
    return result;
}

template <typename Floating>
Vector<Floating> operator*(const Floating scalar, const Vector<Floating> &vector) {
    return (vector * scalar);
}

template <typename Floating>
Vector<Floating> &Vector<Floating>::operator*=(const Floating scalar) {
    for (size_t i = 0; i < len; i++) {
        data[i] *= scalar;
    }
    return *this;
}

// Dot product
template <typename Floating>
Floating Vector<Floating>::operator*(const Vector<Floating> &vector) const {
    if (len != vector.len) {
        throw std::runtime_error("Dot product involving vectors with incompatible lengths!");
    }
    Floating result = static_cast<Floating>(0.0);
    for (size_t i = 0; i < len; i++) {
        result += data[i] * vector.data[i];
    }
    return result;
}

template <typename Floating>
Vector<Floating> Vector<Floating>::cross_product(const Vector<Floating> &vector) const {
    if ((len != 3) || (vector.len != 3)) {
        throw std::runtime_error("Cross product involving vectors with incompatible lengths!");
    }
    Vector<Floating> result(len);
    result.data[0] = data[1] * vector.data[2] - data[2] * vector.data[1];
    result.data[1] = data[2] * vector.data[0] - data[0] * vector.data[2];
    result.data[2] = data[0] * vector.data[1] - data[1] * vector.data[0];
    return result;
}

template <typename Floating>
Floating Vector<Floating>::norm(void) const {
    Floating value = static_cast<Floating>(0.0);
    for (size_t i = 0; i < len; i++) {
        value += data[i] * data[i];
    }
    return square_root<Floating>(value);
}

template <typename Floating>
Floating Vector<Floating>::max(void) const {
    Floating value = static_cast<Floating>(0.0);
    for (size_t i = 0; i < len; i++) {
        value = maximum<Floating>(value, data[i]);
    }
    return value;
}

template <typename Floating>
Floating Vector<Floating>::min(void) const {
    Floating value = static_cast<Floating>(INFINITY);
    for (size_t i = 0; i < len; i++) {
        value = minimum(value, data[i]);
    }
    return value;
}

template <typename Floating>
Floating Vector<Floating>::max_abs(void) const {
    Floating error = static_cast<Floating>(0.0);
    for (size_t i = 0; i < len; i++) {
        error = maximum(fabs(data[i]), error);
    }
    return error;
}

template <typename Floating>
Floating Vector<Floating>::mean(void) const {
    Floating sum = static_cast<Floating>(0.0);
    for (size_t i = 0; i < len; i++) {
        sum += data[i];
    }
    return (sum / static_cast<Floating>(len));
}

template <typename Floating>
Vector<Floating> Vector<Floating>::operator+(const Vector<Floating> &vector) const {
    if (len != vector.len) {
        throw std::runtime_error("Sum involving vectors with incompatible lengths!");
    }
    Vector<Floating> result(len);
    for (size_t i = 0; i < len; i++) {
        result.data[i] = data[i] + vector.data[i];
    }
    return result;
}

template <typename Floating>
Vector<Floating> Vector<Floating>::operator-(const Vector<Floating> &vector) const {
    if (len != vector.len) {
        throw std::runtime_error("Subtraction involving vectors with incompatible lengths!");
    }
    Vector<Floating> result(len);
    for (size_t i = 0; i < len; i++) {
        result.data[i] = data[i] - vector.data[i];
    }
    return result;
}

template <typename Floating>
Floating Vector<Floating>::max_diff(const Vector &vector) const {
    if (len != vector.len) {
        throw std::runtime_error("Comparisson involving vectors with incompatible lengths!");
    }
    Floating error = static_cast<Floating>(0.0);
    for (size_t i = 0; i < len; i++) {
        error = maximum<Floating>(fabs(data[i] - vector.data[i]), error);
    }
    return error;
}

template <typename Floating>
bool Vector<Floating>::operator==(const Vector &vector) const {
    if (len != vector.len) {
        return false;
    }
    for (size_t i = 0; i < len; i++) {
        if (!are_close<Floating>(data[i], vector.data[i], static_cast<Floating>(vector_precision))) {
            return false;
        }
    }
    return true;
}

template <typename Floating>
bool Vector<Floating>::is_orthogonal(const Vector &vector) const {
    if (len != vector.len) {
        return false;
    }
    return are_close<Floating>((*this) * vector, 0.0, static_cast<Floating>(vector_precision));
}

template <typename Floating>
bool Vector<Floating>::is_sorted(void) const {
    for (size_t i = 0; (i + 1) < len; i++) {
        if (data[i] > data[i + 1]) {
            return false;
        }
    }
    return true;
}

template <typename Floating>
void qs(const Floating *array, const size_t left, const size_t right) {
    const Floating middle = array[(left + right) / 2];
    size_t i = left;
    size_t j = right;
    do {
        while (array[i] < middle && i < right) {
            i++;
        }
        while (middle < array[j] && j > left && j != 0) {
            j--;
        }
        if (i <= j) {
            swap<Floating>(array[i], array[j]);
            i++;
            if (j != 0) {
                j--;
            }
        }
    } while (i <= j);
    if (left < j) {
        qs<Floating>(array, left, j);
    }
    if (i < right) {
        qs<Floating>(array, i, right);
    }
}

// Quicksort algorithm
template <typename Floating>
void Vector<Floating>::sort(void) {
    if (len != 0) {
        qs<Floating>(data, 0, len - 1);
    }
}

template <typename Floating>
size_t Vector<Floating>::search(const double value) const {
    size_t closest_index = 0;
    for (size_t i = 0; i < len; i++) {
        if (data[i] == value) {
            return i;
        } else if (fabs(data[i] - value) < fabs(data[closest_index] - value)) {
            closest_index = i;
        }
    }
    return closest_index;
}

template <typename Floating>
size_t Vector<Floating>::binary_search(const double value) const {
    size_t middle = len;
    size_t low = 0;
    size_t high = len - 1;
    while (low <= high) {
        middle = (low + high) / 2;
        if (value < data[middle]) {
            high = middle - 1;
        } else if (value > data[middle]) {
            low = middle + 1;
        } else {
            break;
        }
    }
    return middle;
}

#endif  // __VECTOR_CPP

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