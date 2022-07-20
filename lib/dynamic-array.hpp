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

#include <sstream>

constexpr size_t initial_array_capacity = 4;

template <typename Number>
class Dynamic_Array {
   private:
    Number *values;
    size_t capacity;
    size_t length;

    void grow_capacity_if_needed(void);

   public:
    Dynamic_Array(void);
    ~Dynamic_Array(void);
    std::string to_string(void) const;
    void push(const Number value);
    Number pop(void);
    void unshift(const Number value);
    Number shift(void);
    Number value_at(const size_t index) const;
    size_t find(const Number value) const;
    void delete_at(const size_t index);
    Number &operator[](const size_t index) const;

    // Iterators
    Number *begin(void) { return &values[0]; }
    const Number *begin(void) const { return &values[0]; }
    Number *end(void) { return &values[length]; }
    const Number *end(void) const { return &values[length]; }
};

template <typename Number>
Dynamic_Array<Number>::Dynamic_Array(void) : length(0) {
    capacity = initial_array_capacity;
    values = new int[capacity];
}

template <typename Number>
Dynamic_Array<Number>::~Dynamic_Array(void) {
    length = 0;
    capacity = 0;
    delete[] values;
    values = NULL;
}

template <typename Number>
std::ostream &operator<<(std::ostream &os, const Dynamic_Array<Number> &array) {
    return os << array.to_string();
}

template <typename Number>
std::string Dynamic_Array<Number>::to_string(void) const {
    std::ostringstream strs;
    strs << "Array length: " << length << ", capacity: " << capacity << std::endl;
    for (size_t i = 0; i < length; i++) {
        strs << "[" << i << "]: " << values[i] << std::endl;
    }
    return strs.str();
}

template <typename Number>
void Dynamic_Array<Number>::grow_capacity_if_needed(void) {
    if (length + 1 > capacity) {
        capacity *= 2;
        int *new_values = new int[capacity];
        std::copy(&values[0], &values[length], new_values);
        delete[] values;
        values = new_values;
    }
}

template <typename Number>
void Dynamic_Array<Number>::push(const Number value) {
    grow_capacity_if_needed();
    values[length] = value;
    length++;
}

template <typename Number>
Number Dynamic_Array<Number>::pop(void) {
    if (length == 0) {
        throw std::runtime_error("Trying to pop an empty array!");
    }
    length--;
    return values[length];
}

// Inserts element at the beginning of the array
template <typename Number>
void Dynamic_Array<Number>::unshift(const Number value) {
    grow_capacity_if_needed();
    for (size_t i = length; i > 0; i--) {
        values[i] = values[i - 1];
    }
    values[0] = value;
    length++;
}

// Removes and returns first element of the array
template <typename Number>
Number Dynamic_Array<Number>::shift(void) {
    if (length == 0) {
        throw std::runtime_error("Trying to shift an empty array!");
    }
    const Number value = values[0];
    length--;
    for (size_t i = 0; i < length; i++) {
        values[i] = values[i + 1];
    }
    return value;
}

template <typename Number>
Number Dynamic_Array<Number>::value_at(const size_t index) const {
    if (index >= length) {
        throw std::runtime_error("Trying to access the array in invalid range!");
    }
    return values[index];
}

template <typename Number>
size_t Dynamic_Array<Number>::find(const Number value) const {
    // Sequential search
    for (size_t i = 0; i < length; i++) {
        if (values[i] == value) {
            return i;
        }
    }
    throw std::runtime_error("Didn't found the requested value in the array!");
}

template <typename Number>
void Dynamic_Array<Number>::delete_at(const size_t index) {
    if (index >= length) {
        throw std::runtime_error("Trying to delete an element from the array in invalid range!");
    }
    length--;
    for (size_t i = index; i < length; i++) {
        values[i] = values[i + 1];
    }
}

template <typename Number>
Number &Dynamic_Array<Number>::operator[](const size_t index) const {
    if (index >= length) {
        throw std::runtime_error("Trying to access dynamic array in invalid range!");
    }
    return values[index];
}

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