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

#include <cmath>
#include <cstdint>

constexpr uint64_t scalar_iterations = 10000;
constexpr double scalar_precision = 1e-10;
constexpr double const_pi = 3.14159265358979323846;
constexpr double const_euler = 2.7182818284590452354;

template <typename Floating>
void swap(Floating &a, Floating &b) {
    const Floating temp = a;
    a = b;
    b = temp;
}

uint64_t factorial(uint64_t value) {
    uint64_t result = 1;
    while (value > 1) {
        result = result * value;
        value--;
    }
    return result;
}

template <typename Floating>
bool are_close(const Floating a, const Floating b, const Floating delta) {
    return (fabs(a - b) < delta);
}

template <typename Floating>
bool isNAN(const Floating value) {
    return (value != value);
}

template <typename Floating>
Floating maximum(const Floating a, const Floating b) {
    return ((a > b) ? a : b);
}

template <typename Floating>
Floating minimum(const Floating a, const Floating b) {
    return ((a < b) ? a : b);
}

template <typename Floating>
Floating sign(const Floating value) {
    return static_cast<Floating>((value > 0) ? 1.0 : -1.0);
}

// My own round function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating round(const Floating value) {
    return static_cast<Floating>((value >= 0.0) ? floor(value + 0.5) : ceil(value - 0.5));
}

template <typename Floating>
Floating random_number(const Floating min, const Floating max) {
    const Floating rand_unitary = (static_cast<Floating>(rand())) / (static_cast<Floating>(RAND_MAX));
    return (rand_unitary * (max - min) + min);
}

// My own square root function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating square_root(const Floating value) {
    if (are_close<Floating>(fabs(value), 0.0, static_cast<Floating>(scalar_precision))) {
        return 0.0;  // square_root(0) = 0
    } else if (value < 0) {
        return NAN;
    }
    Floating x = value;
    // Use the Newton-Raphson method to find the root
    // of the function f(x) = x^2 - value
    for (size_t k = 0; k < scalar_iterations; k++) {
        const Floating delta = (value / x - x) / 2.0;
        x += delta;
        if (are_close<Floating>(fabs(delta), 0.0, static_cast<Floating>(scalar_precision))) {
            break;
        }
    }
    return x;
}

// My own root function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating root(const Floating value, const uint64_t n) {
    if (n == 1) {
        return value;
    } else if ((n == 0) && (are_close(value, static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision)))) {
        return NAN;
    } else if (n == 0) {
        return 1.0;
    } else if (are_close(value, static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision))) {
        return 0.0;  // root(0) = 0
    } else if ((n % 2 == 0) && (value < static_cast<Floating>(0.0))) {
        return NAN;
    }
    Floating x = value;
    // Use the Newton-Raphson method to find the root
    // of the function f(x) = x^n - value
    for (size_t k = 0; k < scalar_iterations; k++) {
        const Floating delta = (value / power(x, (n - 1)) - x) / (static_cast<Floating>(n));
        x += delta;
        if (are_close<Floating>(fabs(delta), static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision))) {
            break;
        }
    }
    return x;
}

// My own power function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating power(const Floating base, uint64_t expoent) {
    Floating result = static_cast<Floating>(1.0);
    while (expoent != 0) {
        result *= base;
        expoent--;
    }
    return result;
}

// My own exponential function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating exponential(const Floating value) {
    Floating term = static_cast<Floating>(1.0);
    Floating result = term;
    for (uint64_t i = 1; i < scalar_iterations; i++) {
        term *= value / (static_cast<Floating>(i));
        result += term;
        if (are_close<Floating>(fabs(term), static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision))) {
            break;
        }
    }
    return result;
}

// My own sine function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating sine(Floating value) {
    value = value - static_cast<Floating>(2.0 * const_pi) * floor(value / static_cast<Floating>(2.0 * const_pi));
    Floating term = value;
    Floating result = term;
    for (uint64_t i = 1; i < scalar_iterations; i++) {
        term *= -value * value / (static_cast<Floating>((2 * i + 1) * (2 * i)));
        result += term;
        if (are_close<Floating>(fabs(term), static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision))) {
            break;
        }
    }
    return result;
}

// My own cosine function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating cosine(Floating value) {
    value = value - static_cast<Floating>(2.0 * const_pi) * floor(value / static_cast<Floating>(2.0 * const_pi));
    Floating term = static_cast<Floating>(1.0);
    Floating result = term;
    for (uint64_t i = 1; i < scalar_iterations; i++) {
        term *= -value * value / (static_cast<Floating>((2 * i) * (2 * i - 1)));
        result += term;
        if (are_close<Floating>(fabs(term), static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision))) {
            break;
        }
    }
    return result;
}

// My own tangent function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating tangent(const Floating value) {
    return (sine(value) / cosine(value));
}

// My own arctangent function, so I don't need to link with -lm,
// avoiding any dependencies
template <typename Floating>
Floating arctangent(const Floating value) {
    if (are_close<Floating>(fabs(value), static_cast<Floating>(1.0), static_cast<Floating>(scalar_precision))) {
        return (sign(value) * const_pi / 4.0);
    } else if (fabs(value) < 1.0) {
        Floating result = value;
        for (uint64_t i = 1; i < scalar_iterations; i++) {
            const Floating term = static_cast<Floating>(i % 2 ? -1.0 : 1.0) * power(value, 2 * i + 1) / (static_cast<Floating>(2 * i + 1));
            result += term;
            if (are_close<Floating>(term, static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision))) {
                break;
            }
        }
        return result;
    } else {
        Floating result = static_cast<Floating>(const_pi / 2.0 * (value > static_cast<Floating>(1.0) ? 1.0 : -1.0));
        for (uint64_t i = 1; i < scalar_iterations; i++) {
            const Floating term = static_cast<Floating>(i % 2 ? -1.0 : 1.0) / (power(value, 2 * i - 1) * (static_cast<Floating>(2 * i - 1)));
            result += term;
            if (are_close<Floating>(term, static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision))) {
                break;
            }
        }
        return result;
    }
}

template <typename Floating>
Floating atan2(const Floating y, const Floating x) {
    const bool x_is_zero = are_close<Floating>(x, static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision));
    const bool y_is_zero = are_close<Floating>(y, static_cast<Floating>(0.0), static_cast<Floating>(scalar_precision));
    if (x_is_zero && y_is_zero) {
        return static_cast<Floating>(0.0);
    } else if (x_is_zero) {
        return (sign(y) * static_cast<Floating>(const_pi / 2.0));
    } else if (x > static_cast<Floating>(0.0)) {
        return arctangent(y / x);
    } else if (y >= static_cast<Floating>(0.0)) {
        return (arctangent(y / x) + static_cast<Floating>(const_pi));
    } else {
        return (arctangent(y / x) - static_cast<Floating>(const_pi));
    }
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