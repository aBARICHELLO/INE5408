// Copyright 2017 Barichello

#ifndef STRUCTURES_ARRAY_QUEUE_H
#define STRUCTURES_ARRAY_QUEUE_H

#include <cstdint>  // std::size_t
#include <stdexcept>  // C++ Exceptions

namespace structures {

template<typename T>
//! Class ArrayQueue
/*!
    Principal class
*/
class ArrayQueue {
 public:
    /*!  Constructor with parameters */
    explicit ArrayQueue(std::size_t max = DEFAULT_SIZE) {
        max_size_ = max;
        size_ = 0;
        contents = new T[max];
    }

    /*!  Destructor */
    ~ArrayQueue() {
        delete[] contents;
    }

    /*!  Enqueue */
    void enqueue(const T& data) {
        if (full())
            throw std::out_of_range("Queue is full");
        contents[size_++] = data;
    }

    /*!  Dequeue */
    T dequeue() {
        if (empty()) {
            throw std::out_of_range("Queue is empty");
        }

        T dequeued = contents[0];
        for (auto i = 0u; i < size()-1; ++i) {
            contents[i] = std::move(contents[i+1]);
        }
        --size_;

        return dequeued;
    }

    /*!  Back */
    T& back() {
        if (!empty()) {
            return contents[size()-1];
        }
        throw std::out_of_range("The queue is empty!");
    }

    /*!  Clear */
    void clear() {
        size_ = 0;
    }

    /*!  Size */
    std::size_t size() {
        return size_;
    }

    /*!  Max_Size */
    std::size_t max_size() {
        return max_size_;
    }

    /*!  Checks if the list is empty */
    bool empty() {
        return size() == 0;
    }

    /*!  Checks if the list is full */
    bool full() {
        return size() == max_size();
    }

 private:
    T* contents;
    std::size_t size_;
    std::size_t max_size_;

    static const auto DEFAULT_SIZE = 10u;
};
}  // namespace structures

#endif
