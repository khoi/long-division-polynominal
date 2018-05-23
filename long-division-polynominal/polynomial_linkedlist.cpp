//
//  polynomial_linkedlist.cpp
//  long-division-polynominal
//
//  Created by Khoi Lai on 5/22/18.
//  Copyright © 2018 Khoi Lai. All rights reserved.
//

#include "polynomial_linkedlist.hpp"

#include <map>

PolynomialLL::PolynomialLL() {
    head = nullptr;
    length = 0;
}

PolynomialLL::~PolynomialLL() {
    Term *term = head;
    while (term) {
        Term *deleteMe = term;
        term = term->next;
        delete deleteMe;
    }
}

PolynomialLL::PolynomialLL(const PolynomialLL &p) {
    Term *current = p.head;
    auto *copy = new Term();
    copy->coeff = current->coeff;
    copy->pow = current->pow;
    copy->next = nullptr;
    Term *head = copy;

    current = current->next;
    while (current) {
        auto *t = new Term();
        t->coeff = current->coeff;
        t->pow = current->pow;
        copy->next = t;
        copy = copy->next;
        copy->next = nullptr;
        current = current->next;
    }

    this->head = head;
    this->length = p.length;
}

void PolynomialLL::add(double coeff, int pow) {
    auto *t = new Term();
    t->coeff = coeff;
    t->pow = pow;
    t->next = head;
    head = t;
    ++length;
}

std::ostream &operator<<(std::ostream &os, const PolynomialLL &p) {
    if (p.isZero()) {
        return os << 0;
    }
    auto node = p.head;
    while (node) {
        if (node->coeff == 1.0) {
            if (node != p.head) {
                if (node->pow >= 1)
                    os << "+";
                else
                    os << (node != p.head ? "+" : "") << node->coeff;
            }
        } else if (node->coeff == -1.0) {
            if (node->pow >= 1)
                os << "-";
            else
                os << node->coeff;
        } else if (node->coeff < 0.0) {
            os << "-" << -node->coeff << (node->pow != 0 ? "*" : "");
        } else {
            os << (node != p.head ? "+" : "") << node->coeff << (node->pow != 0 ? "*" : "");
        }

        if (node->pow == 1)
            os << "x";
        else if (node->pow > 1)
            os << "x^" << node->pow;
        node = node->next;
    }
    return os;
}

PolynomialLL operator*(const PolynomialLL& lhs, const PolynomialLL& rhs){
    PolynomialLL result(lhs);
    result *= rhs;
    return result;
}

PolynomialLL &PolynomialLL::operator+=(const PolynomialLL &rhs) {
    std::map<int, double, std::greater<int>> powAndCoeffs;

    Term *current = head;
    while (current) {
        if (powAndCoeffs[current->pow]) {
            powAndCoeffs[current->pow] += current->coeff;
        } else {
            powAndCoeffs[current->pow] = current->coeff;
        }
        auto deleteMe = current;
        current = current->next;
        delete deleteMe;
    }

    current = rhs.head; // Iterate through the rhs and add it
    while (current) {
        if (powAndCoeffs[current->pow]) {
            powAndCoeffs[current->pow] += current->coeff;
        } else {
            powAndCoeffs[current->pow] = current->coeff;
        }
        current = current->next;
    }

    for (auto it = powAndCoeffs.cbegin(); it != powAndCoeffs.cend();) { // Remove value where coeff = 0
        if ((*it).second == 0) {
            powAndCoeffs.erase(it++);
        }
        else {
            ++it;
        }
    }

    this->length = powAndCoeffs.size();
    if (powAndCoeffs.empty()) {
        this->head = nullptr;
    }
    else {
        auto currentIterator = powAndCoeffs.begin();
        auto *node = new Term();

        node->coeff = currentIterator->second;
        node->pow = currentIterator->first;
        node->next = nullptr;

        auto newHead = node;
        ++currentIterator;

        for (auto it = currentIterator; it != powAndCoeffs.end(); ++it) {
            if (it->second == 0) { continue; }
            auto *t = new Term();
            t->pow = it->first;
            t->coeff = it->second;
            t->next = nullptr;
            node->next = t;
            node = t;
        }
        this->head = newHead;
    }


    return *this;
}

