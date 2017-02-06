/*
 *  LL.h
 *
 *  Author: Oliver Hill
 */

#ifndef LL_h
#define LL_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>

#include "Term.h"

/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                        class Node declaration                          **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/



template <typename T>
class Node{
public:
    T info;
    Node<T> *next;
    Node(T = T(), Node<T>* = NULL);
    
    template <typename F>
    friend std::ostream &operator <<(std::ostream &, const Node<F>&);
    
};//END NODE CLASS DEFINITION



/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                        class LL<T> declaration                         **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/
template <typename T>
class LL{
private:
    unsigned long count;
    Node<T> *head;
    
    //Private function called by overloaded assignment operator and copy contructor
    void copyList(const LL<T> &);
    
public:
    //Default Constructor
    LL();
    
    //Destructor
    ~LL(){ this->clear(); }
    
    //Copy Constructor: May throw a string exception if a bad_alloc in copyList occurs
    LL(const LL<T> &);
    
    //Overloaded assignment: May throw a string exception if a bad_alloc in copyList occurs
    LL<T> operator =(const LL<T> &);
    
    //Push_back function: Throws a string exception if a bad_alloc occurs
    void push_back(T);
    
    //Insert function: Throws a string exception if a bad_alloc occurs
    void insert(T);
    
    //Pop_back function removes the last element from the list and deallocates memory
    void pop_back();
    
    //Remove function removes all objects from the list and deallocates memory
    void clear();
    
    //Size function returns number of objects in the linked list
    unsigned long size() const{return count;}
    
    //At function, same as at function of vector class, May throw std::out_of_range exception
    T& at(int) const;

    //Friend function, overloaded stream insertion operator mainly for testing
    template <typename F>
    friend std::ostream &operator <<(std::ostream &, const LL<F>&);
    
    //Polynomial Specific Functions
    LL<Term> addTo(const LL<Term> &);
    
    LL<Term> subtractFrom(const LL<Term> &);
    
    LL<Term> multiplyBy(const LL<Term> &);
    
    LL<Term> divideBy(const LL<Term> &);
    
    void simplify();
    
    void removeDuplicates();
    
    void sort();
   
    void print();
    
};//END LL CLASS DEFINITION

#endif
