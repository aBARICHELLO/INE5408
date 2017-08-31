// Copyright [2017] <Artur Barichello>
#ifndef STRUCTURES_LINKED_STACK_H
#define STRUCTURES_LINKED_STACK_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! LinkedStack class
class LinkedStack {
 public:
    LinkedStack() {}

    ~LinkedStack() {
        clear();
    }

    //! Clears the list
    void clear() {
        auto current_node = top_;

        for (auto i = 0u; i < size(); ++i) {
            auto aux = current_node;
            current_node = current_node->next();
            delete aux;
        }
        size_ = 0;
    }

    //! Push
    void push(const T& data) {
        auto next_node = top_;
        auto new_node = new Node{data, next_node};
        top_ = new_node;
        size_++;
    }

    //! Pop
    T pop() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto temp_node = top_;
        auto temp_data = temp_node->data();
        top_ = top_->next();

        --size_;
        delete temp_node;
        return temp_data;
    }

    //! Returns the data at the top of the Stack
    T& top() const {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }
        return top_->data();
    }

    //! Empty stack
    bool empty() const {
        return size() == 0;
    }

    //! Number of elements in the stack
    std::size_t size() const {
        return size_;
    }

 private:
    //! Node class
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
        Node* next_;
    };

    Node* top_{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
