#include <cstdlib>
#include <iostream>
#include <vector>

#define DEFAULT_NUMBERS 10

bool is_prime(const int number) {
    if (number < 2) {
        return false;
    }
    for (int i = 2; i <= (number / 2); i++) {
        if ((number % i) == 0) {
            return false;
        }
    }
    return true;
}

int main(const int argc, const char *const argv[]) {
    const size_t numbers = (argc >= 2) ? atoi(argv[1]) : DEFAULT_NUMBERS;
    std::cout << "The first " << numbers << " prime numbers are:" << std::endl;
    std::vector<int> primes;
    for (int i = 0; primes.size() < numbers; i++) {
        if (is_prime(i)) {
            primes.push_back(i);
        }
    }
    for (auto value : primes) {
        std::cout << value << std::endl;
    }
    return EXIT_SUCCESS;
}