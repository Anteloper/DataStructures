//
//  Stack.cpp
//  Homework1
//
//  Created by Oliver Hill on 9/27/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#include "Stack.h"
#include "LL.h"

template <typename T>
Stack<T>::Stack(){//BEGIN Default Constructor
    count = 0;
    head = NULL;
}//END Default Constructor

template<typename T>
Stack<T> Stack<T>::operator =(const Stack<T> &rhsObj) {//BEGIN overloaded assignment operator
    this->clear();
    this->head=NULL;
    try{
        copyList(rhsObj);
        return *this;
    }
    catch(std::string exc){
        throw std::string(exc);
    }
}//END overloaded assignment operator


template<typename T>
Stack<T>::Stack(const Stack<T> &otherStack){
    try{
        copyList(otherStack);
    }
    catch(std::string exc){
        throw std::string(exc);
    }
}

template<typename T>
Stack<T>::~Stack(){
    Node<T> *thisNode = head;
    Node<T> *temp;
    while(thisNode!=NULL){
        temp = thisNode->next;
        delete thisNode;
        thisNode = temp;
    }
    head = NULL;
    count = 0;
}

template<typename T>
void Stack<T>::pop(){
    if (head != NULL){
        Node<T> *newHead = head->next;
        delete head;
        head = newHead;
    }
    else{
        throw(string("Tried to pop on an empty stack"));
    }
}

template <typename T>
T& Stack<T>::top(){
    if(head != NULL){
        return head->info;
    }
    else{
        throw(string("Top is null"));
    }
}


template<typename T>
void Stack<T>::copyStack(const Stack<T> &listToCopy){//BEGIN Function CopyList
    if (listToCopy.head == NULL)
        return;
    
    //Create a deep copy of the head to be copied and set the new head to that copy
    try{
        head = new Node<T>(listToCopy.head->info, NULL);
    }
    catch(std::bad_alloc){
        throw std::string("Program ran out of memory to allocate");
    }
    catch(...){
        return;
    }
    
    Node<T> *thisNode = listToCopy.head->next;
    if (thisNode != NULL){
        while(thisNode->next != NULL){
            push_back(thisNode->info);
            thisNode = thisNode->next;
        }
        push_back(thisNode->info);
        count = listToCopy.count;
    }
    
}//END Function CopyList

template <typename T>
void Stack<T>::push(T& e){
    Node<T> *newHead = new Node<LL<Term>>(e, head);
    head = newHead;
}

template <typename T>
void Stack<T>::print(){
    cout << "STACK: \n";
    Node<LL<Term>> *poly = head;
    while(poly != NULL){
        poly->info.print();
        cout << "\n";
        poly = poly->next;
    }
}



