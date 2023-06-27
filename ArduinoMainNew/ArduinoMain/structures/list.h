#ifndef list_h
#define list_h
#include <stdlib.h>
//errors codes
//1001 - list.append() alloc error
//1002 - list[] index error
//1003 - list.insert() index error
//1004 - list.insert() alloc error
//1005 - list.pop() index error
#ifndef STRUCT_FORWARD_NODE
#define STRUCT_FORWARD_NODE
template<typename T>
struct ForwardNode{
    T val;
    ForwardNode<T>* next;
};
#endif

template<typename T>
class list{
public:
    list(void(*_errorHandler)(int) = nullptr){
        first_ = nullptr;
        last_ = nullptr;
        errorHandler = _errorHandler;
        length_ = 0;
    }
    
    ~list(){
        clean();
    }

    void append(T val){
        ForwardNode<T>* tmp = new ForwardNode<T>;
        if (!tmp && errorHandler) errorHandler(1001);
        tmp->val = val;
        tmp->next = nullptr;

        if (!length_){
            first_ = tmp;
            last_ = tmp;
        }
        else{
            last_->next = tmp;
            last_ = tmp;
        }
        length_++;
    }

    void insert(int index, T val){
        if(index < 0) index += length_;
        if((index >= length_ || index < 0) && errorHandler) errorHandler(1003);
        ForwardNode<T>* tmp = new ForwardNode<T>;
        if (!tmp && errorHandler) errorHandler(1004);
        tmp->next = nullptr;
        tmp->val = val;
        if(index == 0){
            if(!length_) last_ = tmp;
            else tmp->next = first_;
            first_ = tmp;
            return;
        }

        ForwardNode<T>* p = first_;
        for (int i = 0; i < (index-1); i++) {
            p = p->next;
        }
        if(!p->next) last_ = tmp;
        tmp->next = p->next;
        p->next = tmp;
        length_++;
    }

    T& operator[](int index){
        if(index < 0) index += length_;
        if((!length_ || index >= length_ || index < 0) && errorHandler) errorHandler(1002);
        ForwardNode<T>* p = first_;
        for (int i = 0; i < index; i++) {
            p = p->next;
        }
        return p->val;
    }

    T pop(int index = -1){
        if(index < 0) index += length_;
        if((!length_ || index >= length_ || index < 0) && errorHandler) errorHandler(1005);
        ForwardNode<T>* tmp;
        if(index == 0){
            tmp = first_;
            first_ = first_->next;
        }
        else{
            ForwardNode<T>* p = first_;
            for (int i = 0; i < (index-1); i++) {
                p = p->next;
            }
            tmp = p->next;
            p->next = tmp->next;
            if(!p->next) last_ = p;
        }
        T value = tmp->val;
        delete tmp;
        length_--;
        return value;
    }
    T& last(){
        return last_->val;
    }
    void clean(){
        if(length_){
            ForwardNode<T>* tmp = first_;
            while(tmp->next){
                ForwardNode<T>* buffer = tmp;
                tmp = tmp->next;
                delete buffer;
            }
            delete tmp;
        }
    }
    inline size_t size() {
      return sizeof(list<T>) + length_ * sizeof(ForwardNode<T>);
    }
    inline int len(){return length_;}

private:
    ForwardNode<T>* first_;
    ForwardNode<T>* last_;
    int length_;
    void (*errorHandler)(int);
};

#endif
