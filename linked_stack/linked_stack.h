// Copyright [2017] <Artur Barichello>
namespace structures {
    
    template<typename T>
    //! LinkedStack class
    class LinkedStack {
     public:
        LinkedStack();
    
        ~LinkedStack();
    
        //! Clears the list
        void clear() {
        }
    
        //! Push
        void push(const T& data) {
        }
    
        //! Pop
        T pop() {
        }
    
        //! Returns the data at the top of the Stack
        T& top() const {
        }
    
        //! Empty stack
        bool empty() const {
        }
    
        //! Number of elements in the stack
        std::size_t size() const {
        }
    
     private:
        //! Node class
        class Node {
         public:
            explicit Node(const T& data) {
            }
    
            Node(const T& data, Node* next) {
            }
    
            T& data() {
            }
    
            const T& data() const {
            }
    
            Node* next() {
            }
    
            const Node* next() const {
            }
    
            void next(Node* next) {
            }
    
         private:
            T data_;
            Node* next_;
        };
    
        Node* top_;
        std::size_t size_;
    };
    
    }  // namespace structures
    