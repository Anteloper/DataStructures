//
//  main.cpp
//  BinaryTree
//
//  Created by Oliver Hill on 10/17/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#include <iostream>
#include "BinaryTree.cpp"


int main(int argc, const char * argv[]) {
    BinaryTree<int> tree;
    tree.insert(5);
    tree.insert(3);
    tree.insert(6);
    tree.printInOrder();
}

