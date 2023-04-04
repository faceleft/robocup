#ifndef list_h
#define list_h

#include "error.h"

template<typename T>
struct Node {
  T val;
  Node<T>* next;
};

template<typename T>
class list {
public:
  int len = 0;
  list() {
    _first = NULL;
    _last = NULL;
  }
  ~list() {
    this->clear();
  }
  void append(T val) {
    Node<T>* tmp = (Node<T>*)new Node<T>;
    if(tmp == NULL) error(ALLOC_ERROR);
    tmp->val = val;
    tmp->next = NULL;
    if (_first != NULL) {
      _last->next = tmp;
      _last = tmp;
    } else {
      _first = tmp;
      _last = tmp;
    }
    len++;
  }
  T& last() {
    return (*_last).val;
  }
  T& operator[](int n){
    return this->at(n);  
  }
  T& at(int n) {
    if (n < 0) { n = len + n; }
    return (*_at(n)).val;
  }
  void del(int n) {
    if (n < 0) { n = len + n; }

    if (n != 0) {
      Node<T>* buff = _at(n);
      if (n < len) {
        _at(n - 1)->next = _at(n + 1);
      }
      delete buff;
    } else {
      Node<T>* a = _first;
      _first = _at(n + 1);
      delete a;
    }
    len--;
  }
  void clear() {
    if (_first != NULL) {
      Node<T>* now = _first;
      while (now->next != NULL) {
        Node<T>* buff = now;
        now = now->next;
        delete buff;
      }
      delete now;
      _first = NULL;
      _last = NULL;
    }
  }
private:
  Node<T>* _first;
  Node<T>* _last;
  Node<T>* _at(unsigned int n) {
    if (_first == NULL) {
      return NULL;
    }
    Node<T>* now = _first;
    while (n > 0) {
      now = now->next;
      n--;
    }
    return now;
  }
};

#endif
