//
//  Stack.h
//  
//
//  Created by Oliver Hill on 9/27/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include "LL.h"


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                                                                        **
 **                        class Stack<T> declaration                      **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/


//A stack implemented on top of a a linked list. The API hides the linked list from the user.

template <typename T>
class Stack{
private:
    unsigned long count;
    Node<T> *head;
    
    //Private function to be called by assignment operator and copy constructor
    void copyStack(const Stack<T> &);
    
public:
    //Default Constructor
    Stack();
    
    //Destructor
    ~Stack();
    
    //Copy Constructor: May throw a string exception if a bad_alloc in copyList occurs
    Stack(const Stack<T> &);
    
    //Overloaded assignment: May throw a string exception if a bad_alloc in copyList occurs
    Stack<T> operator =(const Stack<T> &);
    
    //API FUNCTIONS
    
    //Push function: Throws a string exception if a bad_alloc occurs
    void push(T&);
    
    //Pop function removes the top element from the stack and deallocates memory
    void pop();
    
    //Top function: List must not be empty
    T& top();
    
    //Empty function: Returns true if the stack is empty
    bool empty(){return head == NULL;}
    
    void print();
};


#endif /* Stack_h */
