//
//  MinHeap.h
//  MinHeap
//
//  Created by Oliver Hill on 5/3/17.
//  Copyright © 2017 Oliver Hill. All rights reserved.

#include <iostream>
#include <vector>


template <typename T>
class MinHeap{
    
private:
    std::vector<T> arr;
    int size;
    int nextIndex;
    
    //Returns index values
    int parent(int index){ return index/2; }
    int leftChild(int index){ return index*2; }
    int rightChild(int index){ return index*2+1; }
    
    //Helper function to swap two indices in the array
    void swap(int index1, int index2);
    
    //Called after every insert
    void heapify(int index);
    
    //Restores the array to a heap after one pop
    void restore(int index);
    
public:
    //First item is always inserted at 1 to maintain heap properties
    MinHeap();
    
    //Inserts the value at the end of the list, swaps upwards as needed
    void push(T n);
    
    //Returns and removes the top item from the heap, restores heap properties
    T& pop();
    
    //Returns the top of the heap
    T& top();
    
    //Prints out the heap as a linear list
    void print() const;
    
    //Sorts the heap
    void sort();
    
    //Will turn any array into a valid heap
    void makeHeap();
    
};








