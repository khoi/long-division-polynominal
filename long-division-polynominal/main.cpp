#include "polynomial.hpp"
#include <cmath>
#include <cstring>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

#define DEBUG_MODE false

using namespace std;

void replaceSubstr(std::string &str, const std::string &oldStr,
                   const std::string &newStr) {
    std::string::size_type pos = 0u;
    while ((pos = str.find(oldStr, pos)) != std::string::npos) {
        str.replace(pos, oldStr.length(), newStr);
        pos += newStr.length();
    }
}

vector<string> split(const string &str, const string &delim) {
    vector<string> tokens;
    size_t prev = 0, pos = 0;
    do {
        pos = str.find(delim, prev);
        if (pos == string::npos)
            pos = str.length();
        string token = str.substr(prev, pos - prev);
        if (!token.empty())
            tokens.push_back(token);
        prev = pos + delim.length();
    } while (pos < str.length() && prev < str.length());
    return tokens;
}

Polynomial *validateInput(const string &s) {
    string input(s);
    string delim = "+";
    int degree = INT_MIN;
    replaceSubstr(input, "-", "+-");
    vector<string> terms = split(input, delim);
    map<int, double> powAndCoeff;
    for (vector<string>::const_iterator i = terms.begin(); i != terms.end();
         ++i) {
        string term = *i;
        unsigned long positionOfX = term.find('x');
        bool hasX = positionOfX != string::npos;

        if (hasX) {
            unsigned long positionOfPowChar = term.find('^');
            bool hasPow = positionOfPowChar != string::npos;
            if (hasPow) {
                string powString = term.substr(positionOfPowChar + 1);
                stringstream ss1(powString);
                int pow;
                double coeff;
                if (!(ss1 >> pow && ss1.eof())) {
                    cout << term << " " << pow << " is not a valid pow."
                         << endl;
                    return nullptr;
                }

                string coeffString = term.substr(0, positionOfX);

                if (coeffString.length() == 0) {
                    coeff = 1.0;
                } else if (coeffString == "-") {
                    coeff = -1.0;
                } else {
                    stringstream ss2(coeffString);
                    bool coeffConversionFail = (ss2 >> coeff).fail();
                    string remainString;
                    getline(ss2, remainString);

                    if (coeffConversionFail || remainString != "*") {
                        cout << term << " " << coeffString
                             << " is not a valid coeff." << endl;
                        return nullptr;
                    }
                }

                if (coeff == 0) {
                    cout << "Coeff can't be zero." << endl;
                    return nullptr;
                }
                if (DEBUG_MODE)
                    cout << " has pow " << pow << " and coeff " << coeff;
                powAndCoeff[pow] += coeff;
                if (pow > degree)
                    degree = pow;
            } else { // Having pow == 1. For instance: -3*x or just x
                int pow = 1;
                double coeff = 0;
                string coeffString = term.substr(0, positionOfX);

                if (coeffString.length() == 0) { // the term is only x
                    coeff = 1.0;
                } else if (coeffString == "-") { // The term is only -x
                    coeff = -1.0;
                } else {
                    stringstream ss(coeffString);
                    int coeffConversionFail = (ss >> coeff).fail();
                    string remainString;
                    getline(ss, remainString);

                    if (coeffConversionFail || remainString != "*") {
                        cout << term << " " << coeffString
                             << " is not a valid coeff." << endl;
                        return nullptr;
                    }
                }

                if (coeff == 0) {
                    cout << "Coeff can't be zero." << endl;
                    return nullptr;
                }

                if (DEBUG_MODE)
                    cout << " has pow " << pow << " and coeff " << coeff;
                powAndCoeff[pow] += coeff;
                if (pow > degree)
                    degree = pow;
            }
        } else {
            double coeff;
            int pow = 0;
            stringstream ss(term);
            if (!(ss >> coeff && ss.eof())) {
                cout << term << " is not a valid coeff." << endl;
                return nullptr;
                ;
            }

            if (coeff == 0) {
                cout << "Coeff can't be zero." << endl;
                return nullptr;
            }

            if (DEBUG_MODE)
                cout << " has pow " << pow << " and coeff " << coeff;
            powAndCoeff[pow] += coeff;
            if (pow > degree)
                degree = pow;
        }
        if (DEBUG_MODE)
            cout << " " << term << endl;
    }

    int size = degree + 1;
    auto *coeffs = new double[size];

    for (int i = 0; i < size; ++i) {
        coeffs[i] = 0;
    }

    for (auto elem : powAndCoeff) {
        int pow = elem.first;
        double coeff = elem.second;
        coeffs[degree - pow] = coeff;
    }

    return new Polynomial(coeffs, size);
}

int main(int argc, const char *argv[]) {
    string a;
    string b;

    cout << "Enter dividend: ";
    cin >> a;
    auto p1 = validateInput(a);

    if (p1 == nullptr) {
        return 1;
    }

    cout << "Enter divisor: ";
    cin >> b;
    auto p2 = validateInput(b);

    if (p2 == nullptr) {
        return 1;
    }

    auto dividend = *p1;
    auto divisor = *p2;

    if (divisor.isZero()) {
        cout << "Divisor is not allowed to be 0" << endl;
        return 1;
    }

    if (dividend.getDegree() < divisor.getDegree()) {
        cout << "Divisor's degree is higher than the dividend. Terminating."
             << endl;
        return 0;
    }

    if (dividend.isZero()) {
        cout << "Quotient = " << 0 << endl;
        cout << "Remainder = " << 0 << endl;
        return 0;
    }

    Polynomial q = Polynomial();
    Polynomial r = Polynomial(dividend);

    while (!r.isZero() && r.getDegree() >= divisor.getDegree()) {
        int tmpSize = r.getDegree() - divisor.getDegree() + 1;
        auto *tmpCoeffs = new double[tmpSize];
        tmpCoeffs[0] = r.getCoeffs()[0] / divisor.getCoeffs()[0];
        for (int i = 1; i < tmpSize; ++i) {
            tmpCoeffs[i] = 0;
        }
        Polynomial t(tmpCoeffs, tmpSize);

        q += t;
        r -= t * divisor;
    }

    cout << "Quotient = " << q << endl;
    cout << "Remainder = " << r << endl;
    return 0;
}
