
#include "rand.h"
#include <iostream>

template<typename T>
void selection_sort(vector<T>& v) {
    for (unsigned i = 0; i < v.size() - 1; i++) {
        unsigned min_index{ i };
        for (unsigned j = i + 1; j < v.size(); j++)
            if (v[j] < v[min_index])
                min_index = j;
        T tmp = v[i];
        v[i] = v[min_index];
        v[min_index] = tmp;
    }
}

template<typename T>
void merge_sort(vector<T>& v, unsigned l, unsigned r) {
    if (l == r)
        return;
    unsigned m = (l + r) / 2;
    merge_sort(v, l, m);
    merge_sort(v, m + 1, r);

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
            while (l <= r)
                v[l++] = v_l[a++];
            break;
        }
        if (v_l[a] <= v_r[b])
            v[l++] = v_l[a++];
        else
            v[l++] = v_r[b++];
    }
}

int main(int argc, char** argv) {
    RandInt rand_int{ -(1 << 20), 1 << 20 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(1000) };
        vector<int> v1{ v0 };

        selection_sort(v0);
        merge_sort(v1, 0, unsigned int(v1.size()) - 1);

        if (v0 == v1)
            cout << "########  Pass  ########" << endl;
        else
            cout << "########  Fail  ########" << endl;
    }

    return 0;
}