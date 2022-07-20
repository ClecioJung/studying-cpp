#include "../lib/linked-list.hpp"

#include <cstdlib>
#include <iostream>

int main(void) {
    Linked_List list;
    std::cout << "Linked list before insertion:\n"
              << list << std::endl;
    Linked_List::Node &third = list.insert_new_tail(3);
    list.insert_new_head(2);
    list.insert_new_head(1);
    Linked_List::Node &fourth = list.insert_after(third, 4);
    list.insert_after(fourth, 5);
    list.insert_new_tail(6);
    std::cout << "Linked list after insertion:\n"
              << list << std::endl;
    try {
        Linked_List::Node found = list.find(8);
        std::cout << "find 8 in list results in address " << static_cast<void *>(&found) << std::endl;
    } catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    Linked_List::Node &found = list.find(3);
    std::cout << "find 3 in list results in address " << static_cast<void *>(&found) << " with value " << found.value << std::endl;
    list.del(found);
    std::cout << "\nLinked list after deletion of element with value 3:\n"
              << list << std::endl;
    return EXIT_SUCCESS;
}