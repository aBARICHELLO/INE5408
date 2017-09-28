#ifndef STRUCTURES_BINARY_TREE_H
#define STRUCTURES_BINARY_TREE_H

#include <vector>

namespace structures {

template<typename T>
//! Binary Tree
class BinaryTree {
 public:
    //! Constructor
    ~BinaryTree();

    //! Insert
    void insert(const T& data);

    //! Remove
    void remove(const T& data);

    //! Contains
    bool contains(const T& data) const;

    //! Empty
    bool empty() const;

    //! Size
    std::size_t size() const;

    //! Pre ordered
    std::vector<T> pre_order() const;

    //! Normal order
    std::vector<T> in_order() const;

    //! Post ordered
    std::vector<T> post_order() const;

 private:
    struct Node {
        //! Node
        Node(const T& data);

        //! Insert
        void insert(const T& data_);
        
        //! Remove
        bool remove(const T& data_);
        
        //! Contains
        bool contains(const T& data_) const;
        
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