PolynomialLL &PolynomialLL::operator-=(const PolynomialLL &rhs) {
    std::map<int, double, std::greater<int>> powAndCoeffs;

    Term *current = head;
    while (current) {
        if (powAndCoeffs[current->pow]) {
            powAndCoeffs[current->pow] += current->coeff;
        } else {
            powAndCoeffs[current->pow] = current->coeff;
        }
        auto deleteMe = current;
        current = current->next;
        delete deleteMe;
    }

    current = rhs.head; // Iterate through the rhs and add it
    while (current) {
        if (powAndCoeffs[current->pow]) {
            powAndCoeffs[current->pow] -= current->coeff;
        } else {
            powAndCoeffs[current->pow] = current->coeff;
        }
        current = current->next;
    }

    for (auto it = powAndCoeffs.cbegin(); it != powAndCoeffs.cend();) { // Remove value where coeff = 0
        if ((*it).second == 0) {
            powAndCoeffs.erase(it++);
        }
        else {
            ++it;
        }
    }

    this->length = powAndCoeffs.size();
    if (powAndCoeffs.empty()) {
        this->head = nullptr;
    }
    else {
        auto currentIterator = powAndCoeffs.begin();
        auto *node = new Term();

        node->coeff = currentIterator->second;
        node->pow = currentIterator->first;
        node->next = nullptr;

        auto newHead = node;
        ++currentIterator;

        for (auto it = currentIterator; it != powAndCoeffs.end(); ++it) {
            if (it->second == 0) { continue; }
            auto *t = new Term();
            t->pow = it->first;
            t->coeff = it->second;
            t->next = nullptr;
            node->next = t;
            node = t;
        }
        this->head = newHead;
    }


    return *this;
}

PolynomialLL &PolynomialLL::operator*=(const PolynomialLL &rhs) {
    std::map<int, double, std::greater<int>> powAndCoeffs;

    Term *current = head;
    while (current) {
        Term *currentRhs = rhs.head;
        while (currentRhs) {
            int pow = current->pow + currentRhs->pow;
            double coeff = current->coeff * currentRhs->coeff;
            if (coeff != 0) {
                powAndCoeffs[pow] = coeff;
            }
            currentRhs = currentRhs->next;
        }
        auto deleteMe = current;
        current = current->next;
        delete deleteMe;
    }

    for (auto it = powAndCoeffs.cbegin(); it != powAndCoeffs.cend();) { // Remove value where coeff = 0
        if ((*it).second == 0) {
            powAndCoeffs.erase(it++);
        }
        else {
            ++it;
        }
    }

    this->length = powAndCoeffs.size();
    if (powAndCoeffs.empty()) {
        this->head = nullptr;
    }
    else {
        auto currentIterator = powAndCoeffs.begin();
        auto *node = new Term();

        node->coeff = currentIterator->second;
        node->pow = currentIterator->first;
        node->next = nullptr;

        auto newHead = node;
        ++currentIterator;

        for (auto it = currentIterator; it != powAndCoeffs.end(); ++it) {
            if (it->second == 0) { continue; }
            auto *t = new Term();
            t->pow = it->first;
            t->coeff = it->second;
            t->next = nullptr;
            node->next = t;
            node = t;
        }
        this->head = newHead;
    }


    return *this;
}

bool PolynomialLL::isZero() const {
    return head == nullptr;
}

int PolynomialLL::getDegree() const {
    if (head == nullptr) return 0;
    return head->pow;
}

double PolynomialLL::getCoeff(int degree) {
    auto *node = head;

    while (node) {
        if (node->pow == degree) {
            return node->coeff;
        }
        node = node->next;
    }

    return 0;
}
