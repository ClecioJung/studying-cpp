#include "../lib/vector.hpp"

#include <cstdlib>
#include <iostream>

int main(void) {
    Vector<double> a(3);
    Vector<double> b(3);
    a[0] = 2.0;
    a[1] = 3.0;
    a[2] = 4.0;
    std::cout << "Vector a:\n"
              << a << std::endl;
    b[0] = 5.0;
    b[1] = 6.0;
    b[2] = 7.0;
    std::cout << "Vector b:\n"
              << b << std::endl;
    std::cout << "Vector b multiplied by 2 is:\n"
              << b * 2.0 << std::endl;
    std::cout << "Vector a multiplied by 2 is:\n"
              << 2.0 * a << std::endl;
    {
        constexpr double expected_dot_product = 56.0;
        const double dot_product = a * b;
        if (are_close(dot_product, expected_dot_product, vector_precision)) {
            std::cout << "Dot product between a and b: " << dot_product << std::endl;
        } else {
            std::cerr << "The dot product was NOT properly calculated: " << dot_product << std::endl;
            return EXIT_FAILURE;
        }
    }
    {
        const double expected_norm = square_root<double>(29.0);
        const double norm = a.norm();
        if (are_close(norm, expected_norm, vector_precision)) {
            std::cout << "Euclidean norm of a: " << norm << std::endl;
        } else {
            std::cerr << "The euclidean norm was NOT properly calculated: " << norm << std::endl;
            return EXIT_FAILURE;
        }
    }
    {
        auto cross = a.cross_product(b);
        std::cout << "Cross product:\n"
                  << cross;
        if (cross.is_orthogonal(a) && cross.is_orthogonal(b)) {
            std::cout << "The cross product is orthogonal to the vectors a and b!\n\n";
        } else {
            std::cerr << "The cross product was NOT properly calculated!\n";
            return EXIT_FAILURE;
        }
    }
    a *= 2.0;
    std::cout << "Vector a scaled by 2 is:\n"
              << a << std::endl;
    Vector<double> c(3);
    std::cout << "Vector c is random:\n"
              << c.random(0.0, 1.0) << std::endl;
    Vector<double> d(3);
    d = 100.0;
    std::cout << "Vector d is initialized:\n"
              << d << std::endl;
    auto e = a + b;
    std::cout << "Vector e = (a + b):\n"
              << e << std::endl;
    auto f = a - b;
    std::cout << "Vector f = (a - b):\n"
              << f << std::endl;
    std::cout << "For each loop in the vector e:\n";
    for (auto value : e) {
        std::cout << value << " - ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}