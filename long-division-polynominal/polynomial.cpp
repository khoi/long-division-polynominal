//
//  polynomial.cpp
//  long-division-polynominal
//
//  Created by Khoi Lai on 5/10/18.
//  Copyright © 2018 Khoi Lai. All rights reserved.
//

#include "polynomial.hpp"

Polynomial::Polynomial(double c[], int s) {
    coeffs = new double[s];
    for (int i = 0; i < s; i++) {
        coeffs[i] = c[i];
    }
    size = s;
}

int Polynomial::getDegree() {
    return size - 1;
}

Polynomial::~Polynomial() {
    delete []coeffs;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
    for (int i = 0; i < p.size; ++i) {
        if (p.coeffs[i] == 0) continue;
        int pow = p.size - (i + 1);
        os << ((i == 0) ? std::noshowpos : std::showpos) << p.coeffs[i] ;
        if (pow > 0) os << "*" << "x" << "^" << std::noshowpos <<pow;
    }
    return os;
}
