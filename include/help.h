#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Help {
public:
    template<typename T>
    static void Exchange(T& a, T& b) {
        T c;
        c = a;
        a = b;
        b = c;
    }

    template<typename T>
    static void PrintVector(const vector<T>& v) {
        for (const auto& it : v)
            cout << it << ' ';
        cout << "\n\n";
    }
};
