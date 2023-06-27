#ifndef dynamic_stack_h
#define dynamic_stack_h
#include <stdlib.h>
//errors codes
//1401 - dynamic_stack.add() alloc error
//1402 - dynamic_stack.get() queue is empty
#ifndef STRUCT_FORWARD_NODE
#define STRUCT_FORWARD_NODE
template<typename T>
struct ForwardNode{
    T val;
    ForwardNode<T>* next;
};
#endif

template<typename T>
class dynamic_stack {
  public:
    dynamic_stack(void(*_errorHandler)(int) = nullptr) {
      first_ = nullptr;
      length_ = 0;
      errorHandler = _errorHandler;
    }

    ~dynamic_stack() {
      clear();
    }

    void clear() {
      while (length_) get();
    }    
    
    bool add(T val) {
      ForwardNode<T>* tmp = new ForwardNode<T>;
      if (!tmp && errorHandler) errorHandler(1401);
      tmp->val = val;
      tmp->next = nullptr;
      if (!first_) tmp->next = first_;;
      first_ = tmp;
      length_++;
      return true;
    }
    T get() {
      if(!length_ && errorHandler) errorHandler(1402);
      ForwardNode<T>* buffer = first_;
      T value = buffer->val;
      if (first_->next) first_ = first_->next;
      else {
        first_ = nullptr;
      }
      delete buffer;
      length_--;
      return value;
    }
    inline unsigned int len() {
      return length_;
    }
    inline size_t size() {
      return sizeof(dynamic_stack<T>) + length_ * sizeof(ForwardNode<T>);
    }
  private:
    unsigned int length_;
    ForwardNode<T>* first_;
    void (*errorHandler)(int);
};

#endif
