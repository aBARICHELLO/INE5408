#include "doubly_linked_list.h"
#include <iostream>

int main() {
    structures::DoublyLinkedList<int> list{};
    
    for (auto i = 9; i > 0; --i) {
        list.insert_sorted(i);
    }
    
    
    for (auto i = 0; i < 10; ++i) {
        std::cout << list.at(i) << "\n";
    }

    return 0;
}