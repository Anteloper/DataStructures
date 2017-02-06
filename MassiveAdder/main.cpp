//
//  main.cpp
//  Assingment 0
//
//  Created by Oliver Hill on 9/4/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "VectorNum.h"

using namespace std;

///Users/oliverhill/Desktop/numbers.txt


void printCalculation(VectorNum &minuend, VectorNum &subtrahend, bool isAddition, VectorNum &result){
    string dashedLine = "";
    dashedLine.assign(75, '-');
    
    string spacer = "";
    spacer.assign(74-minuend.size(), ' ');
    cout << "\n\n\n" << spacer;
    char sign1 = minuend.isNegative() ? '-' : ' ';
    cout << sign1;
    for(int i = 0; i< minuend.size(); i++){
        cout << minuend.at(i);
    }
    cout << "\n";
    spacer.assign(74-subtrahend.size(), ' ');
    cout << spacer;
    char sign2 = subtrahend.isNegative() ? '-' : ' ';
    cout << sign2;
    for(int i = 0; i< subtrahend.size(); i++){
        cout << subtrahend.at(i);
    }
    cout << "\n";
    char sign = isAddition ? '+' : '-';
    cout << sign << "\n" << dashedLine << "\n";
    
    if( result.isNegative()){ cout << "-"; }
    for(int i = 0; i<result.size(); i++){
        cout << result.at(i);
    }
    cout << "\n\n\n";
}


int main(int argc, const char * argv[]) {
    //VectorNum objects
    VectorNum minuend;
    VectorNum subtrahend;
    VectorNum result;
    
    //Bool to store operation
    bool isOperationAddition = false;
    
    //Variables for file processing
    string fileName = "";
    ifstream inputFile;
    string line;
    
    //Prompt input
    cout << "Enter file name \n";
    cin >> fileName;
    
    //Begin file processing
    inputFile.open(fileName.c_str());
    if(inputFile){
        int iterator = 1;
        while(getline(inputFile, line)){
            switch(iterator){
                case 1:
                    minuend = VectorNum(line);
                    break;
                case 2:
                    subtrahend = VectorNum(line);
                    break;
                case 3:
                    isOperationAddition = (line[0] == '+') ? true : false;
                    if (isOperationAddition){
                        result = minuend+subtrahend;
                    }
                    else{
                        result = minuend-subtrahend;
                    }
                    printCalculation(minuend, subtrahend, isOperationAddition, result);
                    break;
            }
        
            //Reset the iterator after calculation is completed every three lines
            iterator = iterator < 3 ? (++iterator) : 1;
        }
    }
    return 0;
}
