// Copyright [2017] <Artur Barichello>
#ifndef STRUCTURES_DOUBLY_LINKED_LIST_H
#define STRUCTURES_DOUBLY_LINKED_LIST_H

#include <cstdlib>
#include <stdexcept>

namespace structures {

template<typename T>
//! DoublyLinkedList class
class DoublyLinkedList {
 public:
    //! Constructor
    DoublyLinkedList() = default;

    //! Destructor
    ~DoublyLinkedList() {
        clear();
    }

    //! Clears the list
    void clear() {
        auto current_node = head;

        for (auto i = 0u; i < size(); ++i) {
            auto aux = current_node;
            current_node = current_node->next();
            delete aux;
        }
        size_ = 0;
    }

    //! Push back
    void push_back(const T& data) {
        auto new_node = new Node{data};
        if (empty()) {
            head = new_node;
            tail = new_node;
            ++size_;
            return;
        }

        auto old_tail = tail;
        tail = new_node;
        new_node->prev(old_tail);
        old_tail->next(new_node);

        ++size_;
    }

    //! Push front
    void push_front(const T& data) {
        auto new_node = new Node{data};
        if (empty()) {
            head = new_node;
            tail = new_node;
            ++size_;
            return;
        }

        auto old_head = head;
        head = new_node;
        new_node->next(old_head);
        old_head->prev(head);

        ++size_;
    }

    //! Inserts at given position
    void insert(const T& data, std::size_t index) {
        if (empty() || index == 0) {
            return push_front(data);
        } else if (index == size()) {
            return push_back(data);
        } else if (index < 0 || index > size()) {
            throw std::out_of_range("Index out of range!");
        }

        auto previous_node = head;
        for (auto i = 0; i < index-1; ++i) {
            previous_node = previous_node->next();
        }

        auto next_node = previous_node->next();
        auto new_node = new Node{data, previous_node, next_node};

        previous_node->next(new_node);
        next_node->prev(new_node);

        ++size_;
    }

    //! Insert sorted
    void insert_sorted(const T& data) {
        // TODO
    }

    //! Pops at a given position
    T pop(std::size_t index) {
        if (empty() || index < 0 || index > size()) {
            throw std::out_of_range("Out of range!");
        }

        auto previous_node = head;
        for (auto i = 0u; i < index-1; ++i) {
            previous_node = previous_node->next();
        }

        auto delete_node = previous_node->next();
        auto next_node = delete_node->next();

        auto delete_data = delete_node->data();

        previous_node->next(next_node);
        next_node->prev(previous_node);

        --size_;
        delete delete_node;
        return delete_data;
    }

    //! Pop at size()
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto old_tail = tail;
        auto old_data = tail->data();
        tail = tail->prev();

        --size_;
        delete old_tail;
        return old_data;
    }

    //! Pop at 0
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto old_head = head;
        auto old_data = head->data();
        head = head->next();

        --size_;
        delete old_head;
        return old_data;
    }

    //! Removes element from the list
    void remove(const T& data) {
        auto index = find(data);
        pop(index);
    }

    //! Empty
    bool empty() const {
        return size_ == 0;
    }

    //! Contains a specific element
    bool contains(const T& data) const {
        auto current_node = head;

        for (auto i = 0u; i < size()-1; ++i) {
            if (current_node->data() == data) {
                return true;
            }
            current_node = current_node->next();
        }
        return false;
    }

    //! Acess the element at the given index
    T& at(std::size_t index) {
        if (index < 0 || index > size()) {
            throw std::out_of_range("Wrong index!");
        }

        auto current_node = head;
        for (auto i = 0u; i < index; i++) {
            current_node = current_node->next();
        }

        return current_node->data();
    }

    //! At
    const T& at(std::size_t index) const {
        if (index < 0 || index > size()) {
            throw std::out_of_range("Wrong index!");
        }

        auto current_node = head;
        for (auto i = 0u; i < index; i++) {
            current_node = current_node->next();
        }

        return current_node->data();
    }

    //! Returns specific element index
    std::size_t find(const T& data) const {
        auto current_node = head;

        for (auto i = 0u; i < size(); ++i) {
            if (current_node->data() == data) {
                return i;
            }
            current_node = current_node->next();
        }
        return 10;
    }

    //! Returns std::size_t size_
    std::size_t size() const {
        return size_;
    }

 private:
    class Node {
     public:
        //! Constructor
        explicit Node(const T& data, Node* prev = nullptr,
            Node* next = nullptr):
            data_{data}
        {}

        //! Return data w/o const
        T& data() {
            return data_;
        }

        //! Return data const
        const T& data() const {
            return data_;
        }

        //! Setter for previous node
        void prev(Node* node) {
            prev_ = node;
        }

        //! Return prev w/o const
        Node* prev() {
            return prev_;
        }

        //! const Getter for previous node
        const Node* prev() const {
            return prev_;
        }

        //! Setter for next node
        void next(Node* node) {
            next_ = node;
        }

        //! Getter for next node w/o const
        Node* next() {
            return next_;
        }

        //! const Getter for next node
        const Node* next() const {
            return next_;
        }

     private:
        T data_;
        Node* prev_;
        Node* next_;
    };

    Node* head;
    Node* tail;
    std::size_t size_;
};

}  // namespace structures

#endif
