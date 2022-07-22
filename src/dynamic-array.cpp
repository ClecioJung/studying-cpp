#include "../lib/dynamic-array.hpp"

#include <cstdlib>
#include <iostream>

int main(void) {
    Dynamic_Array<int> array;
    std::cout << "Array before insertion:\n"
              << array << std::endl;
    for (int i = 0; i < 16; i++) {
        array.push(i);
    }
    std::cout << "Array after insertion:\n"
              << array << std::endl;
    std::cout << "Pop a value from array: " << array.pop() << std::endl;
    std::cout << "Array after pop:\n"
              << array << std::endl;
    std::cout << "Value at index 5: " << array.value_at(5) << std::endl;
    std::cout << "Find value 10 at position " << array.find(10) << std::endl;
    array.delete_at(2);
    std::cout << "\nArray after delete element at position 2:\n"
              << array << std::endl;
    std::cout << "Shift a value from array: " << array.shift() << std::endl;
    std::cout << "Array after shift:\n"
              << array << std::endl;
    for (int i = 0; i < 5; i++) {
        array.unshift(100 + i);
    }
    std::cout << "Array after insertion at the beginning:\n"
              << array << std::endl;
    std::cout << "For each loop in the array:\n";
    for (auto value : array) {
        std::cout << value << ", ";
    }
    std::cout << std::endl;
    return EXIT_SUCCESS;
}