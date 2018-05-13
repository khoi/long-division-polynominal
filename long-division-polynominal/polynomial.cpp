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
    for (int i = 0; i < s; ++i) {
        coeffs[i] = c[i];
    }
    size = s;
}

Polynomial::Polynomial(const Polynomial &p) {
    coeffs = new double[p.size];
    for (int i = 0; i < p.size; ++i) {
        coeffs[i] = p.coeffs[i];
    }
    size = p.size;
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

Polynomial operator+(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial result(lhs);
    result += rhs;
    return result;
}

Polynomial operator-(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial result(lhs);
    result -= rhs;
    return result;
}

bool operator==(const Polynomial &lhs, const Polynomial &rhs) {
    if (lhs.size != rhs.size) return false;
    for (int i = 0; i < lhs.size; ++i) {
        if (lhs.coeffs[i] != rhs.coeffs[i]) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
    for (int i = 0; i < p.size; ++i) {
        int coeff = p.coeffs[i];
        if (coeff == 0) continue;
        int pow = p.getDegree() - i;

        os << ((i == 0) ? std::noshowpos : std::showpos) << coeff ;
        if (pow > 0) {
            os << "*" << "x";
            if (pow > 1) {
                os << "^" << std::noshowpos <<pow;
            }
        }
    }
    return os;
}
