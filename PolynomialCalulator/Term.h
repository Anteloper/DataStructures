//
//  Term.hpp
//  Homework1
//
//  Created by Oliver Hill on 9/25/16.
//  Copyright © 2016 Oliver Hill. All rights reserved.
//

#ifndef Term_h
#define Term_h

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdexcept>


using namespace std;

class Term{
private:
    int coeff;
    int exponent;
public:
    Term(){};
    Term(int coeff, int exponent){
        this->coeff = coeff;
        this->exponent = exponent;
    }
    
    void setCoeff(int coeff){ this->coeff = coeff; }
    void setExponent(int exponent){ this->exponent = exponent; }
    int getCoeff(){ return coeff;}
    int getExponent(){return exponent;}
    
    friend std::ostream &operator <<(std::ostream &os, const Term &term){
        os << term.coeff << "x^" << term.exponent;
        return os;
    }
};


#endif /* Term_h */
