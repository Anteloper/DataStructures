//
//  BinaryTree.h
//  Project2
//
//  Created by Oliver Hill on 2/20/17.
//  Copyright © 2017 Oliver Hill. All rights reserved.
//

#include <stdio.h>
#include <iomanip>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#ifndef BinaryTree_h
#define BinaryTree_h

template <typename T>
struct Node{
    T data;
    Node *left;
    Node *right;
};

template <typename T>
class BinaryTree{
    
private:
    //PRIVATE MEMBER VARIABLES
    Node<T> *root;
    int nodeCount;
    
    //PRIVATE MEMBER FUNCTIONS
    void insert(T element, Node<T>* &node);
    bool find(T element, Node<T>* node) const;
    Node<T> *nodeFind(T element, Node<T> *node) const;
    int nodeHeight(Node<T> *node) const;
    void printInOrder(Node<T> *node, std::ostream &os) const;
    void printPreOrder(Node<T> *node, std::ostream &os) const;
    void printPostOrder(Node<T> *node, std::ostream &os) const;
    T findMin(Node<T> *node){ return node->left == nullptr ? node->data : findMin(node->left);}
    void remove(Node<T> *&node, T element);
    void removeAll(Node<T> *node);
    Node<T> *deepCopy(Node<T> *root);
    
public:
    /*Default Constructor
    Sets the root to null*/
    BinaryTree<T>(){root = nullptr; nodeCount = 0;}
    
    /*Copy Constructor
     The tree becomes a deep copy of the parameter passed in*/
    BinaryTree<T>(const BinaryTree<T> &t){this->root = deepCopy(t.root); }
    
    /*Overloaded Assingment Operator
     The tree becomes a deep copy of the right side of the operator*/
     BinaryTree<T> operator =(const BinaryTree<T> &rhsObj);
    
    /*Destructor
     Frees all allocated memory*/
    ~BinaryTree(){removeAll(root);}
    
    //Returns the number of nodes in the tree
    //Does not modify the tree
    int count() const{return nodeCount;}
    
    //Returns the height of the  tree
    //Does not modify the tree
    int height() const{ return nodeHeight(root);}
    
    //Returns the height of an element
    //Does not modify the tree
    int height(T element) const{ return nodeHeight(nodeFind(element, root)); }
    
    /*Creates a Node with the value of element
     It is inserted to maintain the properties of a Binary Search tree
     If then node already exists, a warning is printed the the console*/
    void insert(T element);
    
    //Returns true if the element exists in the tree, false if it does not
    //Does not modify the tree
    bool find(T element) const {return find(element, root);}
    
    /*Printing functions: print the the specified order to the stream passed in
     The printing functions do not modify the tree*/
    void printInOrder(std::ostream &os) const {if(root != nullptr) printInOrder(root, os);}
    void printPostOrder(std::ostream &os) const {if(root != nullptr) printPostOrder(root, os);}
    void printPreOrder(std::ostream &os) const {if(root != nullptr) printPreOrder(root, os);}

    //Finds and removes the element at T, prints a warning if it doesn't exist
    void remove(T element);
    
    //Deletes all Nodes in in the tree and frees any allocated memory. Called by destructor.
    void removeAll(){removeAll(root); root = nullptr; nodeCount = 0;}
};

#endif
