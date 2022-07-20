#include "../lib/complex.hpp"

#include <cstdlib>
#include <iostream>

int main(void) {
    Complex<double> a(1.0, 1.0);
    Complex<double> b(1.0);
    Complex<double> c;
    auto d = Complex<double>::from_polar(1.0, 0.1);
    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;
    std::cout << "c = " << c << std::endl;
    std::cout << "d = " << d << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;
    std::cout << "a - b = " << (a - b) << std::endl;
    std::cout << "a * b = " << (a * b) << std::endl;
    std::cout << "a / b = " << (a / b) << std::endl;
    std::cout << "a + 2 = " << (a + 2) << std::endl;
    std::cout << "2 + a = " << (2.0 + a) << std::endl;
    return EXIT_SUCCESS;
}