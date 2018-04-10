#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;



void p1000() {
    int a, b;
    cin >> a >> b;
    while (cin.good()) {
        cout << a + b << endl;
        cin >> a >> b;
    }
}

void p1014() {
	int n, m;

	struct Node {
		int count;
		Node* next[26];

		Node() : count(0) {
			for (int i = 0; i < 26; i++)
				next[i] = nullptr;
		};
		~Node() {
			for (int i = 0; i < 26; i++)
				if (next[i] != nullptr)
					delete next[i];
		}
	};

	Node* data = new Node();
	Node* node;
	string line;

	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> line;
		node = data;
		for (auto& c : line) {
			int idx = static_cast<int>(c - 'a');
			if (node->next[idx] == nullptr)
				node->next[idx] = new Node();
			node = node->next[idx];
			node->count++;
		}
	}

	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> line;
		node = data;
		for (auto it = line.begin(); it != line.end() && node != nullptr; it++)
			node = node->next[static_cast<int>((*it) - 'a')];
		if (node == nullptr)
			cout << 0 << endl;
		else
			cout << node->count << endl;
	}

	delete data;
}

void p1015() {
	int N;
	string pattern;
	string s;
	vector<int> next;
	cin >> N;

	for (int n = 0; n < N; n++) {
		cin >> pattern;
		next.resize(pattern.size());

		next[0] = -1;
		for (int i = 1; i < int(pattern.size()); i++) {
			next[i] = -1;
			int m = i - 1;
			while (next[m] >= 0) {
				if (pattern[i] == pattern[next[m] + 1]) {
					next[i] = next[m] + 1;
					break;
				}
				else {
					m = next[m];
				}
			}
			if (next[i] == -1)
				if (pattern[i] == pattern[0])
					next[i] = 0;
			//cout << "           " << next[i] << endl;
		}

		cin >> s;
		int match = 0;
		int j = 0;	// index in pattern string
		for (int i = 0; i < int(s.size());) {
			//cout << j << " " << i << endl;
			if (s[i] == pattern[j]) {
				i += 1;
				j += 1;
				if (j == int(pattern.size())) {
					match += 1;
					j = next[j - 1] >= 0 ? next[j - 1] + 1 : 0;
				}
			}
			else {
				if (j == 0)
					i += 1;
				else
					j = next[j - 1] >= 0 ? next[j - 1] +1 : 0;
			}
		}
		cout << match << endl;
	}
}

void p1032() {
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
}

string p1049_fun(const string& pre, const string& in) {
    // recursion end point
    if (pre.size() <= 1)
        return pre;

    size_t n = 0;   // number of nodes in the left sub tree
    while (in[n] != pre[0])
        n += 1;

    // recursion
    return p1049_fun(pre.substr(1, n), in.substr(0, n)) +
        p1049_fun(pre.substr(1 + n, pre.npos), in.substr(1 + n, in.npos)) +
        pre[0];
}

void p1049() {
    string pre, in;
    cin >> pre >> in;
    cout << p1049_fun(pre, in);
}

void p1374() {
    string input;

    while (true) {
        cin >> input;
        if (input == "END")
            break;

        size_t i = 0;  // index
        int sum = 0;    // result
        bool op = true; // true for +, false for -

        // process a number and the operator before it for each loop
        while (i < input.size()) {
            // get operator if exists
            if (input[i] == '+') {
                op = true;
                i += 1;
            }
            else if (input[i] == '-') {
                op = false;
                i += 1;
            }
            // get number
            int n = 0;
            while (i < input.size() && input[i] >= '0' && input[i] <= '9')
                n = (n * 10) + (input[i++] - '0');
            // do the operation
            sum += op ? n : -n;
        }
        cout << sum << endl;
    }
}
