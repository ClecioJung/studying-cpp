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

#include <cstring>
#include <functional>
#include <sstream>

std::function<void(int)> func;

class Linked_List {
   public:
    struct Node {
        int value;
        Node *next;
        Node *previous;
    };

    Linked_List(void) : head(nullptr), tail(nullptr) {}
    ~Linked_List(void);
    std::string to_string(void) const;
    Node &insert_new_head(const int value);
    Node &insert_new_tail(const int value);
    Node &insert_before(Node &next, const int value);
    Node &insert_after(Node &previous, const int value);
    Node &find(const int value);
    Node &reverse_find(const int value);
    void del(Node &previous);

   private:
    Node *head;
    Node *tail;
};

Linked_List::~Linked_List(void) {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

std::ostream &operator<<(std::ostream &os, const Linked_List &list) {
    return os << list.to_string();
}

std::string Linked_List::to_string(void) const {
    std::ostringstream strs;
    size_t index = 0;
    Node *current = head;
    strs << "Head: " << static_cast<void *>(head) << " Tail: " << static_cast<void *>(tail) << std::endl;
    strs << "Index - Address - Value\n";
    while (current != nullptr) {
        strs << index << " - " << static_cast<void *>(current) << " - " << current->value << std::endl;
        current = current->next;
        index++;
    }
    return strs.str();
}

Linked_List::Node &Linked_List::insert_new_head(const int value) {
    Node *node = new Node;
    node->value = value;
    node->next = head;
    node->previous = nullptr;
    if (head != nullptr) {
        head->previous = node;
    }
    head = node;
    if (tail == nullptr) {
        tail = node;
    }
    return *node;
}

Linked_List::Node &Linked_List::insert_new_tail(const int value) {
    Node *node = new Node;
    node->value = value;
    node->next = nullptr;
    node->previous = tail;
    if (tail != nullptr) {
        tail->next = node;
    }
    tail = node;
    if (head == nullptr) {
        head = node;
    }
    return *node;
}

Linked_List::Node &Linked_List::insert_before(Node &next, const int value) {
    Node *node = new Node;
    node->value = value;
    node->next = &next;
    Node *previous = next.previous;
    node->previous = previous;
    next.previous = node;
    if (previous != nullptr) {
        previous->next = node;
    }
    if (head == &next) {
        head = node;
    }
    return *node;
}

Linked_List::Node &Linked_List::insert_after(Node &previous, const int value) {
    Node *node = new Node;
    node->value = value;
    node->previous = &previous;
    Node *next = previous.next;
    node->next = next;
    previous.next = node;
    if (next != nullptr) {
        next->previous = node;
    }
    if (tail == &previous) {
        tail = node;
    }
    return *node;
}

Linked_List::Node &Linked_List::find(const int value) {
    // Sequential search
    Node *current = head;
    while (current != nullptr) {
        if (current->value == value) {
            return *current;
        }
        current = current->next;
    }
    throw std::runtime_error("Didn't found the requested value in the linked list!");
}

Linked_List::Node &Linked_List::reverse_find(const int value) {
    // Sequential search
    Node *current = tail;
    while (current != nullptr) {
        if (current->value == value) {
            return *current;
        }
        current = current->previous;
    }
    throw std::runtime_error("Didn't found the requested value in the linked list!");
}

void Linked_List::del(Node &node) {
    Node *previous = node.previous;
    Node *next = node.next;
    if (previous != nullptr) {
        previous->next = next;
    }
    if (next != nullptr) {
        next->previous = previous;
    }
    if (head == &node) {
        head = next;
    }
    if (tail == &node) {
        tail = previous;
    }
    delete &node;
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