#include "../lib/linked-list.hpp"

#include <cstdlib>
#include <iostream>

int main(void) {
    Linked_List<int> list;
    std::cout << "Linked list before insertion:\n"
              << list << std::endl;
    auto &third = list.insert_new_tail(3);
    list.insert_new_head(2);
    list.insert_new_head(1);
    auto &fourth = list.insert_after(third, 4);
    list.insert_after(fourth, 5);
    list.insert_new_tail(6);
    std::cout << "Linked list after insertion:\n"
              << list << std::endl;
    try {
        auto found = list.find(8);
        std::cout << "find 8 in list results in address " << static_cast<void *>(&found) << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    auto &found = list.find(3);
    std::cout << "find 3 in list results in address " << static_cast<void *>(&found) << " with value " << found.value << std::endl;
    list.del(found);
    std::cout << "\nLinked list after deletion of element with value 3:\n"
              << list << std::endl;
    std::cout << "For each loop in the linked list:\n";
    for (auto &value : list) {
        std::cout << value << " - ";
        if (value == 5) {
            value = 8;
        }
    }
    std::cout << "\n\nLinked list after changing value 5 to 8:\n"
              << list << std::endl;
    return EXIT_SUCCESS;
}