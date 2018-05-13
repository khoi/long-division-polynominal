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
    memcpy(coeffs, c, s * sizeof(double));
    size = s;
}

int Polynomial::getDegree() const{
    return size - 1;
}

Polynomial::~Polynomial() {
    delete []coeffs;
}

Polynomial &Polynomial::operator+=(const Polynomial &rhs) {
    int newSize = std::max(size, rhs.size);
    double *newCoeffs = new double[newSize];

    for (int i = 0; i < newSize; ++i) {
        newCoeffs[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        int coeff = coeffs[i];
        int pow = getDegree() - i;
        int idxInNewCoeffs = newSize - pow - 1;
        newCoeffs[idxInNewCoeffs] += coeff;
    }

    for (int i = 0; i < rhs.size; ++i) {
        int coeff = rhs.coeffs[i];
        int pow = rhs.getDegree() - i;
        int idxInNewCoeffs = newSize - pow - 1;
        newCoeffs[idxInNewCoeffs] += coeff;
    }

    delete []coeffs;
    coeffs = newCoeffs;
    size = newSize;
    return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial &rhs) {
    int newSize = std::max(size, rhs.size);
    double *newCoeffs = new double[newSize];

    for (int i = 0; i < newSize; ++i) {
        newCoeffs[i] = 0;
    }

    for (int i = 0; i < size; ++i) {
        int coeff = coeffs[i];
        int pow = getDegree() - i;
        int idxInNewCoeffs = newSize - pow - 1;
        newCoeffs[idxInNewCoeffs] += coeff;
    }

    for (int i = 0; i < rhs.size; ++i) {
        int coeff = rhs.coeffs[i];
        int pow = rhs.getDegree() - i;
        int idxInNewCoeffs = newSize - pow - 1;
        newCoeffs[idxInNewCoeffs] -= coeff;
    }

    delete []coeffs;
    coeffs = newCoeffs;
    size = newSize;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
    for (int i = 0; i < p.size; ++i) {
        if (p.coeffs[i] == 0) continue;
        int pow = p.getDegree() - i;
        os << ((i == 0) ? std::noshowpos : std::showpos) << p.coeffs[i] ;

        if (pow > 0) {
            os << "*" << "x";
            if (pow > 1) {
                os << "^" << std::noshowpos <<pow;
            }
        }
    }
    return os;
}
