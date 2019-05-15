#pragma once

#include<iostream>
using std::cout;
using std::cerr;

template<typename T>
struct List;

template<typename T>
class DNode {
    //private:
protected:
    DNode<T> *next, *prev;
public:
    T data;
    DNode<T>(const T& v, DNode<T>* n = nullptr, DNode<T>* p = nullptr)
        : data(v), next(n), prev(p) { }
    DNode<T>* insert(List<T>& l, DNode* n);                         // insert n before this object
    DNode<T>* add(DNode<T>* n);                                     // insert n after this object
    DNode<T>* add(List<T>& l, DNode* n);
    DNode<T>* erase(List<T>& l);                                   // remove this object from the list
    DNode<T>* find(const List<T>& l, const T& x);             // find s in list
    const DNode<T>* find(const List<T>& l, const T& x) const; // find s in const list

    DNode<T>* advance(int n) const; // move n positions in list

    DNode<T>* getNext() const { return next; }
    DNode<T>* getPrev() const { return prev; }
    void setNext(DNode* n) { next = n; }
    void setPrev(DNode* p) { prev = p; }
};



template<typename T>
struct List {
    List() : first_DNode(nullptr) { } //default ctor
    List(DNode<T>* n) : first_DNode(n) { }
    DNode<T>* first_DNode;
};

// insert n before this object
template<typename T>
DNode<T>* DNode<T>::insert(List<T>& l, DNode* n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    if (this->prev == nullptr) { //inserting at the beginning
        n->setNext(this);
        this->prev = n;
        n->setPrev(nullptr);
        l.first_DNode = n;
    }
    else {
        n->setNext(this);
        n->setPrev(this->prev);
        this->prev = n;
        this->prev->next = n;
    }

    return n;
}

// insert n after this object
template<typename T>
DNode<T>* DNode<T>::add(DNode* n) {
    if (n == nullptr) return this;
    if (this == nullptr) return n;
    this->next->getPrev = n;
    n->next = next;
    next = n;
    n->setPrev(this);
    return n;
}

// insert n after this object
template<typename T>
DNode<T>* DNode<T>::add(List<T>& l, DNode* n) {
    if (n == 0) return this;
    if (this == 0) return n;
    if (this->next == nullptr) { //adding to the end
        this->next = n;
        n->setPrev(this);
    }
    else {
        n->setNext(this->next);
        n->setPrev(this);
        this->next = n;
        n->getNext()->prev = n;
    }
    return n;
}

// erase this object, return next
template<typename T>
DNode<T>* DNode<T>::erase(List<T>& l) {
    if (this == nullptr) return nullptr;
    if (l.first_DNode == this) {
        l.first_DNode = next;
    }
    DNode* p = l.first_DNode;
    while (p->next != this)
        p = p->next;
    p->next = next;
    return next;
}

// find s in list; return 0 for "not found"
template<typename T>
DNode<T>* DNode<T>::find(const List<T>& l, const T& x) {
    DNode* p = l.first_DNode;
    while (p) {
        if (p->data == x) return p;
        p = p->next;
    }
    return nullptr;
}

// find s in const list; return 0 for "not found"
template<typename T>
const DNode<T>* DNode<T>::find(const List<T>& l, const T& x) const {
    const DNode<T>* p = l.first_DNode;
    while (p) {
        if (p->data == x) return p;
        p = p->next;
    }
    return nullptr;
}

// move n positions in list, return 0 for "not found"
// positive n moves forward
template<typename T>
DNode<T>* DNode<T>::advance(int n) const {
    if (this == nullptr) return nullptr;
    DNode<T>* p = const_cast<DNode<T>*>(this);  // UGLY
    if (0 <= n) {
        while (n--) {
            if (p->next == 0) return 0;
            p = p->next;
        }
    }
    else cerr << "must advance by a positive number";
    return p;
}


template<typename T>
void print_all(const List<T>& l)  {
    cout << "{ ";
    DNode<T>* p = l.first_DNode;
    while (p) {
        cout << p->data;
        if (p = p->getNext()) cout << ", ";
    }
    cout << " }";
}

template<typename T>
void print_all(DNode<T>* n) {
    cout << "{ ";
    while (n) {
        cout << n->data;
        if (n = n->getNext()) cout << ", ";
    }
    cout << " }";
}