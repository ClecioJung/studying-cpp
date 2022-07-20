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

#ifndef __LINKED_LIST_CPP
#define __LINKED_LIST_CPP

#include <cstring>
#include <functional>
#include <sstream>

template <typename Number>
class Linked_List {
   public:
    class Node;

    Linked_List(void) : head(nullptr), tail(nullptr) {}
    ~Linked_List(void);
    std::string to_string(void) const;
    Node &insert_new_head(const Number value);
    Node &insert_new_tail(const Number value);
    Node &insert_before(Node &next, const Number value);
    Node &insert_after(Node &previous, const Number value);
    Node &find(const Number value);
    Node &reverse_find(const Number value);
    void del(Node &previous);

    // Iterators
    class List_Iterator;
    List_Iterator begin(void);
    List_Iterator end(void);

   private:
    Node *head;
    Node *tail;
};

template <typename Number>
class Linked_List<Number>::Node {
   private:
    Node *next;
    Node *previous;

   public:
    friend class Linked_List;

    Number value;

    Node(Number value, Node *next, Node *previous) : next(next), previous(previous), value(value) {}
};

template <typename Number>
class Linked_List<Number>::List_Iterator {
   private:
    Node *current;

   public:
    List_Iterator(Node *current) : current(current) {}
    Number &operator*(void) { return current->value; }
    List_Iterator &operator++(void) {
        if (current != nullptr) {
            current = current->next;
        }
        return *this;
    }
    List_Iterator &operator--(void) {
        if (current != nullptr) {
            current = current->previous;
        }
        return *this;
    }
    bool operator!=(const List_Iterator &it) const { return (current != it.current); }
    bool operator==(const List_Iterator &it) const { return (current == it.current); }
};

template <typename Number>
typename Linked_List<Number>::List_Iterator
Linked_List<Number>::begin(void) {
    return List_Iterator(head);
}

template <typename Number>
typename Linked_List<Number>::List_Iterator
Linked_List<Number>::end(void) {
    return List_Iterator(nullptr);
}

template <typename Number>
Linked_List<Number>::~Linked_List(void) {
    Node *current = head;
    while (current != nullptr) {
        Node *next = current->next;
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
}

template <typename Number>
std::ostream &operator<<(std::ostream &os, const Linked_List<Number> &list) {
    return os << list.to_string();
}

template <typename Number>
std::string Linked_List<Number>::to_string(void) const {
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

template <typename Number>
typename Linked_List<Number>::Node &
Linked_List<Number>::insert_new_head(const Number value) {
    Node *node = new Node(value, head, nullptr);
    if (head != nullptr) {
        head->previous = node;
    }
    head = node;
    if (tail == nullptr) {
        tail = node;
    }
    return *node;
}

template <typename Number>
typename Linked_List<Number>::Node &
Linked_List<Number>::insert_new_tail(const Number value) {
    Node *node = new Node(value, nullptr, tail);
    if (tail != nullptr) {
        tail->next = node;
    }
    tail = node;
    if (head == nullptr) {
        head = node;
    }
    return *node;
}

template <typename Number>
typename Linked_List<Number>::Node &
Linked_List<Number>::insert_before(Node &next, const Number value) {
    Node *node = new Node(value, &next, next.previous);
    Node *previous = next.previous;
    next.previous = node;
    if (previous != nullptr) {
        previous->next = node;
    }
    if (head == &next) {
        head = node;
    }
    return *node;
}

template <typename Number>
typename Linked_List<Number>::Node &
Linked_List<Number>::insert_after(Node &previous, const Number value) {
    Node *node = new Node(value, previous.next, &previous);
    Node *next = previous.next;
    previous.next = node;
    if (next != nullptr) {
        next->previous = node;
    }
    if (tail == &previous) {
        tail = node;
    }
    return *node;
}

template <typename Number>
typename Linked_List<Number>::Node &
Linked_List<Number>::find(const Number value) {
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

template <typename Number>
typename Linked_List<Number>::Node &
Linked_List<Number>::reverse_find(const Number value) {
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

template <typename Number>
void Linked_List<Number>::del(Node &node) {
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

#endif  // __LINKED_LIST_CPP

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