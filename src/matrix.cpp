#include "../lib/matrix.hpp"

#include <cstdlib>
#include <iostream>

int main(void) {
    Matrix<double> A(3, 3);
    A(0, 0) = 2.0;
    A(0, 1) = 3.0;
    A(0, 2) = -1.0;
    A(1, 0) = 4.0;
    A(1, 1) = 4.0;
    A(1, 2) = -3.0;
    A(2, 0) = 2.0;
    A(2, 1) = -3.0;
    A(2, 2) = 1.0;
    std::cout << "Matrix A:\n"
              << A << std::endl;
    Matrix<double> B(3, 3);
    B(0, 0) = 1.0;
    B(0, 1) = 0.0;
    B(0, 2) = 0.0;
    B(1, 0) = 0.0;
    B(1, 1) = 1.0;
    B(1, 2) = 0.0;
    B(2, 0) = 0.0;
    B(2, 1) = 0.0;
    B(2, 2) = 1.0;
    std::cout << "Matrix B:\n"
              << B << std::endl;
    std::cout << "Matrix A * B:\n"
              << A * B << std::endl;
    std::cout << "The transpose matrix of A is:\n"
              << A.transpose() << std::endl;
    std::cout << "Matrix B multiplied by 2 is:\n"
              << B * 2.0 << std::endl;
    std::cout << "Matrix B multiplied by 3 is:\n"
              << 3.0 * B << std::endl;
    {
        Vector<double> v(3);
        v[0] = 1.0;
        v[1] = 0.0;
        v[2] = 0.0;
        std::cout << "Vector v:\n"
                  << v << std::endl;
        std::cout << "Multiplication A * v:\n"
                  << A * v << std::endl;
    }
    {
        const double expected_trace = 7.0;
        const double trace = A.trace();
        if (are_close(trace, expected_trace, scalar_precision)) {
            std::cout << "The trace of A is: " << trace << std::endl
                      << std::endl;
        } else {
            std::cerr << "The trace was NOT properly calculated: " << trace << std::endl;
            return EXIT_FAILURE;
        }
    }
    {
        const double expected_determinant = -20.0;
        const double determinant = A.determinant();
        if (are_close(determinant, expected_determinant, scalar_precision)) {
            std::cout << "The determinant of A is: " << determinant << std::endl
                      << std::endl;
        } else {
            std::cerr << "The determinant was NOT properly calculated: " << determinant << std::endl;
            return EXIT_FAILURE;
        }
    }
    {
        auto sym = A.symmetric();
        std::cout << "Symmetric matrix:\n"
                  << sym << std::endl;
        auto skew = A.skew_symmetric();
        std::cout << "Skew-symmetric matrix:\n"
                  << skew << std::endl;
        auto sum = sym + skew;
        std::cout << "Sum of the previous matrices:\n"
                  << sum << std::endl;
        if (sym.is_symmetric() && skew.is_skew_symmetric() && (A == sum)) {
            std::cout << "The symmetric and skew-symmetric matrices were properly calculated!\n";
        } else {
            std::cerr << "The symmetric and skew-symmetric matrices were NOT properly calculated!\n";
            return EXIT_FAILURE;
        }
    }
    {
        const auto inv = A.inverse();
        std::cout << "Inverse matrix:\n"
                  << inv << std::endl;
        const auto mul = A * inv;
        std::cout << "A * matrix_inverse(A) =\n"
                  << mul << std::endl;
        const auto identity = Matrix<double>::identity(A.rows());
        std::cout << "identity =\n"
                  << identity << std::endl;
        if (mul == identity) {
            std::cout << "The inverse matrix was properly calculated!\n";
        } else {
            std::cerr << "The inverse matrix was NOT properly calculated!\n";
            return EXIT_FAILURE;
        }
    }
    {
        A *= 2.0;
        std::cout << "Matrix A scaled by 2 is:\n"
                  << A << std::endl;
        Matrix<double> C(3, 3);
        std::cout << "Matrix C is random:\n"
                  << C.random(0.0, 1.0) << std::endl;
        Matrix<double> D(3, 3);
        D = 100.0;
        std::cout << "Matrix D is initialized:\n"
                  << D << std::endl;
        auto E = A + B;
        std::cout << "Matrix E = (A + B):\n"
                  << E << std::endl;
        auto F = A - B;
        std::cout << "Matrix F = (A - B):\n"
                  << F << std::endl;
    }
    return EXIT_SUCCESS;
}