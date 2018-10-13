#include "../include/rand.h"
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
static void max_heapify(vector<T>& v, unsigned n, unsigned i) {
    unsigned l{ (i << 1) + 1 };
    unsigned r{ (i << 1) + 2 };
    unsigned largest{ i };
    if (l < n && v[l] > v[largest])
        largest = l;
    if (r < n && v[r] > v[largest])
        largest = r;
    if (largest != i) {
        T t{ v[i] };
        v[i] = v[largest];
        v[largest] = t;
        max_heapify(v, n, largest);
    }
}

template<typename T>
void heap_sort(vector<T>& v) {
    /*
    ** build max heap
    */
    for (unsigned i = v.size() / 2 - 1; i >= 0; ) {
        max_heapify(v, v.size(), i);
        if (i == 0)
            break;
        i -= 1;
    }

    /*
    ** sort
    */
    for (unsigned n = v.size() - 1; n > 0; n--) {
        T t{ v[n] };
        v[n] = v[0];
        v[0] = t;
        max_heapify(v, n, 0);
    }
}

int main(int argc, char** argv) {
    RandInt rand_int{ -(1 << 20), 1 << 20 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(RandInt(100, 1000).Next()) };
        vector<int> v1{ v0 };

        selection_sort(v0);
        heap_sort(v1);

        if (v0 == v1)
            cout << "########  Pass  ########" << endl;
        else {
            cout << "########  Fail  ########" << endl;
        }
    }

    return 0;
}