//
//  main.cpp
//  long-division-polynominal
//
//  Created by Khoi Lai on 5/10/18.
//  Copyright © 2018 Khoi Lai. All rights reserved.
//

#include "polynomial.hpp"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

void replaceSubstr(std::string& str,
               const std::string& oldStr,
               const std::string& newStr)
{
    std::string::size_type pos = 0u;
    while((pos = str.find(oldStr, pos)) != std::string::npos){
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

vector<string> split(const string& str, const string& delim)
{
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do
    {
        pos = str.find(delim, prev);
        if (pos == string::npos) pos = str.length();
        string token = str.substr(prev, pos-prev);
        if (!token.empty()) tokens.push_back(token);
        prev = pos + delim.length();
    }
    while (pos < str.length() && prev < str.length());
    return tokens;
}

int main(int argc, const char *argv[]) {
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
        cout << "Enter dividend: ";
        string dividend;
        string delim = "+";
        cin >> dividend;
        replaceSubstr(dividend, "-", "+-");
        vector<string> terms = split(dividend, delim);
        map<int, double> powAndCoeff;

        for (vector<string>::const_iterator i = terms.begin(); i != terms.end(); ++i) {
            string term = *i;

            unsigned long positionOfX = term.find('x');
            bool hasX = positionOfX != string::npos;

            if (hasX) {
                unsigned long positionOfPowChar = term.find("^");
                bool hasPow = positionOfPowChar != string::npos;
                if (hasPow) {
                    string powString = term.substr(positionOfPowChar + 1);
                    stringstream ss1(powString);
                    int pow;
                    double coeff;
                    if (!(ss1 >> pow && ss1.eof())) {
                        cout << term << " is not a valid term." << endl;
                        return 1;
                    }

                    string coeffString = term.substr(0, positionOfX);
                    stringstream ss2(coeffString);
                    bool coeffConversionFail = (ss2 >> coeff).fail();
                    string remainString;
                    getline(ss2, remainString);

                    if (coeffString.length() == 0) { // case where coeff = 1. For instance: x^3
                        coeff = 1;
                    }
                    else if (coeffConversionFail || remainString != "*") {
                        cout << term << " is not a valid term." << endl;
                        return 1;
                    }
                    cout << " has pow " << pow << " and coeff " << coeff;
                    powAndCoeff[pow] += coeff;
                } else { // Having pow == 1. For instance: -3*x
                    int pow = 1;
                    double coeff = 0;
                    string coeffString = term.substr(0, positionOfX);
                    stringstream ss(coeffString);
                    int coeffConversionFail = (ss >> coeff).fail();
                    string remainString;
                    getline(ss, remainString);

                    if (coeffConversionFail || remainString != "*") {
                        cout << term << " is not a valid term." << endl;
                        return 1;
                    }
                    cout << " has pow " << pow << " and coeff " << coeff;
                    powAndCoeff[pow] += coeff;
                }
            } else {
                double coeff;
                stringstream ss(term);
                if (!(ss >> coeff && ss.eof())) {
                    cout << term << " is not a valid term." << endl;
                    return 1;
                }
                cout << " has pow " << 0 << " and coeff " << coeff;
                powAndCoeff[0] += coeff;
            }
            cout << " " << term << endl;
        }

        for(auto elem : powAndCoeff)
        {
            cout << elem.first << " " << elem.second << "\n";
        }
    }

    return 1;
}
