//
//  VectorNum.h
//  Assingment 0
//
//  Created by Oliver Hill on 9/7/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#ifndef VectorNum_h
#define VectorNum_h

#include <stdio.h>
#include <vector>
#include <string>

using namespace std;
class VectorNum{
private:
    vector<int> number;
    bool isNegativeNumber;
    
    //Recursive function that returns true if the number value in the first vector is greater than or equal to the second
    //Pre Condition: vectors reperesent a postive integer with no leading zeros
    bool comparePositiveVectors(vector<int> &, vector<int> &, int =0);
    
    //Postcondition: the second vector will have the value of the nine's complement of the first vector parameter
    void loadNinesCompFromVector(const vector<int> &, vector<int> &);
    
    //Better Big-Oh runtime than running a while loop to grab the first digit of an int
    //Converts number to string, gets the first character, then returns that character as an int
    int getFirstDigit(int number);
    
    //Adds two positive vectors assuming that param1 >= param2. The result is loaded into param3
    void addPositiveVectors(vector<int> &, vector<int> &, vector<int> &);
    
public:
    
    //Contructors
    //Default initializer creates "blank" values
    VectorNum();
    
    //Contructor for creating an instance from a line from the given text file
    VectorNum(string line);
    
    //Constructor for vector<int> and bool parameters
    VectorNum(vector<int> &, bool);
    
    
    //Accessors and mutators
    //vector<int> const getNumber() {return number;}
    void setNumber(vector<int> newNum){ number = newNum; }
    bool const isNegative(){return isNegativeNumber;}
    void setNegative(bool negative){isNegativeNumber = negative;}
    int at(int i){ return number.at(i); }
    int size(){ return number.size(); }
    
    //Overloaded operators
    //These compare THE ABSOLUTE VALUE of the vector numbers. They do not take into account signs
    bool operator>=(VectorNum &v2) { return comparePositiveVectors(number, v2.number); }
    bool operator<(VectorNum &v2){ return !(*this >= v2); }
    bool operator<=(VectorNum &v2){ return comparePositiveVectors(v2.number, number); }
    bool operator>(VectorNum &v2){ return !(*this <= v2); }
    VectorNum operator-(VectorNum&);
    VectorNum operator+(VectorNum&);
};


#endif /* VectorNum_h */
