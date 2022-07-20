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

#ifndef __CIRCULAR_BUFFER_CPP
#define __CIRCULAR_BUFFER_CPP

#include <sstream>
#include <string>

template <typename Floating, size_t capacity>
class Circular_Buffer {
   public:
    Circular_Buffer(void) : start(values, 0), finish(values, 0) {}
    std::string to_string(void) const;
    void push(const Floating value);
    Floating pop(void);
    void unshift(const Floating value);
    Floating shift(void);

    // Iterators
    template <bool Const>
    class Buffer_Iterator;
    Buffer_Iterator<false> begin(void);
    Buffer_Iterator<false> end(void);
    Buffer_Iterator<true> begin(void) const;
    Buffer_Iterator<true> end(void) const;

   private:
    Floating values[capacity];
    Buffer_Iterator<false> start;
    Buffer_Iterator<false> finish;
};

template <typename Floating, size_t capacity>
std::ostream &operator<<(std::ostream &os, Circular_Buffer<Floating, capacity> buf) {
    return os << buf.to_string();
}

template <typename Floating, size_t capacity>
std::string Circular_Buffer<Floating, capacity>::to_string(void) const {
    std::ostringstream strs;
    strs << "Start: " << start.index << ", finish: " << finish.index << std::endl;
    for (auto it = this->begin(); it != this->end(); ++it) {
        strs << "[" << it.index << "]: " << *it << std::endl;
    }
    return strs.str();
}

template <typename Floating, size_t capacity>
void Circular_Buffer<Floating, capacity>::push(const Floating value) {
    values[finish.index] = value;
    ++finish;
    if (start == finish) {
        throw std::runtime_error("Buffer overflow!");
    }
}

template <typename Floating, size_t capacity>
Floating Circular_Buffer<Floating, capacity>::pop(void) {
    if (start == finish) {
        throw std::runtime_error("Buffer is empty!");
    }
    --finish;
    return values[finish.index];
}

// Inserts element at the beginning of the buffer
template <typename Floating, size_t capacity>
void Circular_Buffer<Floating, capacity>::unshift(const Floating value) {
    --start;
    values[start.index] = value;
    if (start == finish) {
        throw std::runtime_error("Buffer overflow!");
    }
}

// Removes and returns first element of the buffer
template <typename Floating, size_t capacity>
Floating Circular_Buffer<Floating, capacity>::shift(void) {
    if (start == finish) {
        throw std::runtime_error("Buffer is empty!");
    }
    Floating value = values[start.index];
    ++start;
    return value;
}

template <typename Floating, size_t capacity>
template <bool Const>
class Circular_Buffer<Floating, capacity>::Buffer_Iterator {
   private:
    const Floating *const values;
    size_t index;

   public:
    friend class Circular_Buffer<Floating, capacity>;

    Buffer_Iterator(const Floating *const values, size_t index);
    Buffer_Iterator &operator++(void);
    Buffer_Iterator &operator--(void);
    bool operator!=(const Buffer_Iterator &it) const;
    bool operator==(const Buffer_Iterator &it) const;

    template <bool Q = Const>
    typename std::enable_if<!Q, Floating &>::type operator*();
    template <bool Q = Const>
    typename std::enable_if<Q, const Floating &>::type operator*();
};

template <typename Floating, size_t capacity>
template <bool Const>
Circular_Buffer<Floating, capacity>::Buffer_Iterator<Const>::Buffer_Iterator(const Floating *const values, size_t index) : values(values) {
    if (index > capacity) {
        throw std::runtime_error("Invalid index in buffer iterator!");
    }
    this->index = index;
}

template <typename Floating, size_t capacity>
template <bool Const>
template <bool Q>
typename std::enable_if<!Q, Floating &>::type
Circular_Buffer<Floating, capacity>::Buffer_Iterator<Const>::operator*(void) {
    return const_cast<Floating *>(values)[index];
}

template <typename Floating, size_t capacity>
template <bool Const>
template <bool Q>
typename std::enable_if<Q, const Floating &>::type
Circular_Buffer<Floating, capacity>::Buffer_Iterator<Const>::operator*(void) {
    return values[index];
}

template <typename Floating, size_t capacity>
template <bool Const>
typename Circular_Buffer<Floating, capacity>::template Buffer_Iterator<Const> &
Circular_Buffer<Floating, capacity>::Buffer_Iterator<Const>::operator++(void) {
    index++;
    if (index >= capacity) {
        index = 0;
    }
    return *this;
}

template <typename Floating, size_t capacity>
template <bool Const>
typename Circular_Buffer<Floating, capacity>::template Buffer_Iterator<Const> &
Circular_Buffer<Floating, capacity>::Buffer_Iterator<Const>::operator--(void) {
    index--;
    if (index >= capacity) {
        index = capacity - 1;
    }
    return *this;
}

template <typename Floating, size_t capacity>
template <bool Const>
bool Circular_Buffer<Floating, capacity>::Buffer_Iterator<Const>::operator!=(const Buffer_Iterator<Const> &it) const {
    return (index != it.index);
}

template <typename Floating, size_t capacity>
template <bool Const>
bool Circular_Buffer<Floating, capacity>::Buffer_Iterator<Const>::operator==(const Buffer_Iterator<Const> &it) const {
    return (index == it.index);
}

template <typename Floating, size_t capacity>
typename Circular_Buffer<Floating, capacity>::template Buffer_Iterator<false>
Circular_Buffer<Floating, capacity>::begin(void) {
    return start;
}

template <typename Floating, size_t capacity>
typename Circular_Buffer<Floating, capacity>::template Buffer_Iterator<false>
Circular_Buffer<Floating, capacity>::end(void) {
    return finish;
}

template <typename Floating, size_t capacity>
typename Circular_Buffer<Floating, capacity>::template Buffer_Iterator<true>
Circular_Buffer<Floating, capacity>::begin(void) const {
    return Buffer_Iterator<true>(this->values, start.index);
}

template <typename Floating, size_t capacity>
typename Circular_Buffer<Floating, capacity>::template Buffer_Iterator<true>
Circular_Buffer<Floating, capacity>::end(void) const {
    return Buffer_Iterator<true>(this->values, finish.index);
}

#endif  // __CIRCULAR_BUFFER_CPP

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