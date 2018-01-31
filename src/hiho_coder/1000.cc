#include <iostream>
#include <string>
#include <cctype>
#include <cstdio>
using namespace std;


extern "C" __declspec(dllexport) int p1032(int argc, char** argv) {
    int N;
    cin >> N;

    char* s = new char[2000002];
    int* r = new int[2000002];  // radius of each number excluding self
    for (int x = 0; x < N; x++) {
        int n = 3;
        s[0] = '#';
        s[1] = getchar();
        while (isspace(s[1]))
            s[1] = getchar();
        s[2] = '#';
        while (true) {
            char c;
            c = getchar();
            if (isspace(c) || c == EOF)
                break;
            else {
                s[n++] = c;
                s[n++] = '#';
            }
        }

        int m = 0;  // id of the number with the right most wing
        int p = 0;  // id of the number with the biggest radius
        r[0] = 0;
        for (int i = 1; i < n; i++) {
            r[i] = 0;
            if (i >= m + r[m]) {
                while (i - r[i] - 1 >= 0 && i + r[i] + 1 < n && s[i - r[i] - 1] == s[i + r[i] + 1])
                    r[i] += 1;
            }
            else {
                int ii = 2 * m - i;
                if (ii - r[ii] > m - r[m]) {
                    r[i] = r[ii];
                }
                else if (ii - r[ii] < m - r[m]) {
                    r[i] = m + r[m] - i;
                }
                else {
                    r[i] = m + r[m] - i;
                    while (i - r[i] - 1 >= 0 && i + r[i] + 1 < n && s[i - r[i] - 1] == s[i + r[i] + 1])
                        r[i] += 1;
                }
            }

            if (i + r[i] > m + r[m])
                m = i;
            if (r[i] > r[p])
                p = i;
        }
        cout << r[p] << '\n';
    }
    delete[] s;
    delete[] r;
    return 0;
}

struct p1000Node {
    p1000Node* next[27];
    int count;

    p1000Node() : count(0) {
        for (int i = 0; i < 27; i++)
            next[i] = 0;
    }

    p1000Node* Add(char c) {
        int idx = int(c - 'a');
        if (next[idx] == 0)
            next[idx] = new p1000Node();
        return next[idx];
    }

    void End() {
        count += 1;
    }
};

extern "C" __declspec(dllexport) int p1000(int argc, char** argv) {
    int n, m;
    p1000Node* head = new p1000Node();

    string line;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> line;
        p1000Node* h = head;
        for (unsigned j = 0; j < line.size(); j++)
            h = h->Add(line[j]);
        h->End();
    }

    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> line;
        p1000Node* h = head;
        bool fail = false;
        for (unsigned j = 0; j < line.size(); j++) {
            h = h->next[line[j] - 'a'];
            if (h == 0) {
                fail = true;
                break;
            }
        }
        if (fail) {
            cout << 0 << endl;
            break;
        }
        cout << h->count << endl;
    }

    return 0;
}
