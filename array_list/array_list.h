//  Copyright [2017] <Barichello>

//  95.45/100.0
#ifndef STRUCTURES_ARRAY_LIST_H
#define STRUCTURES_ARRAY_LIST_H

#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
/*!  ArrayList class */
class ArrayList {
 public:
    //!  ArrayList constructor //
    explicit ArrayList(std::size_t max_size_ = DEFAULT_MAX) :
	   contents{new T[max_size_]}, max_size_{DEFAULT_MAX}, size_{0} {
    }

    //!  ArrayList destructor //
    ~ArrayList() {
        delete[] contents;
    }

    //!  Clears our array list //
    void clear() {
        size_ = 0;
    }

    //!  Inserts an element - back //
    void push_back(const T& data) {
        if (full())
            throw std::out_of_range("Full!");
        contents[size_++] = data;
    }

    //!  Inserts an element - front //
    void push_front(const T& data) {
        insert(data, 0);
    }

    //!  Inserts an element at an given position //
    void insert(const T& data, int index) {
        if (full() || index < 0 || index >= max_size())
            throw std::out_of_range("Out of range!");
        move_up(index);
        contents[index] = data;
        size_++;
    }

    //!  Inserts the element by ordering the array //
    void insert_sorted(const T& data) {
        if (empty()) {
            return push_front(data);
        }

        if (full()) {
            throw std::out_of_range("Full!");
        }

        
        auto index = 0u;
        while (index < size() && data > contents[index]) {
            ++index;
        }
        insert(data, index);
    }

    /*! Removes element from given index.
        Function moves one down starts shifting 
        from index*/
    T pop(std::size_t index) {
        if (empty() || index < 0 || index >= size())
            throw std::out_of_range("Out of range");
        T element = contents[index];
        move_down(index);
        size_--;
        return element;
    }

    //!  Removes element from back //
    T pop_back() {
        if (empty())
            throw std::out_of_range("Empty!");
        return contents[--size_];
    }

    //!  Remove selement from front //
    T pop_front() {
        return pop(0);
    }

    /*!  Receives data as a parameter, uses the find function
    to get the data index and removes it from the ArrayList */
    void remove(const T& data) {
        std::size_t dataIndex = find(data);
        pop(dataIndex);
    }

    //!  Checks if the arraylist is full //
    bool full() const {
        return size() == max_size();
    }

    //!  Checks if the arraylist is empty //
    bool empty() const {
        return size() == 0;
    }

    //!  Checks if the arraylist contains a given element //
    bool contains(const T& data) const {
        bool contains = false;
        for (auto a = 0u; a < size(); ++a) {
            if (data == contents[a]) {
                contains = true;
            }
        }
        return contains;
    }

    //!  Finds //
    std::size_t find(const T& data) const {
        for (auto a = 0; a <= size(); ++a) {
            if (contents[a] ==  data)
                return a;
        }
        return 10;
    }

    //!  Arraylist current size //
    std::size_t size() const {
        return size_;
    }

    //!  Arraylist max size //
    std::size_t max_size() const {
        return max_size_;
    }

    //!   //
    T& at(std::size_t index) {
        if (index > size() || index < 0)
            throw std::out_of_range("Out of range!");
        return contents[index];
    }

    //!   //
    T& operator[](std::size_t index) {
        return contents[index];
    }

    //!  Returns the data that is at the given index //
    const T& at(std::size_t index) const {
        if (index >= size() || index < 0)
            throw std::out_of_range("Out of range");
        return contents[index];
    }

    //!   //
    const T& operator[](std::size_t index) const {
        return contents[index];
    }

    /*! Moves elements down */
    void move_down(std::size_t position) {
        for (int i = position; i < size(); ++i) {
			contents[i] = contents[i+1];
        }
    }

    /*! Moves the elements up */
    void move_up(std::size_t position) {
        for (auto i = size(); i > position; --i) {
            contents[i] = std::move(contents[i-1]);
        }
    }

 private:
    T* contents;
    std::size_t max_size_;
    std::size_t size_;

    static const auto DEFAULT_MAX = 10u;
};
}  // namespace structures

#endif