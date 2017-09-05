// Copyright [2017] <Artur Barichello>
#ifndef STRUCTURES_CIRCULAR_LIST_H
#define STRUCTURES_CIRCULAR_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Circular List class
class CircularList {
 public:
    //! Constructor
    CircularList();
    
    //! Destructor
    ~CircularList();

    //! Clears
    void clear();

    //! Push back
    void push_back(const T& data);
    
    //! Push front
    void push_front(const T& data);
    
    //! Inserts
    void insert(const T& data, std::size_t index);
    
    //! Sorted insert
    void insert_sorted(const T& data);

    //! Returns the element at the given index
    T& at(std::size_t index);
    
    //! Returns element at the given index (const)
    const T& at(std::size_t index) const;

    //! Pop
    T pop(std::size_t index);
    
    //! Pop back
    T pop_back();
    
    //! Pop front
    T pop_front();
    
    //! Removes an element from the list
    void remove(const T& data);

    //! Empty check
    bool empty() const;
    
    //! Checks if the list onstains the given data parameter
    bool contains(const T& data) const;
    
    //! Finds the index of the given parameter
    std::size_t find(const T& data) const;

    //! Number of elements that the list is currently holding
    std::size_t size() const;

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
    Node* tail{nullptr};
    std::size_t size_{0u};
};

} // namespace structures

#endif
