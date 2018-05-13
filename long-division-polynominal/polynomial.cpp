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

int Polynomial::getDegree() const { return size - 1; }

Polynomial::~Polynomial() { delete[] coeffs; }

Polynomial &Polynomial::operator+=(const Polynomial &rhs) {
    int newSize = std::max(size, rhs.size);
    double *newCoeffs = new double[newSize];

    for (int i = newSize - 1; i >= 0; --i) {
        newCoeffs[i] = 0;
        int pow = newSize - i - 1;

        int lhsIdx = getDegree() - pow;
        int rhsIdx = rhs.getDegree() - pow;

        if (lhsIdx >= 0)
            newCoeffs[i] += coeffs[lhsIdx];
        if (rhsIdx >= 0)
            newCoeffs[i] += rhs.coeffs[rhsIdx];
    }

    delete[] coeffs;
    coeffs = newCoeffs;
    size = newSize;

    return *this;
}

Polynomial &Polynomial::operator-=(const Polynomial &rhs) {
    int newSize = std::max(size, rhs.size);
    double *newCoeffs = new double[newSize];

    for (int i = newSize - 1; i >= 0; --i) {
        newCoeffs[i] = 0;
        int pow = newSize - i - 1;

        int lhsIdx = getDegree() - pow;
        int rhsIdx = rhs.getDegree() - pow;

        if (lhsIdx >= 0)
            newCoeffs[i] += coeffs[lhsIdx];
        if (rhsIdx >= 0)
            newCoeffs[i] -= rhs.coeffs[rhsIdx];
    }

    delete[] coeffs;
    coeffs = newCoeffs;
    size = newSize;
    return *this;
}

Polynomial &Polynomial::operator*=(const Polynomial &rhs) {
    int newSize = getDegree() + rhs.getDegree() + 1;
    double *newCoeffs = new double[newSize];

    for (int i = newSize - 1; i >= 0; --i) {
        newCoeffs[i] = 0;
    }

    for (int i = size - 1; i >= 0; --i) {
        for (int j = rhs.size - 1; j >= 0; --j) {
            int lhsPow = getDegree() - i;
            int rhsPow = rhs.getDegree() - j;
            int resultPow = lhsPow + rhsPow;
            newCoeffs[newSize - 1 - resultPow] += coeffs[i] * rhs.coeffs[j];
        }
    }

    delete[] coeffs;
    coeffs = newCoeffs;
    size = newSize;
    return *this;
}

Polynomial &Polynomial::operator*=(double val) {
    double *newCoeffs = new double[size];

    for (int i = size - 1; i >= 0; --i) {
        newCoeffs[i] = coeffs[i] * val;
    }

    delete[] coeffs;
    coeffs = newCoeffs;
    return *this;
}

Polynomial &Polynomial::operator/=(double val) {
    double *newCoeffs = new double[size];

    for (int i = size - 1; i >= 0; --i) {
        newCoeffs[i] = coeffs[i] / val;
    }

    delete[] coeffs;
    coeffs = newCoeffs;
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

Polynomial operator*(const Polynomial &lhs, const Polynomial &rhs) {
    Polynomial result(lhs);
    result *= rhs;
    return result;
}

Polynomial operator*(const Polynomial &lhs, double rhs) {
    Polynomial result(lhs);
    result *= rhs;
    return result;
}

Polynomial operator/(const Polynomial &lhs, double rhs) {
    Polynomial result(lhs);
    result /= rhs;
    return result;
}

bool operator==(const Polynomial &lhs, const Polynomial &rhs) {
    if (lhs.size != rhs.size)
        return false;
    for (int i = 0; i < lhs.size; ++i) {
        if (lhs.coeffs[i] != rhs.coeffs[i]) {
            return false;
        }
    }
    return true;
}

std::ostream &operator<<(std::ostream &os, const Polynomial &p) {
    for (int i = 0; i < p.size; ++i) {
        double coeff = p.coeffs[i];
        int pow = p.getDegree() - i;

        if (coeff == 0)
            continue;

        if (coeff == 1.0) {
            if (i > 0) {
                if (pow >= 1) {
                    std::cout << "+";
                } else {
                    std::cout << (i > 0 ? "+" : "") << coeff;
                }
            }
        } else if (coeff == -1.0) {
            std::cout << "-";
        } else if (coeff < 0.0) {
            std::cout << "-" << -coeff << (pow != 0 ? "*" : "");
        } else {
            std::cout << (i > 0 ? "+" : "") << coeff << (pow != 0 ? "*" : "");
        }

        if (pow == 1)
            std::cout << "x";
        else if (pow > 1)
            std::cout << "x^" << pow;
    }
    return os;
}
