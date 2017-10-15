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

        int height_left, height_right;
        root->update_height();
        switch (root->balance_type()) {
            case 0:
                height_left = root->get_height(root->left);
                height_right = root->get_height(root->right);
                root->height = std::max(height_left, height_right) + 1;
                break;
            case 1:
                root = root->simple_left();
                break;
            case 2:
                root = root->double_left();
                break;
            case 3:
                root = root->simple_right();
                break;
            case 4:
                root = root->double_right();
                break;
            default:
                break;
        }
    }

    //! Remov
    void remove(const T& node_data) {
        if (empty()) {
            throw std::out_of_range("Empty!");
        }
        
        if (size() != 1) {
            if (root->remove(node_data)) {
                --size_;
                int height_left, height_right;
                root->update_height();
                switch (root->balance_type()) {
                    case 0:
                        height_left = root->get_height(root->left);
                        break;
                }
            }
        }
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
            node_data{node_data}
        {}

        //! Node destructor
        ~Node() {
            //delete node_data;
            if (left != nullptr) {
                delete left;
            }
            if (right != nullptr) {
                delete right;
            }
        }
        
        T node_data;
        std::size_t height{0};
        Node* left{nullptr};
        Node* right{nullptr};

        //! Node insert
        void insert(const T& data_) {
            if (data_ <= node_data) {
                if (!left) {
                    left = new Node(data_);
                } else {
                    left->insert(data_);
                }
            } else {
                if (!right) {
                    right = new Node(data_);
                } else {
                    right->insert(data_);
                }
            }
        }

        Node* remove(const T& data, Node* arv, bool& deleted) {
            deleted = false;
            if (arv == nullptr)
                return arv;
            // Go to left
            if (data < arv->node_data) {
                arv->left = remove(data, arv->left, deleted);
                return arv;
            }
            // Go to right
            if (data > arv->node_data) {
                arv->right = remove(data, arv->right, deleted);
                return arv;
            }
            // I found
            // Two sons
            if (arv->right != nullptr && arv->left != nullptr) {
                Node* temp = arv->right->minimum();
                arv->node_data = temp->node_data;
                arv->right = remove(data, arv->right, deleted);
                return arv;
            }
            // One son or leaf
            Node* temp = nullptr;
            if (arv->right != nullptr)
                temp = arv->right;
            else
                temp = arv->left;

            arv->right = arv->left = nullptr;
            delete arv;
            deleted = true;
            return temp;
        }

        //! Node remove
        bool remove(const T& data_) {
            bool deleted = false;
            if (data_ < node_data && left != nullptr) {
                left = remove(node_data, left, deleted);
            } else if (data_ > node_data && right != nullptr) {
                right = remove(node_data, right, deleted);
            } else if (data_ == node_data) {
                if (right != nullptr && left != nullptr) {
                    Node* temp = right->minimum();
                    node_data = temp->node_data;
                    right = remove(node_data, right, deleted);
                } else if (right != nullptr) {
                    Node* temp = right->minimum();
                    node_data = temp->node_data;
                    right = temp->right;
                    left = temp->left;
                    temp->right = temp->left = nullptr;
                    delete temp;
                    deleted = true;
                } else if (left != nullptr) {
                    Node* temp = left;
                    node_data = temp->node_data;
                    right = temp->right;
                    left = temp->left;
                    temp->right = temp->left = nullptr;
                    delete temp;
                    deleted = true;
                }
            }
            return deleted;
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

        //! Update height
        void update_height() {
            int height_left, height_right;
            if (left == nullptr && right == nullptr) {
                height = 0;
            } else {
                // Left side balancing
                if (!left) {
                    left->update_height();
                    switch (left->balance_type()) {
                        case 0: // Balanced, update heights
                            height_left = get_height(left->left);
                            height_right = get_height(left->right);
                            left->height = std::max(height_left, height_right) + 1;
                            break;
                        case 1: // Left left
                            left = left->simple_left();
                            break;
                        case 2: // Left right
                            left = left->double_left();
                            break;
                        case 3: // Right right
                            left = left->simple_right();
                            break;
                        case 4: // Right right
                            left = left->double_right();
                            break;
                        default:
                            break;
                    }
                }

                // Right side balancing
                if (right) {
                    right->update_height();
                    switch (right->balance_type()) {
                        case 0: // Balanced, update heights
                            height_left = get_height(right->left);
                            height_right = get_height(right->right);
                            right->height = std::max(height_left, height_right) + 1;
                            break;
                        case 1: // Left left
                            right = right->simple_left();
                            break;
                        case 2: // Left right
                            right = right->double_left();
                            break;
                        case 3: // Right right
                            right = right->simple_right();
                            break;
                        case 4: // Right right
                            right = right->double_right();
                            break;
                        default:
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
            if (get_height(left) - get_height(right) > 1) {
                if (get_height(left->left) > get_height(left->right)) {
                    return 1;
                }
                else {
                    return 2;
                }
            } else if (get_height(right) - get_height(left) > 1) {
                if (get_height(right->right) > get_height(right->left)) {
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

        Node* minimum() {
            if (left == nullptr) {
                return this;
            }
            return left->minimum();
        }

        //! Simple left
        Node* simple_left() {
            Node* temp_node = left;
            left = temp_node->right;
            temp_node->right = this;

            height = std::max(get_height(left), get_height(right) + 1);
            temp_node->height = std::max(get_height(temp_node->left), get_height(this)) + 1;
        }

        //! Simple right
        Node* simple_right() {
            Node* temp_node = right;
            right = temp_node->left;
            temp_node->left = this;

            height = std::max(get_height(right), get_height(left) + 1);
            temp_node->height = std::max(get_height(temp_node->right), get_height(this)) + 1;
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
    };

    Node* root{nullptr};
    std::size_t size_{0u};
};

}  // namespace structures

#endif
