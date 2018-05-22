//
//  PolynomialLL_linkedlist.hpp
//  long-division-polynominal
//
//  Created by Khoi Lai on 5/22/18.
//  Copyright © 2018 Khoi Lai. All rights reserved.
//
#include <iostream>

class PolynomialLL {
    struct Term {
        int coeff;
        int pow;
        Term *next;
    };
public:
    PolynomialLL();
    PolynomialLL(const PolynomialLL& p);
    ~PolynomialLL();
    void add(int coeff, int pow);

private:
    Term* head; // head node of the terms
    int length;
    friend std::ostream& operator<<(std::ostream& os, const PolynomialLL& p);
};

