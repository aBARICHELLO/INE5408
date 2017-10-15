// Copyright [2017] <Barichello>

#ifndef STRUCTURES_AVL_TREE
#define STRUCTURES_AVL_TREE

#include <vector>
#include <stdexcept>
#include "array_list.h"

namespace structures {
template<typename T>
//! avl class
class AVLTree {
public:
    //! Destructor
    ~AVLTree();

    //! Insert
    void insert(const T& node_data);

    //! Remov
    void remove(const T& node_data);

    //! Contains
    bool contains(const T& node_data) const;

    //! Empty
    bool empty() const;

    //! Size
    std::size_t size() const;

    //! Pre order
    std::vector<T> pre_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->pre_order(vector);
        }
        return vector;
    }

    //! In order
    std::vector<T> in_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->in_order(vector);
        }
        return vector;
    }

    //! Post order
    std::vector<T> post_order() const {
        auto vector = std::vector<T>{};
        if (!empty()) {
            root->post_order(vector);
        }
        return vector;
    }

private:
    //! Node struct
    struct Node {
        //! Node constructor
        explicit Node(const T& node_data):
            node_data(node_data)
        {}

        //! Node destructor
        ~Node() {
            delete node_data;
            if (left != nullptr) {
                delete left;
            }
            if (right != nullptr) {
                delete right;
            }
        }

        //! Node insert
        void insert(const T& data_) {
            if (data_ <= node_data) {
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

        //! Node remove
        bool remove(const T& data_) {
            if (data_ == node_data) {
                node_data = T{};
                return true;
            } else if (data_ < node_data) {
                return (left) and left->remove(data_);
            } else {
                return (right) and right->remove(data_);
            }
        }

        //! Contains
        bool contains(const T& data_) const {
            if (data_ < node_data) {
                return left == nullptr ? false : left->contains(data_);
            } else if (data_ > node_data) {
                return right == nullptr ? false : left->contains(data_);
            } else {
                return true;
            }
        }

        //! Height
        void updateHeight() ;

        //! Simple left
        Node* simpleLeft() ;

        //! Simple right
        Node* simpleRight() ;

        //! Double left
        Node* doubleLeft() ;

        //! Double right
        Node* doubleRight() ;

        //! Pre order
        void pre_order(std::vector<T>& v) const {
            v.push_back(node_data);
            if (left) {
                left->pre_order(v);
            }
            if (right) {
                right->pre_order(v);
            }
        }

        //! In order
        void in_order(ArrayList<T>& v) const {
            if (left) {
                left->pre_order(v);
            }
            v.push_back(node_data);
            if (right) {
                right->pre_order(v);
            }
        }

        //! Post order
        void post_order(ArrayList<T>& v) const {
            if (left) {
                left->pre_order(v);
            }
            if (right) {
                right->pre_order(v);
            }
            v.push_back(node_data);
        }

        T node_data;
        std::size_t height{0};
        Node* left{nullptr};
        Node* right{nullptr};
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

#endif
