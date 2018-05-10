//
//  polynomial.hpp
//  long-division-polynominal
//
//  Created by Khoi Lai on 5/10/18.
//  Copyright © 2018 Khoi Lai. All rights reserved.
//

#include <iostream>

class Polynomial {
public:
    Polynomial(double[], int);
    ~Polynomial();
    int getDegree();
    int getSize();
private:
    double *coeffs; // array of terms
    int size; // = highest degree + 1
friend std::ostream &operator<<(std::ostream &os, const Polynomial &p);
};


