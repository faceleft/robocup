#ifndef dynamic_queue_h
#define dynamic_queue_h
#include <stdlib.h>
//errors codes
//1201 - dynamic_queue.add() alloc error
//1202 - dynamic_queue.get() queue is empty
#ifndef STRUCT_FORWARD_NODE
#define STRUCT_FORWARD_NODE
template<typename T>
struct ForwardNode{
    T val;
    ForwardNode<T>* next;
};
#endif

template<typename T>
class dynamic_queue {
  public:
    dynamic_queue(void(*_errorHandler)(int) = nullptr) {
      first_ = nullptr;
      last_ = nullptr;
      length_ = 0;
      errorHandler = _errorHandler;

    }

    ~dynamic_queue() {
      clear();
    }

    void clear() {
      while (length_) get();
    }

    void add(T val) {
      ForwardNode<T>* tmp = new ForwardNode<T>;
      if (!tmp && errorHandler) errorHandler(1201);
      tmp->val = val;
      tmp->next = nullptr;
      if (last_) last_->next = tmp;
      if (!first_) first_ = tmp;
      last_ = tmp;
      length_++;
    }
    T get() {
      if(!length_ && errorHandler) errorHandler(1202);
      ForwardNode<T>* buffer = first_;
      T value = buffer->val;
      if (first_->next != 0 ) first_ = first_->next;
      else {
        first_ = nullptr;
        last_ =  nullptr;
      }
      delete buffer;
      length_--;
      return value;
    }
    inline unsigned int len() {
      return length_;
    }
    inline size_t size() {
      return sizeof(dynamic_queue<T>) + length_*sizeof(ForwardNode<T>);
    }

  private:
    unsigned int length_;
    ForwardNode<T>* first_;
    ForwardNode<T>* last_;
    void (*errorHandler)(int);
};


#endif
