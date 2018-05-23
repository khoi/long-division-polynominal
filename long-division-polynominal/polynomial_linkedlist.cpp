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
    head = NULL;
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
    Term *copy = new Term();
    copy->coeff = current->coeff;
    copy->pow = current->pow;
    copy->next = nullptr;
    Term *head = copy;

    current = current->next;
    while (current) {
        Term *t = new Term();
        t->coeff = current->coeff;
        t->pow = current->pow;
        copy->next = t;
        copy = copy->next;
        copy->next = nullptr;
        current = current->next;
    }

    this->head = head;
}

void PolynomialLL::add(double coeff, int pow) {
    Term *t = new Term();
    t->coeff = coeff;
    t->pow = pow;
    t->next = head;
    head = t;
}

std::ostream &operator<<(std::ostream &os, const PolynomialLL &p) {
    if (p.isZero()) {
        return os << 0;
    }
    auto node = p.head;
    while (node) {
        os << "coeff: " << node->coeff << " pow: " << node->pow << std::endl;
        node = node->next;
    }
    return os;
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

    if (powAndCoeffs.empty()) {
        this->head = NULL;
    }
    else {
        auto currentIterator = powAndCoeffs.begin();
        Term *node = new Term();

        node->coeff = currentIterator->second;
        node->pow = currentIterator->first;
        node->next = nullptr;

        auto newHead = node;
        ++currentIterator;

        for (auto it = currentIterator; it != powAndCoeffs.end(); ++it) {
            if (it->second == 0) { continue; }
            Term *t = new Term();
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

    if (powAndCoeffs.empty()) {
        this->head = NULL;
    }
    else {
        auto currentIterator = powAndCoeffs.begin();
        Term *node = new Term();

        node->coeff = currentIterator->second;
        node->pow = currentIterator->first;
        node->next = nullptr;

        auto newHead = node;
        ++currentIterator;

        for (auto it = currentIterator; it != powAndCoeffs.end(); ++it) {
            if (it->second == 0) { continue; }
            Term *t = new Term();
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

    if (powAndCoeffs.empty()) {
        this->head = NULL;
    }
    else {
        auto currentIterator = powAndCoeffs.begin();
        Term *node = new Term();

        node->coeff = currentIterator->second;
        node->pow = currentIterator->first;
        node->next = nullptr;

        auto newHead = node;
        ++currentIterator;

        for (auto it = currentIterator; it != powAndCoeffs.end(); ++it) {
            if (it->second == 0) { continue; }
            Term *t = new Term();
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
