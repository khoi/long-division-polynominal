//
//  polynomial_linkedlist.cpp
//  long-division-polynominal
//
//  Created by Khoi Lai on 5/22/18.
//  Copyright © 2018 Khoi Lai. All rights reserved.
//

#include "polynomial_linkedlist.hpp"

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

void PolynomialLL::add(int coeff, int pow) {
    Term *t = new Term();
    t->coeff = coeff;
    t->pow = pow;
    t->next = head;
    head = t;
}

std::ostream &operator<<(std::ostream &os, const PolynomialLL &p) {
    auto node = p.head;
    while (node) {
        os << "coeff: " << node->coeff << " pow: " << node->pow << std::endl;
        node = node->next;
    }
    return os;
}

PolynomialLL &PolynomialLL::operator+=(const PolynomialLL &rhs) {
    Term *current = head;
    Term *newTerm = new Term();
    newTerm->coeff = current->coeff;
    newTerm->pow = current->pow;
    newTerm->next = nullptr;

    Term *headNewTerm = newTerm;
    current = current->next;

    while (current) {
        Term *t = new Term();
        t->coeff = current->coeff;
        t->pow = current->pow;
        newTerm->next = t;
        newTerm = newTerm->next;
        newTerm->next = nullptr;
        current = current->next;
    }


    current = rhs.head; // Iterate through the rhs and add it
    auto *node = headNewTerm;

    while (current) {
        bool powExist = false;
        while (node) {
            if(current->pow == node->pow) {
                node->coeff += current->coeff;
                powExist = true;
                break;
            }
            node = node->next;
        }
        if (!powExist) {
            Term *t = new Term();
            t->coeff = current->coeff;
            t->pow = current->pow;
            newTerm->next = t;
            newTerm = newTerm->next;
            newTerm->next = nullptr;
        }
        current = current->next;
    }


    this->head = headNewTerm;
}
