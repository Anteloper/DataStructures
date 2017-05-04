//
//  MinHeap.cpp
//  MinHeap
//
//  Created by Oliver Hill on 5/3/17.
//  Copyright © 2017 Oliver Hill. All rights reserved.
//

#include <iostream>
#include "MinHeap.h"

template <typename T>
void MinHeap<T>::swap(int index1, int index2){
    T temp = arr[index2];
    arr[index2] = arr[index1];
    arr[index1] = temp;
}

template <typename T>
void MinHeap<T>::heapify(int index){
    int p = parent(index);
    if(index != 1 && arr[p] > arr[index]){
        swap(index, p);
        heapify(p);
    }
}

template <typename T>
void MinHeap<T>::restore(int index){
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

template <typename T>
MinHeap<T>::MinHeap(){
    arr = std::vector<T>(3);
    nextIndex = 1;
}

template <typename T>
void MinHeap<T>::push(T n){
    arr[nextIndex] = n;
    heapify(nextIndex);
    nextIndex++;
}

template <typename T>
T& MinHeap<T>::pop(){
    if(nextIndex <= 1) throw(std::string("Underflow"));
    T top = arr[1];
    arr[1] = arr[nextIndex-1];
    nextIndex--;
    restore(1);
    return top;
}

template <typename T>
T& MinHeap<T>::top(){

    if(nextIndex >=2) return arr.at(1);
    throw(std::string("No items inserted"));
}

template <typename T>
void MinHeap<T>::print() const{
    for(int i =1; i<nextIndex; i++)
        std::cout << arr[i] << " ";
    std::cout << "\n\n";
    
}

template <typename T>
void MinHeap<T>::sort(){
    std::sort(arr.begin(), arr.end());
}

template <typename T>
void MinHeap<T>::makeHeap(){
    for(int i = nextIndex/2; i>0; i--)
        restore(i);
}

