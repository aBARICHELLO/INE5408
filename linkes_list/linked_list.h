// Copyright [2017] <Artur Barichello>
#ifndef STRUCTURES_LINKED_LIST_H
#define STRUCTURES_LINKED_LIST_H

#include <cstdint>


namespace structures {

template<typename T>
//! LinkedList class
class LinkedList {
 public:
    //! Default constructor
    LinkedList() {
    }

    //! Destructor
    ~LinkedList() {
    }

    //! Clears the list
    void clear() {
    }

    //! Inserts an element at size()
    void push_back(const T& data) {
    }

    //! Inserts at 0
    void push_front(const T& data) {
    }

    //! Inserts at the given index
    void insert(const T& data, std::size_t index) {
    }

    //! Inserts by sorting first
    void insert_sorted(const T& data) {
    }

    //! Returns the element at the given index
    T& at(std::size_t index) {
    }

    //! Removes an element from the given index
    T pop(std::size_t index) {
    }

    //! Removes the last element
    T pop_back() {
    }

    //! Removes the first element
    T pop_front() {
    }

    //! Removes from given index
    void remove(const T& data) {
    }

    //! Checks if the list is empty
    bool empty() const {
    }

    //! Returns a boolean if the list contains the given data
    bool contains(const T& data) const {
    }

    //! Finds the index from the given data
    std::size_t find(const T& data) const {
    }

    //! Size of the list
    std::size_t size() const {
    }

 private:
    class Node {  // Elemento
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
