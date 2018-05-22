//
//  polynomial_linkedlist.cpp
//  long-division-polynominal
//
//  Created by Khoi Lai on 5/22/18.
//  Copyright © 2018 Khoi Lai. All rights reserved.
//

#include "polynomial_linkedlist.hpp"

PolynomialLL::PolynomialLL() {
    length = 0;
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
    this->length = p.length;
}

void PolynomialLL::add(int coeff, int pow) {
    Term *t = new Term();
    t->coeff = coeff;
    t->pow = pow;
    t->next = head;
    head = t;
    length++;
}

std::ostream &operator<<(std::ostream &os, const PolynomialLL &p) {
    auto node = p.head;
    while (node) {
        os << "coeff: " << node->coeff << " pow: " << node->pow << std::endl;
        node = node->next;
    }
    return os;
}
