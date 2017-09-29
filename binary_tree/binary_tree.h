// Copyright [2017] <Barichello>

#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <vector>
#include <cstdint>
#include <stdexcept>

namespace structures {

template<typename T>
//! Binary Tree
class BinaryTree {
 public:
    //! Destructor
    ~BinaryTree() {
        while (!empty()) {
            remove(root->data);
        }
    }

    //! Insert
    void insert(const T& data) {
        if (empty()) {
            root = new Node(data);
        } else {
            root->insert(data);
        }
        ++size_;
    }

    //! Remove
    void remove(const T& data) {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }
        root->remove(data);
        --size_;
    }

    //! Contains
    bool contains(const T& data) const {
        if (empty()) {
            return false;
        }
        return root->contains(data);
    }

    //! Empty
    bool empty() const {
        return size() == 0;
    }

    //! Size
    std::size_t size() const {
        return size_;
    }

    //! Pre ordered
    std::vector<T> pre_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->pre_order(vector);
        }
        return vector;
    }

    //! Normal order
    std::vector<T> in_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->pre_order(vector);
        }
        return vector;
    }

    //! Post ordered
    std::vector<T> post_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->pre_order(vector);
        }
        return vector;
    }

 private:
    struct Node {
        //! Node
        explicit Node(const T& data) {
            this->data = data;
        }

        //! Insert
        void insert(const T& data_) {
            if (data_ <= data) {
                if (left == nullptr) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else {
                if (right == nullptr) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        //! Remove
        bool remove(const T& data_) {
            return true;
        }

        //! Contains
        bool contains(const T& data_) const {
            if (data_ < data) {
                return left == nullptr ? false : left->contains(data);
            } else if (data_ > data) {
                return right == nullptr ? false : right->contains(data);
            }
            return true;
        }

        //! Pre order
        void pre_order(std::vector<T>& v) const {
            v.push_back(data);
            if (left) {
                left->pre_order(v);
            }
            if (right) {
                right->pre_order(v);
            }
        }

        //! Normal order
        void in_order(std::vector<T>& v) const {
            if (left) {
                left->pre_order(v);
            }
            v.push_back(data);
            if (right) {
                right->pre_order(v);
            }
        }

        //! Post order
        void post_order(std::vector<T>& v) const {
            if (left) {
                left->pre_order(v);
            }
            if (right) {
                right->pre_order(v);
            }
            v.push_back(data);
        }

        T data;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

#endif
