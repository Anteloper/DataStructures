//
//  BinaryTree.cpp
//  BinaryTree
//
//  Created by Oliver Hill on 10/21/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//


#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#ifndef BinaryTree_h
#define BinaryTree_h

using namespace std;


template <typename T>
struct Node{
    T data;
    Node *left;
    Node *right;
};

template <typename T>
class BinaryTree{
    
private:
    Node<T> *root;
    int nodeCount;
    void insert(T element, Node<T>* &node);
    bool find(T element, Node<T>* node);
    Node<T> *nodeFind(T element, Node<T> *node);
    int nodeHeight(Node<T> *node);
    void printInOrder(Node<T> *node);
    void printPreOrder(Node<T> *node);
    void printPostOrder(Node<T> *node);
    void deleteAll(Node<T> *node);
    Node<T> *deleteNode(Node<T> *node, T element);
    
public:
    BinaryTree<T>(){root = NULL; nodeCount = 0;}
    int count(){return nodeCount;}
    void insert(T element);
    int height(){ return nodeHeight(root);}
    int height(T element){ return nodeHeight(nodeFind(element, root)); }
    bool find(T element){return find(element, root);}
    void printInOrder(){if(root != NULL) printInOrder(root);}
    void printPostOrder(){if(root != NULL) printPostOrder(root);}
    void printPreOrder(){if(root != NULL) printPreOrder(root);}
    void deleteAll(){deleteAll(root); root = NULL; nodeCount = 0;}
    void Delete(T element){deleteNode(nodeFind(element, root), element);}
    void load(string fileName);
    ~BinaryTree(){deleteAll(root);}
};



//PRIVATE HEIGHT
template <typename T>
int BinaryTree<T>::nodeHeight(Node<T> *node){
    if(node == NULL)
        return -1;
    else
        return std::max(nodeHeight(node->left), nodeHeight(node->right)) + 1;
}


//PRIVATE NODE FIND
template <typename T>
Node<T> *BinaryTree<T>::nodeFind(T element, Node<T> *node)
{
    if(node!=NULL)
    {
        if(element==node->data)
            return node;
        if(element<node->data)
            return nodeFind(element, node->left);
        else
            return nodeFind(element, node->right);
    }
    else return NULL;
}


//PRIVATE FIND
template <typename T>
bool BinaryTree<T>::find(T element, Node<T>* node){
    if(node!=NULL){
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
    if(node != NULL)
        insert(element, (element > node->data ? node->right : node->left));
    
    if(node == NULL){
        Node<T> *next = new Node<T>;
        next->data = element;
        next->left = NULL;
        next->right = NULL;
        node = next;
    }
}

//PUBLIC INSERT
template <typename T>
void BinaryTree<T>::insert(T element){
    if(root == NULL){
        root = new Node<T>;
        root->data = element;
        root->left = NULL;
        root->right = NULL;
    }
    
    else{
        if(find(element))
            cout << "Duplicate value entered, no insertion cancelled";
        else
            insert(element, root);
    }
    nodeCount++;
}

//INORDER PRINT
template <typename T>
void BinaryTree<T>::printInOrder(Node<T> *node){
    if(node->left != NULL)
        printInOrder(node->left);
    
    cout << node->data << "\n";
    
    if(node->right != NULL)
        printInOrder(node->right);
    
}

//POST ORDER PRINT
template <typename T>
void BinaryTree<T>::printPostOrder(Node<T> *node){
    if(node->left != NULL)
        printInOrder(node->left);
    
    if(node->right != NULL)
        printInOrder(node->right);
    
    cout << node->data << "\n";
}


//PRE ORDER PRINT
template <typename T>
void BinaryTree<T>::printPreOrder(Node<T> *node){
    cout << node->data << "\n";
    
    if(node->left != NULL)
        printInOrder(node->left);
    
    
    if(node->right != NULL)
        printInOrder(node->right);
    
}

//PRIVATE DELETE ALL
template<typename T>
void BinaryTree<T>::deleteAll(Node<T> *node){
    if(node != NULL){
        deleteAll(node->left);
        deleteAll(node->right);
        delete node;
    }
}


//PRIVATE DELETENODE
template <typename T>
Node<T> *BinaryTree<T>::deleteNode(Node<T> *node, T element){
    if(node == NULL)
        return node;
    else if(element < node->data)
        node->left = deleteNode(node->left,element);
    else if(element > node->data)
        node->right = deleteNode(node->right, element);
    
    else {
        //IF NO CHILD NODES EXIST
        if(node->left == NULL && node->right == NULL){
            delete node;
            node = NULL;
            
            
        //IF ONLY LEFT CHILD EXISTS
        } else if(node->left == NULL){
            Node<T> *temp = node;
            node = node->right;
            delete temp;
        //IF ONLY RIGHT CHILD EXISTS
        } else if(node->right == NULL){
            Node<T> *temp = node;
            node = node->left;
            delete temp;
            
            
        //BOTH CHILDREN EXIST
        } else{
            Node<T> *temp = node->right;
            
            while(temp->left != NULL){
                temp = temp->left;
            }
            node->data = temp->data;
            node->right = deleteNode(node->right, temp->data);
        }
    }
    return node;
}

#endif
