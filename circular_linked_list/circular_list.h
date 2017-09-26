// Copyright [2017] <Artur Barichello>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

template<typename T>
class CircularList {
 public:
    //! Constructor
    CircularList() = default;

    //! Destructor
    ~CircularList() {
        clear();
    }

    //! Clears the list
    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    //! Inserts an element at size()
    void push_back(const T& data) {
        auto new_node = new Node{data};
        if (empty()) {  // Make the node point to itself.
            head = new_node;
            head->next(new_node);
        } else {
            auto previous_node = head;
            for (auto i = 0u; i < size()-1; ++i) {
                previous_node = previous_node->next();
            }
            previous_node->next(new_node);
            new_node->next(head);  // Circular
        }
        ++size_;
    }

    //! Inserts at 0
    void push_front(const T& data) {
        auto new_node = new Node{data, head};
        head = new_node;
        ++size_;
    }

    //! Inserts at the given index
    void insert(const T& data, std::size_t index) {
        if (index < 0 || index > size()) {
            throw std::out_of_range("Out of range!");
        } else if (index == 0 || empty()) {
            return push_front(data);
        }

        auto previous = head;
        for (auto i = 0; i < index-1; ++i) {
            previous = previous->next();
        }

        auto next_node = previous->next();
        auto new_node = new Node{data, next_node};
        previous->next(new_node);
        ++size_;
    }

    //! Inserts by sorting first
    void insert_sorted(const T& data) {
        auto current_node = head;
        auto index = 0;
        while (index < size() && data > current_node->data()) {
            current_node = current_node->next();
            ++index;
        }
        insert(data, index);
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
        if (empty() || index < 0 || index >= size()) {
            throw std::out_of_range("Out of range!");
        }

        if (index == 1) {
            return pop_front();
        }

        auto previous_node = head;
        for (auto i = 0u; i < index-1; ++i) {
            previous_node = previous_node->next();
        }

        auto delete_node = previous_node->next();
        auto delete_node_data = delete_node->data();
        auto next_node = delete_node->next();

        previous_node->next(next_node);
        --size_;
        delete delete_node;
        return delete_node_data;
    }

    //! Removes the last element
    T pop_back() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto current_node = head;
        for (auto i = 0u; i < size()-1; ++i) {
            current_node = current_node->next();
        }

        current_node->next(head);
        auto end_data = current_node->data();

        delete current_node;
        --size_;
        return end_data;
    }

    //! Removes the first element
    T pop_front() {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto temp_node = head;
        auto temp_data = temp_node->data();
        head = head->next();

        --size_;
        delete temp_node;
        return temp_data;
    }

    //! Removes from given index
    void remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }

        auto index = find(data);
        pop(index);
    }

    //! Checks if the list is empty
    bool empty() const {
        return size() == 0;
    }

    //! Returns a boolean if the list contains the given data
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

    //! Finds the index from the given data
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

    Node* head{nullptr};
    std::size_t size_{0u};
};

#endif
