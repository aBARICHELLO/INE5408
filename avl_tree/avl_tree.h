// Copyright [2017] <Barichello>

#ifndef STRUCTURES_AVL_TREE
#define STRUCTURES_AVL_TREE

#include <stdexcept>
#include "array_list.h"

namespace structures {
template<typename T>
//! avl class
class AVLTree {
public:
    //! Constructor
    ~AVLTree();

    //! Insert
    void insert(const T& data);

    //! Remov
    void remove(const T& data);

    //! Contains
    bool contains(const T& data) const;

    //! Empty
    bool empty() const;

    //! Size
    std::size_t size() const;

    //! Pre order
    ArrayList<T> pre_order() const;

    //! In order
    ArrayList<T> in_order() const;

    //! Post order
    ArrayList<T> post_order() const;

private:
    //! Node struct
    struct Node {
        //! Node constructor
        Node(const T& data);

        //! Node insert
        void insert(const T& data_);

        //! Node remove
        bool remove(const T& data_);

        //! Contains
        bool contains(const T& data_) const;

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
        void pre_order(ArrayList<T>& v) const;

        //! In order
        void in_order(ArrayList<T>& v) const;

        //! Post order
        void post_order(ArrayList<T>& v) const;

        T data;
        std::size_t height;
        Node* left;
        Node* right;
    };

    Node* root;
    std::size_t size_;
};

}  // namespace structures

#endif
