//
//  main.cpp
//  long-division-polynominal
//
//  Created by Khoi Lai on 5/10/18.
//  Copyright © 2018 Khoi Lai. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>
#include "polynomial.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    if (argc == 1) {
        cout << "Please pass 0 or 1 as the program argument" << endl;
        return 1;
    }

    if (argc > 2) {
        cout << "Only 1 argument (0|1) is allowed." << endl;
        return 1;
    }

    const char *option = argv[1];

    int isPrintingName = strcmp(option, "0") == 0;
    int isInNormalMode = strcmp(option, "1") == 0;

    if (!isInNormalMode && !isPrintingName) {
        cout << option << " is not a valid input." << endl;
        return 1;
    }

    if (isPrintingName) {
        cout << "Email goes here" << endl;
        return 0;
    }

    if (isInNormalMode) {
        double a[] = {1, 2, 1};
        double b[] = {1, 1};
        Polynomial p1(a, 3);
        Polynomial p2(b, 2);

        cout <<  p1 << endl;
        cout << "+" << endl;
        cout <<  p2 << endl;
        cout << "_____" << endl;
        cout << p1 + p2 << endl;

        cout << endl;

        cout <<  p2 << endl;
        cout << "-" << endl;
        cout <<  p1 << endl;
        cout << "_____" << endl;
        cout << p2 - p1 << endl;

        return 0;
    }

    return 1;
}
