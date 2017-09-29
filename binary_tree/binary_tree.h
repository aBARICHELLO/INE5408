#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <vector>
#include <cstdint>

namespace structures {

template<typename T>
//! Binary Tree
class BinaryTree {
 public:
    //! Destructor
    ~BinaryTree() {
        while (!empty()) {
            remove();
        }
    }

    //! Insert
    void insert(const T& data);

    //! Remove
    void remove(const T& data);

    //! Contains
    bool contains(const T& data) const {
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
    std::vector<T> pre_order() const;

    //! Normal order
    std::vector<T> in_order() const;

    //! Post ordered
    std::vector<T> post_order() const;

 private:
    struct Node {
        //! Node
        explicit Node(const T& data) {
            this->data = data;
        }

        //! Insert
        void insert(const T& data_) {
            if (data < data_) {
                if (left == nullptr) {
                    left = new Node(data);
                } else {
                    left->insert(data);
                }
            } else {
                if (right == nullptr) {
                    right = new Node(data);
                } else {
                    right->insert(data);
                }
            }        
        }
        
        //! Remove
        bool remove(const T& data_) {
            // First find the node:
        }
        
        //! Contains
        bool contains(const T& data_) const {
            if(data_ == data) {
                return true;
            } else if (data_ < data) {
                return left == nullptr ? false : left->contains(data);
            } else if (data_ > data) {
                return right == nullptr ? false : right->contains(data);
            }
            return false;
        }
        
        //! Pre order
        void pre_order(std::vector<T>& v) const;
        
        //! Normal order
        void in_order(std::vector<T>& v) const;
        
        //! Post order
        void post_order(std::vector<T>& v) const;
        
        T data;
        Node* left;
        Node* right;
    };

    Node* root;
    std::size_t size_;
};

} // namespace structures

#endif
