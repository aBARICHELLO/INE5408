// Copyright 2017 Barichello
#ifndef STRUCTURES_ARRAY_STACK_H
#define STRUCTURES_ARRAY_STACK_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ exceptions

namespace structures {

template<typename T>
//!  Classe ArrayStack
/*!
    Principal class
*/
class ArrayStack {
 public:
    /*!  ArrayStack constructor with parameters  */
    explicit ArrayStack(std::size_t max = DEFAULT_SIZE) {
        top_ = 0;
        max_size_ = max;
        contents = new T[max_size_];
    }

    /*!  Destructor */
    ~ArrayStack() {
        delete[] contents;
    }

    /*!  Push an element to the top of the stack */
    void push(const T& data) {
        if (full())
            throw std::out_of_range("Full");
        contents[top_++] = data;
    }

    /*!  Pop an element from the top of the stack */
    T pop() {
        if (empty())
            throw(std::out_of_range("The stack is empty!"));
        return contents[--top_];
    }

    /*!  Returns the value from Top */
    T& top() {
        return contents[top_ - 1];
    }

    /*!  Clears the top variable */
    void clear() {
        top_ = 0;
    }

    /*!  Returns the size of the stack */
    std::size_t size() {
        return top_;
    }

    /*!  Numbers that can fit in the stack */
    std::size_t max_size() {
        return max_size_;
    }

    /*!  Checks if the Stack is empty */
    bool empty() {
        return size() == 0;
    }

    /*!  CHecks if the Stack is full */
    bool full() {
        return size() == max_size();
    }

 private:
    T* contents;
    std::size_t top_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};
}  // namespace structures

#endif
