//
//  VectorNum.cpp
//  Assingment 0
//
//  Created by Oliver Hill on 9/7/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#include <iostream>
#include "VectorNum.h"
#include <vector>

using namespace std;

bool VectorNum::comparePositiveVectors(vector<int> &v1, vector<int> &v2, int index){
    if (v1.size() != v2.size()){
        return v1.size() > v2.size();
    }
    else{//Vectors have same number of digits
        if (index == v1.size())
            return true;//If control reaches this point all digits have been compared, the numbers are equal
        
        else{
            if (v1.at(index) != v2.at(index)){
                return v1.at(index) > v2.at(index);
            }
            else{
                return comparePositiveVectors(v1, v2, index+1);
            }
        }
    }
}

void VectorNum::loadNinesCompFromVector(const vector<int> &v1, vector<int> &v2){
    v2.clear();
    for (int i = 0; i < v1.size(); i++)
        v2.push_back(-(v1.at(i)) + 9);
}

int VectorNum::getFirstDigit(int number){
    string carryString = to_string(number);
    // Source: http://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
    return carryString[0] - '0';
}

void VectorNum::addPositiveVectors(vector<int> &v1, vector<int> &v2, vector<int> &result){
    int carry = 0;
    //Assuming v1.size() >= v2.size()
    for(int i = 1; i<=v1.size(); i++){
        int bottomDigit = (v2.size() < i) ? 0 : v2.at(v2.size() - i);
        int digit = v1.at(v1.size()-i) + bottomDigit + carry;
        if (digit < 10){
            result.push_back(digit);
            carry = 0;
        }
        else{
            result.push_back(digit%10);
            carry = getFirstDigit(digit);
        }
    }
    if (carry != 0)
        result.push_back(carry);
    
    reverse(result.begin(), result.end());
}

VectorNum::VectorNum(){
    number = vector<int>();
    isNegativeNumber = false;
}

VectorNum::VectorNum(string line){
    number.clear();
    char sign = ' ';
    int firstDigit = 0;
    
    if (line[0] == '+' || line[0] == '-'){
        sign = line[0];
        firstDigit = 1;
    }
    
    //If there is not a '-' in front of the number, there is either a '+' or nothing at all
    isNegativeNumber = (sign == '-');
    
    for(int i = firstDigit; i < line.size(); i++){
        if (isdigit(line[i])){
            //Source: http://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
            int charInt = line[i]-'0';
            number.push_back(charInt);
        }
    }
}

VectorNum::VectorNum(vector<int> &v, bool isNegative){
    number = v;
    isNegativeNumber = isNegative;
}

VectorNum VectorNum::operator-(VectorNum &v2){
    //Both positive
    if (!this->isNegative() && !v2.isNegative()){
        bool shouldNegateResult = false;
        vector<int> larger = this->number;
        vector<int> smaller = v2.number;
        if (!comparePositiveVectors(this->number, v2.number)){
            shouldNegateResult = true;
            larger = v2.number;
            smaller = this->number;
        }
        //Logic from wikipedia article given by professor
        vector<int> ninesComp;
        loadNinesCompFromVector(larger, ninesComp);
        vector<int> temp;
        addPositiveVectors(ninesComp, smaller, temp);
        vector<int> result;
        loadNinesCompFromVector(temp, result);
        return VectorNum(result, shouldNegateResult);
    }
    
    //One positive one negative. Add absolute values and negate answer
    else if (this -> isNegative() != v2.isNegative()){
        //Only negate if the minuend is negative.
        bool shouldNegateResult = this -> isNegative();
        vector<int> result;
        addPositiveVectors(this->number, v2.number, result);
        
        //If the subtrahend is negative, signs cancel and we can do normal addition
        return(VectorNum(result, shouldNegateResult));
    }
    
    //Both negative. Let the signs cancel and treat as addition
    else{
        VectorNum positiveSubtrahend = VectorNum(v2.number, false);
        return *this + positiveSubtrahend;
    }
}

VectorNum VectorNum::operator+(VectorNum &v2){
    //Both positive or both negative
    if (this->isNegative() == v2.isNegative()){
        vector<int> result;
        //Add absolute values and store in result
        addPositiveVectors(this->number, v2.number, result);
        
        //Return result if both were positive, negative result if both were negative
        return VectorNum(result, this->isNegative());
    }
    
    //One positive, one negative
    else{
        VectorNum larger = comparePositiveVectors(this->number, v2.number) ? *this : v2;
        VectorNum smaller = comparePositiveVectors(this->number, v2.number) ? v2 : *this;
        
        //Larger number is negative. Subtract smaller number from absolute value of larger number and negate result
        if (larger.isNegative()){
            larger.setNegative(false);
            VectorNum result = larger-smaller;
            result.setNegative(true);
            return result;
        }
        //Smaller number is negative. Subtract absolute value of smaller number from larger numbers
        else{
            smaller.setNegative(false);
            VectorNum result;
            result = larger-smaller;
            return result;
        }
    }
}




