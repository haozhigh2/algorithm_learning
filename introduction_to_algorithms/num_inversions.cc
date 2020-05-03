#include "rand.h"
#include <iostream>
#include <unordered_set>
using namespace std;


template<typename T>
unsigned inversions_baseline(const vector<T>& v) {
    unsigned n{ 0 };
    for (unsigned i = 0; i < v.size() - 1; i++)
        for (unsigned j = i + 1; j < v.size(); j++)
            if (v[i] > v[j])
                n += 1;
    return n;
}

template<typename T>
unsigned inversions(vector<T>& v, unsigned l, unsigned r) {
    if (l == r)
        return 0;
    unsigned n{ 0 };
    unsigned m = (l + r) / 2;
    n += inversions(v, l, m);
    n += inversions(v, m + 1, r);

    vector<T> v_l(v.begin() + l, v.begin() + m + 1);
    vector<T> v_r(v.begin() + m + 1, v.begin() + r + 1);
    unsigned a{ 0 };
    unsigned b{ 0 };
    while (l <= r) {
        if (a == v_l.size()) {
            while (l <= r)
                v[l++] = v_r[b++];
            break;
        }
        if (b == v_r.size()) {
            while (l <= r) {
                v[l++] = v_l[a++];
                n += b;
            }
            break;
        }
        if (v_l[a] <= v_r[b]) {
            v[l++] = v_l[a++];
            n += b;
        }
        else
            v[l++] = v_r[b++];
    }
    return n;
}


int main(int argc, char** argv) {
    RandInt rand_int{ -(1 << 20), 1 << 20 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(1000) };
        unordered_set<int> s(v0.begin(), v0.end());
        vector<int> v1(s.begin(), s.end());
        vector<int> v2(v1);

        unsigned n0{ inversions_baseline(v1) };
        unsigned n1{ inversions(v2, 0, unsigned int(v2.size()) - 1) };

        if (n0 == n1) {
            cout << "########  Pass  ########" << endl;
            cout << n0 << ' ' << n1 << endl;
        }
        else {
            cout << "########  Fail  ########" << endl;
            cout << n0 << ' ' << n1 << endl;
        }
    }

    return 0;
}