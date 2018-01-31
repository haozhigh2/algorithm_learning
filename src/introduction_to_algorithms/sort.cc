#include "rand.h"
#include "help.h"



template<typename T>
void selection_sort(vector<T>& v) {
    for (unsigned i = 0; i < v.size() - 1; i++) {
        unsigned min_index{ i };
        for (unsigned j = i + 1; j < v.size(); j++)
            if (v[j] < v[min_index])
                min_index = j;
        Help::Exchange(v[i], v[min_index]);
    }
}

template<typename T>
void insertion_sort(vector<T>& v) {
    for (unsigned i = 1; i < v.size(); i++) {
        T tmp{ v[i] };
        int j{ static_cast<int>(i - 1) };
        while (j >= 0 && v[j] > tmp) {
            v[j + 1] = v[j];
            j -= 1;
        }
        v[j + 1] = tmp;
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

extern "C" __declspec(dllexport) int C02_01_insertion_sort(int argc, char** argv) {
    RandInt rand_int{ -(1 << 20), 1 << 20 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(1000) };
        vector<int> v1{ v0 };

        //Help::PrintVector(v1);

        selection_sort(v0);
        insertion_sort(v1);

        //Help::PrintVector(v1);

        if (v0 == v1)
            cout << "########  Pass  ########" << endl;
        else
            cout << "########  Fail  ########" << endl;
        getchar();
    }
    return 0;
}

extern "C" __declspec(dllexport) int C02_03_merge_sort(int argc, char** argv) {
    RandInt rand_int{ -(1 << 20), 1 << 20 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(1000) };
        vector<int> v1{ v0 };

        //Help::PrintVector(v1);

        selection_sort(v0);
        merge_sort(v1, 0, v1.size() - 1);

        //Help::PrintVector(v1);

        if (v0 == v1)
            cout << "########  Pass  ########" << endl;
        else
            cout << "########  Fail  ########" << endl;
    }
    getchar();
    return 0;
}

extern "C" __declspec(dllexport) int C06_04_heap_sort(int argc, char** argv) {
    RandInt rand_int{ -(1 << 20), 1 << 20 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(RandInt(100, 1000).Next()) };
        vector<int> v1{ v0 };

        //Help::PrintVector(v1);

        selection_sort(v0);
        heap_sort(v1);

        //Help::PrintVector(v1);

        if (v0 == v1)
            cout << "########  Pass  ########" << endl;
        else {
            cout << "########  Fail  ########" << endl;
            Help::PrintVector(v0);
            Help::PrintVector(v1);
            getchar();
        }
    }
    getchar();
    return 0;
}