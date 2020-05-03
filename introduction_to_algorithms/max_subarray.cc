
#include "rand.h"
#include <iostream>
using namespace std;

template<typename T>
T maximum_subarray_baseline(const vector<T>& v) {
    vector<T> s(v.size() + 1, 0);
    for (unsigned i = 1; i <= v.size(); i++)
        s[i] = s[i - 1] + v[i - 1];
    T max_sum = 0;
    for (unsigned i = 0; i < s.size() - 1; i++)
        for (unsigned j = i + 1; j < s.size(); j++)
            if (s[j] - s[i] > max_sum)
                max_sum = s[j] - s[i];
    return max_sum;
}

template<typename T>
T maximum_subarray(const vector<T>& v) {
    vector<T> s(v.size() + 1, 0);
    vector<T> min_sum(v.size() + 1, 0);
    for (unsigned i = 1; i <= v.size(); i++) {
        s[i] = s[i - 1] + v[i - 1];
        min_sum[i] = s[i] < min_sum[i - 1] ? s[i] : min_sum[i - 1];
    }
    T max_sum = 0;
    for (unsigned i = 1; i <= v.size(); i++)
        if (s[i] - min_sum[i - 1] > max_sum)
            max_sum = s[i] - min_sum[i - 1];
    return max_sum;
}

int main(int argc, char** argv) {
    RandInt rand_int{ -(1 << 15), 1 << 15 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(1000) };

        int n0{ maximum_subarray_baseline(v0) };
        int n1{ maximum_subarray(v0) };

        if (n0 == n1) {
            cout << "########  Pass  ########" << endl;
            cout << n0 << ' ' << n1 << endl;
        }
        else {
            cout << "########  Fail  ########" << endl;
            cout << n0 << ' ' << n1 << endl;
        }
    }
}
