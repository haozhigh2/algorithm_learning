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
void fast_sort(vector<T>& v, int idx_l, int idx_r) {
    if (idx_l >= idx_r)
        return;

    int idx_last_small {idx_l};
    for (int idx_next = idx_l + 1; idx_next <= idx_r; idx_next++) {
        if (v[idx_next] < v[idx_l]) {
            T tmp = v[idx_last_small + 1];
            v[idx_last_small + 1] = v[idx_next];
            v[idx_next] = tmp;

            idx_last_small += 1;
        }
    }

    T tmp = v[idx_last_small];
    v[idx_last_small] = v[idx_l];
    v[idx_l] = tmp;

    fast_sort(v, idx_l, idx_last_small - 1);
    fast_sort(v, idx_last_small + 1, idx_r);
}

int main(int argc, char** argv) {
    RandInt rand_int{ -(1 << 20), 1 << 20 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(RandInt(100, 1000).Next()) };
        vector<int> v1{ v0 };

        selection_sort(v0);
        fast_sort(v1, 0, int(v1.size()) - 1);

        for (const auto& x: v1)
            cout << x << " ";
        cout << endl;

        if (v0 == v1)
            cout << "########  Pass  ########" << endl;
        else {
            cout << "########  Fail  ########" << endl;
        }
    }

    return 0;
}