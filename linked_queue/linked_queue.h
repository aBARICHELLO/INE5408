namespace structures {
    
    template<typename T>
    //! LinkedQueue class
    class LinkedQueue {
     public:
        LinkedQueue();
    
        ~LinkedQueue();
    
        //! Clear the queue
        void clear() {
        }
    
        //! Inserts into the queue
        void enqueue(const T& data) {
        }
    
        //! Removes the item from the queue
        T dequeue() {
        }
    
        //! First data from the queue
        T& front() const {
        }
    
        //! Last data from the queue
        T& back() const {
        }
    
        //! Empty
        bool empty() const {
        }
    
        //! Size of the queue
        std::size_t size() const {
        }
    
     private:
        //! Head
        Node* head {
        }
    
        //! Tail
        Node* tail {
        }
    
        std::size_t size_;
    };
    
}  // namespace structures
    