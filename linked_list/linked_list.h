// Copyright [2017] <Artur Barichello>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! LinkedList class
class LinkedList {
 public:
    //! Default constructor
    LinkedList() {}

    //! Destructor
    ~LinkedList() {}

    //! Clears the list
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    //! Inserts an element at size()
    void push_back(const T& data) {
        auto new_node = new Node{data};
        if (empty()) {
            head = new_node;
        } else {
            end()->next(new_node);
        }
        ++size_;
    }

    //! Inserts at 0
    void push_front(const T& data) {
        head = new Node{data, head};
        ++size_;
    }

    //! Inserts at the given index
    void insert(const T& data, std::size_t index) {
        if (index < 0 || index > size()) {
            throw std::out_of_range("Out of range!");
        } else if (index == 0) {
            push_front(data);
        } else {
            auto previous = head;
            for (auto i = 0; i < index-1; ++i) {
                previous = previous->next();
            }
            auto next_node = previous->next();
            auto new_node = new Node{data};
            new_node->next(next_node);
            previous->next(new_node);
        }
    }

    //! Inserts by sorting first
    void insert_sorted(const T& data) {
    }

    //! Returns the element at the given index
    T& at(std::size_t index) {
        if (index > size() || empty()) {
            throw std::out_of_range("Out of range");
        }

        auto current_node = head;
        for (auto i = 0u; i < index; ++i) {
            current_node = current_node->next();
        }
        return current_node->data();
    }

    //! Removes an element from the given index
    T pop(std::size_t index) {
    }

    //! Removes the last element
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }
        delete end();
        --size_;
    }

    //! Removes the first element
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }
        auto temp_node = head;
        head = head->next();
        --size_;
    }

    //! Removes from given index
    void remove(const T& data) {
    }

    //! Checks if the list is empty
    bool empty() const {
        return size() == 0;
    }

    //! Returns a boolean if the list contains the given data
    bool contains(const T& data) const {
    }

    //! Finds the index from the given data
    std::size_t find(const T& data) const {
        auto current_node = head;
        auto index = 0;

        while (index < size()) {
            if (current_node->data() == data) {
                break;
            }
        }
        ++index;
        return index;
    }

    //! Size of the list
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
        explicit Node(const T& data):
            data_{data}
        {}

        //! Node
        Node(const T& data, Node* next):
            data_{data},
            next_{next}
        {}

        //! Getter
        T& data() {
            return data_;
        }

        //! Getter const
        const T& data() const {
            return data_;
        }

        //! Next node
        Node* next() {
            return next_;
        }

        //! Getter const, next
        const Node* next() const {
            return next_;
        }

        //! Setter next
        void next(Node* node) {
            next_ = node;
        }

     private:
        T data_;
        Node* next_{nullptr};
    };

    //! Last node
    Node* end() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next();
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
