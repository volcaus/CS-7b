#include <iostream>
#include "BST.h"

BST::Node::Node(int n, int d, Node* parent){
    this-> num = n;
    this-> den = d;
    this-> parent = parent;
}

BST::BST(int n, int d, int lvl){
    this->startN = n;
    this->startD = d;
    this->level = lvl;

    root = Node(n,d, nullptr);
}

BST::Node* BST::lowest(BST::Node* start){
    while(true){
        if (start->left == nullptr)
            return start;
        else
            lowest(start->left);
    }
}

BST::Node* BST::highest(BST::Node* start){
    while(true){
        if (start->right == nullptr)
            return start;
        else
            BST::highest(start->right);
    }
}

BST::Node* BST::find(int n, int d){
    BST::Node* p = rootptr;

    while(true){
        if (p->num == n && p->den == d)
            return p;
        else if (double(n) / double(d) < p->value())
            p = p->left;
        else if (double(n) / double(d) > p->value())
            p = p->right;
    }
}

BST::Node* BST::addNode(double n, double d, BST::Node* parent){
    if (n/d < parent->value()){
        parent->left = new Node(n,d,parent);
        return parent->left;
    }
    else{
        parent->right = new Node(n,d,parent);
        return parent->right;
    }
}

BST::Node* BST::step(BST::Node* n, int iter){
    if (iter == 0){
        currentptr = n;
        return n;
    }
    if (n->num == 0 && iter > 0)
        return nullptr;

    if (n->value() >= 1){
        n->num -= n->den;
        return BST::step(n, iter - 1);
    }

    n->den -= n->num;
    return BST::step(n, iter-1);
}