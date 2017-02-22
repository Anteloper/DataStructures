//
//  BinaryTree.cpp
//  BinaryTree
//
//  Created by Oliver Hill on 10/21/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//


#include "BinaryTree.h"


template <typename T>
BinaryTree<T> BinaryTree<T>::operator =(const BinaryTree<T> &rhsObj){
    if(this != &rhsObj){
        this->root = deepCopy(rhsObj.root);
    }
    return *this;
}


//PRIVATE HEIGHT
template <typename T>
int BinaryTree<T>::nodeHeight(Node<T> *node) const{
    if(node == nullptr)
        return -1;
    else
        return std::max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
}


//PRIVATE NODE FIND
template <typename T>
Node<T> *BinaryTree<T>::nodeFind(T element, Node<T> *node) const{

    if(node!=nullptr)
    {
        if(element==node->data)
            return node;
        if(element<node->data)
            return nodeFind(element, node->left);
        else
            return nodeFind(element, node->right);
    }
    else
        return nullptr;
}


//PRIVATE FIND
template <typename T>
bool BinaryTree<T>::find(T element, Node<T>* node) const{
    if(node!=nullptr){
        if(element==node->data)
            return true;
        if(element<node->data)
            return find(element, node->left);
        else
            return find(element, node->right);
    }
    else return false;
}


//PRIVATE INSERT
template <typename T>
void BinaryTree<T>::insert(T element, Node<T>* &node){
    if(node != nullptr)
        insert(element, (element > node->data ? node->right : node->left));
    
    if(node == nullptr){
        Node<T> *next = new Node<T>;
        next->data = element;
        next->left = nullptr;
        next->right = nullptr;
        node = next;
    }
}

//PUBLIC INSERT
template <typename T>
void BinaryTree<T>::insert(T element){
    if(root == nullptr){
        root = new Node<T>;
        root->data = element;
        root->left = nullptr;
        root->right = nullptr;
    }
    
    else{
        if(find(element))
            std::cout<< "Warning, duplicate value, ignoring\n\n";
        else
            insert(element, root);
    }
    nodeCount++;
}



//PUBLIC REMOVE
template<typename T>
void BinaryTree<T>::remove(T element){
    Node<T> *node;
    node = nodeFind(element, root);
    remove(node, element);
}

//PRIVATE REMOVE
template <typename T>
void BinaryTree<T>::remove(Node<T> *&node, T element){
    if(node != nullptr) return;
    if(node->data < element)
        remove(node->left, element);
    else if(node->data > element)
        remove(node->right, element);
    else if(node->left != nullptr && node->right != nullptr){
        Node<T> *temp = node->right;
        node->data = findMin(temp);
        remove(node->right, element);
    }
    else{
        Node<T> *temp = node;
        temp = node->left == nullptr ? node->right : node->left;
    }
}

//PRIVATE REMOVE ALL
template<typename T>
void BinaryTree<T>::removeAll(Node<T> *node){
    
    if(node != nullptr){
        removeAll(node->left);
        removeAll(node->right);
        delete node;
    }
    nodeCount = 0;
}



//PRIVATE DEEP COPY
//Returns the root of a newly allocated tree, identical to the subtree of the Node passed in
template <typename T>
Node<T> *BinaryTree<T>::deepCopy(Node<T> *root){
    if(root == nullptr)
        return nullptr;
    else{
        Node<T> *next = new Node<T>;
        next->data = root->data;
        next->left = deepCopy(root->left);
        next->right = deepCopy(root->right);
    }
    return root;
}

//INORDER PRINT
template <typename T>
void BinaryTree<T>::printInOrder(Node<T> *node, std::ostream &os) const{
    if(node->left != nullptr)
        printInOrder(node->left, os);
    
    os<< node->data << ", ";
    
    if(node->right != nullptr)
        printInOrder(node->right, os);
    
}


//POST ORDER PRINT
template <typename T>
void BinaryTree<T>::printPostOrder(Node<T> *node, std::ostream &os) const{
    if(node->left != nullptr)
        printInOrder(node->left, os);
    
    if(node->right != nullptr)
        printInOrder(node->right, os);
    
    os<< node->data << ", ";
}


//PRE ORDER PRINT
template <typename T>
void BinaryTree<T>::printPreOrder(Node<T> *node, std::ostream &os) const{
    os<< node->data << ", ";
    
    if(node->left != nullptr)
        printInOrder(node->left, os);
    
    if(node->right != nullptr)
        printInOrder(node->right, os);
    
}



