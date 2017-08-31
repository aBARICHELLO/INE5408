// Copyright [2017] <Artur Barichello>
#ifndef STRUCTURES_LINKED_QUEUE_H
#define STRUCTURES_LINKED_QUEUE_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! LinkedQueue class
class LinkedQueue {
 public:
    LinkedQueue() = default;

    ~LinkedQueue() {
        clear();
    }

    //! Clear the queue
    void clear() {
        auto current_node = head;

        for (auto i = 0u; i < size(); ++i) {
            auto aux = current_node;
            current_node = current_node->next;
            delete aux;
        }
        size_ = 0;
    }

    //! Inserts into the queue
    void enqueue(const T& data) {
        Node* tail_ = tail();

        auto new_node = new Node{data};
        if (tail_) {
            tail_->next = new_node;
        } else {
            head = new_node;
        }
        ++size_;
    }

    //! Removes the item from the queue
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto data = head->data;
        auto delete_node = head;
        head = head->next;
        delete delete_node;
        --size_;
        return data;
    }

    //! First data from the queue
    const T& front() const {
    // Primeiro const = relação ao T, segundo é do retorno da função
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        return head->data;
    }

    //! Last data from the queue
    const T& back() const {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        return tail()->data;
    }

    //! Empty
    bool empty() const {
        return size_ == 0;
    }

    //! Size of the queue
    std::size_t size() const {
        return size_;
    }

 private:
    //! Node class
    class Node {
     public:
        //! Node with pointer
        explicit Node(const T& data, Node* next = nullptr):
            data{data},
            next{next}
        {}

        T data;
        Node* next;
    };

    //! Tail
    Node* tail() {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next;
        }
        return it;
    }

    const Node* tail() const {
        auto it = head;
        for (auto i = 1u; i < size(); ++i) {
            it = it->next;
        }
        return it;
    }

    Node* head{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
