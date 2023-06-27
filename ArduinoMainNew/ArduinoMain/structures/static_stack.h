#ifndef static_stack_h
#define static_stack_h
#include <stdlib.h>
//errors codes
//1301 - static_stack.add() owerflow error
//1302 - static_stack.get() queue is empty
template<typename T, unsigned int _size>
class static_stack {
  public:
    static_stack(void(*_errorHandler)(int) = nullptr) {
      first_ = 0;
      length_ = 0;
      errorHandler = _errorHandler;
    }

    void clear() {
      first_ = 0;
      length_ = 0;
    }
    
    bool add(T val) {
      if (length_ >= _size && errorHandler) errorHandler(1301);
      if (first_ == 0) first_ = _size - 1;
      else first_--;
      data[first_] = val;
      length_++;
      return true;
    }

    T get() {
      if(!length_ && errorHandler) errorHandler(1302);
      T value = data[first_];
      first_ = (first_+1) % _size;
      length_--;
      return value;
    }
    inline unsigned int len() {
      return length_;
    }
    inline size_t size() {
      return sizeof(static_stack<T, _size>);
    }
  private:
    T data[_size];
    unsigned int length_;
    unsigned int first_;
    void (*errorHandler)(int);
};

#endif
