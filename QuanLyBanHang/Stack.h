#pragma once
#include <iostream>
using namespace std;

template<typename T>
class Stack {
private:
    class Node {
    private:
        T _data;
        Node* _pNext;
    public:
        Node(T data, Node* next = NULL) : _data(data), _pNext(next) {}
        friend Stack;
    };

    Node* _pTop;

public:
    Stack() : _pTop(NULL) {}
    
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const T& val) {
        _pTop = new Node(val, _pTop);
    }

    T pop() {
        if (isEmpty()) {
            throw runtime_error("Stack underflow");
        }
        Node* pTemp = _pTop;
        T val = _pTop->_data;
        _pTop = _pTop->_pNext;
        delete pTemp;
        return val;
    }

    bool isEmpty() const {
        return _pTop == NULL;
    }
};
