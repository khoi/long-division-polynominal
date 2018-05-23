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
        double coeff;
        int pow;
        Term *next;
    };
public:
    PolynomialLL();
    PolynomialLL(const PolynomialLL& p);
    ~PolynomialLL();
    void add(double coeff, int pow);
    int getLength() const;
    bool isZero() const;

    PolynomialLL& operator+=(const PolynomialLL& rhs);
    PolynomialLL& operator-=(const PolynomialLL& rhs);
    PolynomialLL& operator*=(const PolynomialLL& rhs);

private:
    int length;
    Term* head; // head node of the terms
    friend std::ostream& operator<<(std::ostream& os, const PolynomialLL& p);
};

