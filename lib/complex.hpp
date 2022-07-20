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

#ifndef __COMPLEX_CPP
#define __COMPLEX_CPP

#include <cmath>
#include <sstream>
#include <string>

#include "scalar.hpp"

constexpr double complex_precision = 1e-6;

template <typename Floating>
class Complex {
   private:
    Floating real;
    Floating imag;

   public:
    explicit Complex(Floating real, Floating imag) : real(real), imag(imag){};
    explicit Complex(Floating real) : real(real), imag(0){};
    explicit Complex(void) : real(0), imag(0){};
    std::string to_string(void) const;
    static Complex<Floating> from_polar(Floating modulus, Floating phase);
    Floating modulus(void) const;
    Floating argument(void) const;
    Complex<Floating> conjugate(void) const;
    Complex<Floating> inverse(void) const;
    Complex<Floating> operator+(Complex<Floating> b) const;
    Complex<Floating> operator+(Floating b) const;
    Complex<Floating> operator-(Complex<Floating> b) const;
    Complex<Floating> operator-(Floating b) const;
    Complex<Floating> operator*(Complex<Floating> b) const;
    Complex<Floating> operator*(Floating b) const;
    Complex<Floating> operator/(Complex<Floating> b) const;
    Complex<Floating> operator/(Floating b) const;
    bool operator==(Complex<Floating> b) const;
    bool operator==(Floating b) const;
};

template <typename Floating>
std::ostream& operator<<(std::ostream& os, const Complex<Floating> complex) {
    return os << complex.to_string();
}

template <typename Floating>
std::string Complex<Floating>::to_string(void) const {
    std::ostringstream strs;
    const char imaginary_unit = 'i';
    const bool print_real = !are_close<Floating>(real, static_cast<Floating>(0.0), static_cast<Floating>(complex_precision));
    const bool print_imag = !are_close<Floating>(imag, static_cast<Floating>(0.0), static_cast<Floating>(complex_precision));
    if (print_real && print_imag) {
        strs << real << ((imag > static_cast<Floating>(0.0)) ? " + " : " - ") << fabs(imag) << '*' << imaginary_unit;
    } else if (print_real && !print_imag) {
        strs << real;
    } else if (!print_real && print_imag) {
        strs << imag << '*' << imaginary_unit;
    } else {
        strs << "0.0";
    }
    return strs.str();
}

template <typename Floating>
Complex<Floating> Complex<Floating>::from_polar(const Floating modulus, const Floating phase) {
    Floating real = modulus * cosine<Floating>(phase);
    Floating imag = modulus * sine<Floating>(phase);
    return Complex<Floating>(real, imag);
}

template <typename Floating>
Floating Complex<Floating>::modulus(void) const {
    return square_root<Floating>(real * real + imag * imag);
}

template <typename Floating>
Floating Complex<Floating>::argument(void) const {
    return atan2<Floating>(imag, real);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::conjugate(void) const {
    return Complex<Floating>(real, -imag);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::inverse(void) const {
    const Floating squared_modulus = real * real + imag * imag;
    const Floating r = real / squared_modulus;
    const Floating i = -imag / squared_modulus;
    return Complex<Floating>(r, i);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::operator+(Complex<Floating> b) const {
    return Complex<Floating>(real + b.real, imag + b.imag);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::operator+(Floating b) const {
    return Complex<Floating>(real + b, imag);
}

template <typename Floating>
Complex<Floating> operator+(Floating b, Complex<Floating> a) {
    return (a + b);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::operator-(Complex<Floating> b) const {
    return Complex<Floating>(real - b.real, imag - b.imag);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::operator-(Floating b) const {
    return Complex<Floating>(real - b, imag);
}

template <typename Floating>
Complex<Floating> operator-(Floating b, Complex<Floating> a) {
    return (a - b);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::operator*(Complex<Floating> b) const {
    const Floating r = real * b.real - imag * b.imag;
    const Floating i = real * b.imag + imag * b.real;
    return Complex<Floating>(r, i);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::operator*(Floating b) const {
    return Complex<Floating>(real * b, imag * b);
}

template <typename Floating>
Complex<Floating> operator*(Floating b, Complex<Floating> a) {
    return (a * b);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::operator/(Complex<Floating> b) const {
    const Floating b_squared_modulus = b.real * b.real + b.imag * b.imag;
    const Floating r = (real * b.real + imag * b.imag) / b_squared_modulus;
    const Floating i = (imag * b.real - real * b.imag) / b_squared_modulus;
    return Complex<Floating>(r, i);
}

template <typename Floating>
Complex<Floating> Complex<Floating>::operator/(Floating b) const {
    return Complex<Floating>(real / b, imag / b);
}

template <typename Floating>
Complex<Floating> operator/(Floating b, Complex<Floating> a) {
    return (a / b);
}

template <typename Floating>
bool Complex<Floating>::operator==(Complex<Floating> b) const {
    return (are_close<Floating>(real, b.real, complex_precision)) && (are_close<Floating>(imag, b.imag, complex_precision));
}

template <typename Floating>
bool Complex<Floating>::operator==(Floating b) const {
    return (are_close<Floating>(real, b, complex_precision)) && (are_close<Floating>(imag, 0.0, complex_precision));
}

template <typename Floating>
Complex<Floating> operator==(Floating b, Complex<Floating> a) {
    return (a == b);
}

#endif  // __COMPLEX_CPP

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