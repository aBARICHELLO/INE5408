// Copyright [2017] <Barichello>
/* Sources:
Sanfoundry.com/cpp-program-implement-avl-trees/

*/
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
    ~AVLTree() {
        while (!empty()) {
            remove(root->node_data);
        }
    }

    //! Insert
    void insert(const T& node_data) {
        if (empty()) {
            root = new Node(node_data);
        } else {
            root->insert(node_data);
        }
        ++size_;
    }

    //! Remov
    void remove(const T& node_data) {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }
        root->remove(node_data);
        --size_;
    }

    //! Contains
    bool contains(const T& node_data) const {
        if (empty()) {
            return false;
        }
        return root->contains(node_data);
    }

    //! Empty
    bool empty() const {
        return size_ == 0;
    }

    //! Size
    std::size_t size() const {
        return size_;
    }

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
        void update_height() {
            std::size_t height_left, height_right;
            if (!left && !right) {
                height = 0;
            } else {
                if (!left) {
                    left->updateHeight();
                    switch (left->balance_type()) {
                        case 0: // Balanced, update heights
                            height_left = height(left->left);
                            height_right = height(left->right);
                            left->height = std::max(height_left, height_right) + 1;
                            break;
                        case 1: // Left left
                            break;
                        case 2: // Left right
                            break;
                        case 3: // Right right
                            break;
                        case 4: // Right right
                            break;
                    }
                }
            }
        }

        /*! Returns the type of the balance:
        0 : Balanced
        1 : Left-Left
        2 : Left-Right
        3 : Right-Right
        4 : Right-Left
        */
        std::size_t balance_type() {
            if (height(left) - height(right) > 1) {
                if (height(left->left) > height(left->right)) {
                    return 1;
                }
                else {
                    return 2;
                }
            } else if (height(right) - height(left) > 1) {
                if (height(right->right) > height(right->left)) {
                    return 3;
                } else {
                    return 4;
                }
            }
            return 0; // Balanced tree
        }

        //! Returns the height of the node
        int get_height(Node* node) {
            return node == nullptr ? -1 : node->height;
        }

        //! Simple left
        Node* simple_left() {
            Node* temp_node = left;
            left = temp_node->right;
            temp_node->right = this;

            height = std::max(height(left), height(right) + 1);
            temp_node->height = std::max(height(temp_node->left), height(this)) + 1;
        }

        //! Simple right
        Node* simple_right() {
            Node* temp_node = right;
            right = temp_node->left;
            temp_node->left = this;

            height = std::max(height(right), height(left) + 1);
            temp_node->height = std::max(height(temp_node->right), height(this)) + 1;
        }

        //! Double left
        Node* double_left() {
            left = left->simple_right();
            return this->simple_left();
        }

        //! Double right
        Node* double_right() {
            right = right->simple_left();
            return this->simple_right();
        }

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
        void in_order(std::vector<T>& v) const {
            if (left) {
                left->pre_order(v);
            }
            v.push_back(node_data);
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
            v.push_back(node_data);
        }

        T node_data;
        std::size_t height;
        Node* left{nullptr};
        Node* right{nullptr};
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
