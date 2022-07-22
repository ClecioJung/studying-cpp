#include "../lib/circular-buffer.hpp"

#include <iostream>

int main(void) {
    try {
        Circular_Buffer<int, 32> buf;
        std::cout << "Buffer before insertion:\n"
                  << buf << std::endl;
        for (int i = 0; i < 16; i++) {
            buf.push(i);
        }
        std::cout << "Buffer after insertion:\n"
                  << buf << std::endl;
        std::cout << "Pop a value from buffer: " << buf.pop() << std::endl;
        std::cout << "Buffer after pop:\n"
                  << buf << std::endl;
        std::cout << "Shift the 1st value from buffer: " << buf.shift() << std::endl;
        std::cout << "Shift the 2nd value from buffer: " << buf.shift() << std::endl;
        std::cout << "Buffer after shift:\n"
                  << buf << std::endl;
        for (int i = 0; i < 5; i++) {
            buf.unshift(105 - i);
        }
        std::cout << "Buffer after insertion at the beginning:\n"
                  << buf << std::endl;
        std::cout << "For each loop in the buffer:\n";
        for (auto& value : buf) {
            std::cout << value << ", ";
            if (value == 105) {
                value = 1050;
            }
        }
        std::cout << "\n\nBuffer after changing value 105 to 1050:\n"
                  << buf << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return EXIT_SUCCESS;
}
