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



//POLYNOMIAL SPECIFIC FUNCTION
template <typename T>
void LL<T>::print(){
    Node<T> *head = this->head;
    Node<T> *node = head;
    while(node != NULL){
        Term term = node->info;
        if (node != head)
            cout << " + ";
        if (term.getCoeff() != 0){
            cout << "(";
            if (term.getCoeff() != 1 || (term.getCoeff() == 1 && term.getExponent() == 0))
                cout << term.getCoeff();
            if (term.getExponent() != 0)
                cout << "x";
            if (term.getExponent() != 1 & term.getExponent() != 0)
                cout << "^" << term.getExponent();
            cout << ")";
        }
        node = node->next;
    }
}


template <typename T>
void LL<T>::sort()
{
    int index;
    int smallestIndex;
    int location;
    T temp;
    for(index = 0; index <this->size()-1; index++){
        smallestIndex = index;
        for(location = index +1; location < this->size(); location++){
            if(this->at(location).getExponent() > this->at(smallestIndex).getExponent()){
                smallestIndex = location;
            }
        }
        temp = this->at(smallestIndex);
        this->at(smallestIndex) = this->at(index);
        this->at(index) = temp;
    }
    
} //END function member function LL<T>::selectionSort()}


//Assumes the list is already simplified and sorted
template <typename T>
void LL<T>::removeDuplicates(){
    LL<Term> removed = LL<Term>();
    for(int i=this->at(0).getExponent(); i>=0; i--){
        for(int j =0; j<this->size(); j++){
            if(this->at(j).getExponent() == i){
                removed.push_back(this->at(j));
                break;
            }
        }
    }
    *this = removed;
}

template <typename T>
void LL<T>::simplify(){
    LL<Term> result = LL<Term>();
    for(int i = 0; i<this->size(); i++){
        Term res = this->at(i);
        for(int j = 0; j<this->size(); j++){
            if(this->at(j).getExponent() == res.getExponent() && i != j)
                res = Term(res.getCoeff() + this->at(j).getCoeff(), res.getExponent());
        }
        result.push_back(res);
    }
    
    this->clear();
    *this = result;
}

//Add the minuend and the subtrahend to the same polynomial, simplify it, sort it, and return it
template <typename T>
LL<Term> LL<T>::addTo(LL<Term> const& minuend){
    LL<Term> result = *this;
    for(int i = 0; i< minuend.size(); i++){
        result.push_back(minuend.at(i));
    }
    
    result.simplify();
    result.sort();
    result.removeDuplicates();
    return result;
}


//Negate the subtrahend, put it in the same polynomial as the minuend, simplify it, sort it, and return it.
template <typename T>
LL<Term> LL<T>::subtractFrom(LL<Term> const &minuend){
    LL<Term> result = minuend;
    for(int i =0; i<this->size(); i++){
        Term negatedTerm = Term((this->at(i).getCoeff()*-1), this->at(i).getExponent());
        result.push_back(negatedTerm);
    }
    result.simplify();
    result.sort();
    result.removeDuplicates();
    return result;
}

template <typename T>
LL<Term> LL<T>::multiplyBy(const LL<Term> &product){
    LL<Term> result = LL<Term>();
    for (int i =0; i<this->size(); i++){
        Term t1 = this->at(i);
        for (int j =0; j<product.size(); j++){
            result.push_back(Term(t1.getCoeff()*product.at(j).getCoeff(), t1.getExponent()+product.at(j).getExponent()));
        }
    }
    result.simplify();
    result.sort();
    result.removeDuplicates();
    return result;
}



//END LL CLASS IMPLEMENTATION

