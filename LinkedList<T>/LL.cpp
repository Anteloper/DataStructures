//
//  LL.cpp
//  Homework1
//
//  Created by Oliver Hill on 9/25/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#include <stdio.h>
#include "LL.h"



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                        class Node implementation                       **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

template<typename T>
Node<T>::Node(T nodeData, Node<T>* nextNode){//BEGIN constructor with parameters
    info = nodeData;
    next = nextNode;
}//END constructor with parameters



//END NODE CLASS IMPLEMENTATION

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                        class LL<T> implementation                      **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/

//LL CLASS IMPLEMENTATION
//MEMBER FUNCTIONS

template <typename T>
LL<T>::LL(){//BEGIN Default Constructor
    count = 0;
    head = NULL;
}//END Default Constructor

template<typename T>
LL<T> LL<T>::operator =(const LL<T> &rhsObj) {//BEGIN overloaded assignment operator
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
LL<T>::LL(const LL<T> &otherLL){
    try{
        copyList(otherLL);
    }
    catch(std::string exc){
        throw std::string(exc);
    }
}

template<typename T>
void LL<T>::copyList(const LL<T> &listToCopy){//BEGIN Function CopyList
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
void LL<T>::push_back(T data){//BEGIN push_back function
    
    try{//prevent against bad_alloc
        //The list is empty
        if (head == NULL){
            head = new Node<T>(data);
            head->next = NULL;
        }
        //The list is not empty
        else{
            Node<T> *thisNode = head;
            while (thisNode->next != NULL)
                thisNode = thisNode->next;
            
            thisNode-> next = new Node<T>(data);
        }
        count++;
    }
    catch(std::bad_alloc){
        throw std::string("Program ran out of memory to allocate\n");
    }
}//END push_back function


template <typename T>
void LL<T>::insert(T data){//BEGIN Insert Function
    try{//prevent against bad_alloc
        //If this list is empty
        if(head==NULL)
            head = new Node<T>(data, NULL);
        
        //If this list is not empty
        else{
            if (data <= head->info) {
                Node<T> *newHead = new Node<T>(data, head);
                head = newHead;
            }
            
            else{
                Node<T> *thisNode = head;
                while (thisNode->next != NULL && data >= thisNode->next->info) {
                    thisNode = thisNode->next;
                }
                Node<T> *insertMe = new Node<T>(data, thisNode->next);
                thisNode->next = insertMe;
            }
        }
        count++;
    }
    catch(std::bad_alloc){
        std::cout<<("Program ran out of memory to allocate");
    }
}//END Insert Function


template <typename T>
void LL<T>::pop_back(){//BEGIN pop_back function
    
    if(head == NULL)
        return;
    
    else if (head->next == NULL)
    {
        delete head;
        head = NULL;
    }
    else{
        Node<T> *thisNode = head;
        
        while (thisNode->next->next != NULL)
            thisNode = thisNode->next;
        
        Node<T> *tail = thisNode->next;
        delete tail;
        thisNode->next = NULL;
    }
    count--;
}//END pop_back function


template <typename T>
void LL<T>::clear(){//BEGIN Clear Function
    
    Node<T> *thisNode = head;
    Node<T> *temp;
    while(thisNode!=NULL){
        
        temp = thisNode->next;
        delete thisNode;
        thisNode = temp;
    }
    head = NULL;
    count = 0;
    
}//END Clear Function



template<typename T>
T& LL<T>::at(int ndx) const{//BEGIN At Function
    try {
        if((ndx > this->size()-1 || ndx < 0) || head==NULL)
            throw std::out_of_range("");
        
        else{
            int iterator = 0;
            Node<T> *thisNode = head;
            while (iterator!=ndx) {
                thisNode = thisNode->next;
                iterator++;
            }
            return thisNode->info;
        }
    }
    catch(std::out_of_range){
        throw std::out_of_range("");
    }
    
}//END At Function

//FRIEND FUNCTIONS
template<typename F>
std::ostream& operator<<(std::ostream &os, const LL<F> &ll){//BEGIN Overloaded Stream Operator
    
    Node<F> *thisNode = ll.head;
    while(thisNode != NULL){
        os << thisNode->info << std::endl;
        thisNode = thisNode->next;
    }
    return os;
    
}//END Overloaded Stream Operator


//END LL CLASS IMPLEMENTATION

