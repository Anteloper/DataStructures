//
//  main.cpp
//  Homework1
//
//  Created by Oliver Hill on 9/25/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "LL.cpp"
#include "Term.h"
#include "Stack.cpp"

using namespace std;

//Returns true if the string represents an operation entered into the text file
bool isOperation(string possibleOp);

//Splits a string into tokens separated by tabs and loads it into the vector elems
void split(const string &s, char delim, vector<string> &elems);

//Loads a polynomial from a string assuming that the polynomial is separated by tabs
void loadPolynomialFromString(string line, LL<Term> &polynomial);

//Safely retrieves from the polynomialf from the stack if possible, if not it throws a string exception
LL<Term> getNextPolynomialFromStack(Stack<LL<Term>> &polyStack);

//Performs the approriate operation and pushes the result onto the stack
void performOperation(char op, Stack<LL<Term>> &polyStack);


int main(int argc, const char * argv[]) {
    
    //Variables for file processing
    string fileName = "";
    ifstream inputFile;
    string line;
    
    //Prompt input
    cout << "Enter file name \n";
    cin >> fileName;
    
    //File Processing
    Stack<LL<Term>> polyStack; //A stack of linked lists of terms. Each linked list represents a polynomial
    
    //Begin file processing
    inputFile.open(fileName.c_str());
    if(inputFile){//Open file
        while(getline(inputFile, line)){
            LL<Term> polynomial = LL<Term>();
            
            if (isOperation(line)){
                try{
                    performOperation(line[0], polyStack);
                }
                catch(string exc){
                    cout << exc << "\n\nThe program will exit now.\n\n";
                    return 0;
                }
            }
            else{//Parse out the line into distinct terms
                loadPolynomialFromString(line, polynomial);
                polyStack.push(polynomial);
                cout << "Pushed polynomial on to stack. Current state of stack: \n";
                polyStack.print();
                cout << "\n\n";
            }
        }
    }
    else{
        cout << "Could not open the file inputted, the program will exit now.\n";
    }
    return 0;
}



//Returns true if the string represents an operation entered into the text file
bool isOperation(string possibleOp){
    if (possibleOp != "+" && possibleOp != "-" && possibleOp != "*"){
        if(possibleOp != "/" && possibleOp != "(" && possibleOp != ")"){
            return false;
        }
    }
    return true;
}


//Code copied and pasted from Stack Overflow to split a string by a specified delimiter.
//I understand how it works completely.
//Author: Evan Teran
//Source: http://stackoverflow.com/questions/236129/split-a-string-in-c
void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss;
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}


//Loads a polynomial from a string assuming that the polynomial is separated by tabs
void loadPolynomialFromString(string line, LL<Term> &polynomial){
    bool isCoeff = true;
    char delimiter = ' ';//Tab character
    Term term;
    
    vector<string> terms;
    split(line, delimiter, terms);//Split by tabs
    
    for(int i=0; i<terms.size(); i++) {//Term processing
        if (isCoeff){
            term = Term();
            //Convert the string at i to an int and set it to the coefficient
            term.setCoeff(stoi(terms.at(i)));
            isCoeff = false;
        }
        else{
            //Convert the string at i to an int and set it to the coefficient
            term.setExponent(stoi(terms.at(i)));
            polynomial.push_back(term);
            isCoeff = true;
        }
    }
}

//Safely gets the next polynomial from the stack
//If there are not enough polynomials on the stack for the operations
//This function will throw a string exception.
LL<Term> getNextPolynomialFromStack(Stack<LL<Term>> &polyStack){
    LL<Term> nextPoly;
    if(!polyStack.empty()){
        nextPoly= polyStack.top();
        polyStack.pop();
    }
    else{
        throw(string("More operators were added than possible for the amount of operands"));
    }
    return nextPoly;
}

//Performs the approriate operation and pushes the result onto the stack
void performOperation(char op, Stack<LL<Term>> &polyStack){
    cout << "Encountered operation " << op;
    LL<Term> top;
    LL<Term> second;
    try{
        top = getNextPolynomialFromStack(polyStack);
        second = getNextPolynomialFromStack(polyStack);
    }
    catch(string exc){
        throw(string(exc));
    }
    LL<Term> result;
    switch(op){
        case '+':
            result = top.addTo(second);
            break;
        case '-':
            result = top.subtractFrom(second);
            break;
        case '*':
            result = top.multiplyBy(second);
            break;
        default:
            throw(string("An operation was entered that is not supported"));
    }
    polyStack.push(result);
    cout << "\nState of stack after opereration\n";
    polyStack.print();
    cout << "\n\n";
}


