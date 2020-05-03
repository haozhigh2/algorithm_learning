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

int main(int argc, char** argv) {
    RandInt rand_int{ -(1 << 20), 1 << 20 };
    for (unsigned i = 0; i < 10; i++) {
        vector<int> v0{ rand_int.NextVector(100) };
        vector<int> v1{ v0 };

        selection_sort(v0);
        insertion_sort(v1);

        cout << "########################" << endl;
        cout << "####     Test" << i + 1 << endl;
        for (const auto& x: v1)
            cout << x << " ";
        cout << endl;

        if (v0 == v1) {
            cout << "####      Pass      ####" << endl;
            cout << "########################" << endl;
        }
        else {
            cout << "####      Fail      ####" << endl;
            cout << "########################" << endl;
        }
    }

    return 0;
}