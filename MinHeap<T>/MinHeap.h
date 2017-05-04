//
//  MinHeap.cpp
//  MinHeap
//
//  Created by Oliver Hill on 5/3/17.
//  Copyright © 2017 Oliver Hill. All rights reserved.
//

#include <stdio.h>
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
    void swap(int index1, int index2){
        T temp = arr[index2];
        arr[index2] = arr[index1];
        arr[index1] = temp;
    }
    
    //Called after every insert
    void heapify(int index){
        int p = parent(index);
        if(index != 1 && arr[p] > arr[index]){
            swap(index, p);
            heapify(p);
        }
    }
    
    //Restores the array to a heap after one pop
    void restore(int index){
        int left = leftChild(index);
        int right = rightChild(index);
        bool hasLeft = left < nextIndex;
        bool hasRight = right < nextIndex;
        
        //Leaf node
        if(!hasLeft && !hasRight) return;
        
        //Is valid heap
        if(hasLeft && arr[index] <= arr[left])
            if((hasRight && arr[index] <= arr[right])|| !hasRight)
                return;
        
        //Recursive case
        int smaller = (hasRight && arr[right] <= arr[left]) ? right : left;
        swap(smaller, index);
        restore(smaller);
    }
    
    
    
    
public:
    //First item is always inserted at 1 to maintain heap properties
    MinHeap(){
        arr = std::vector<T>(3);
        nextIndex = 1;
    }
    
    //Inserts the value at the end of the list, swaps upwards as needed
    void push(T n){
        arr[nextIndex] = n;
        heapify(nextIndex);
        nextIndex++;
    }
    
    //Returns and removes the top item from the heap, restores heap properties
    T pop(){
        if(nextIndex <= 1) throw(std::string("Underflow"));
        T top = arr[1];
        arr[1] = arr[nextIndex-1];
        nextIndex--;
        restore(1);
        return top;
    }
    
    //Returns the top of the heap
    T& top() const{
        if(nextIndex >=2) return arr[1];
        throw(std::string("No items inserted"));
    }
    
    
    //Prints out the heap as a linear list
    void print() const{
        for(int i =1; i<nextIndex; i++)
            std::cout << arr[i] << " ";
        std::cout << "\n\n";
        
    }
    
    //Sorts the heap
    void sort(){
        std::sort(arr.begin(), arr.end());
    }
    
    //Will turn any array into a valid heap
    void makeHeap(){
        for(int i = nextIndex/2; i>0; i--)
            restore(i);
    }
};
