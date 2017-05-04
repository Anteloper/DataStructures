//
//  main.cpp
//  MinHeap
//
//  Created by Oliver Hill on 3/22/17.
//  Copyright © 2017 Oliver Hill. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include "MinHeap.cpp"

char displayMenu();

int main(int argc, const char * argv[]) {
    MinHeap<int> heap = MinHeap<int>();
    
    while(true){
        switch(displayMenu()){
            case 'I':
            case 'i':
                std::cout << "Enter a value: ";
                int val;
                std::cin >> val;
                heap.push(val);
                std::cout << "\n\nState of the heap:\n";
                heap.print();
                break;
            case 'P':
            case 'p':
                try{ heap.pop(); }
                catch(...){ std::cout << "\n\nUnderflow encountered\n\n"; }
                std::cout << "\n\nState of the heap:\n";
                heap.print();
                break;
            case 'S':
            case 's':
                heap.sort();
                std::cout << "\n\nState of the heap:\n";
                heap.print();
                break;
            case 'Q':
            case 'q':
                return 0;
                break;
            default://must be quit selection because isCharValid eliminates all other possibilites
                std::cout << "Invalid Entry, try again\n";
        }
    }
    
}

char displayMenu(){
    char userChoice = 'U';//initialized to a valid choice so the cout line does not execute
    std::cout << std::setw(40) << "Insert a new value" << "     i\n";
    std::cout << std::setw(40) << "Pop a value" << "     p\n";
    std::cout << std::setw(40) << "Sort the heap" <<"     s\n";
    std::cout << std::setw(40) << "Quit" <<  "     q\n\n\n";
    
    std::cout << "Enter your choice:  ";
    std::cin >> userChoice;
    return userChoice;
}

















