#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <map>
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

void p1038() {
	int I;	// number of items
	int N;	// total number of needs available
	vector<int> ns;	// need for each item
	vector<int> vs;	// value for each item
	vector<map<int, int>> data;	// data for dp algorithm

	function<void(int, int)> calc = [&](int i, int n) {
		if (data[i].count(n) > 0)
			return;
		if (i == I - 1) {
			if (n >= ns[i])
				data[i][n] = vs[i];
			else
				data[i][n] = 0;
		}
		else {
			if (n >= ns[i]) {
				calc(i + 1, n);
				calc(i + 1, n - ns[i]);
				data[i][n] = max(data[i + 1][n], vs[i] + data[i + 1][n - ns[i]]);
			}
			else {
				calc(i + 1, n);
				data[i][n] = data[i + 1][n];
			}
		}
	};

	cin >> I >> N;
	ns.resize(I);
	vs.resize(I);
	data.resize(I);
	for (int i = 0; i < I; i++) {
		cin >> ns[i] >> vs[i];
	}
	calc(0, N);
	cout << data[0][N];
}

void p1040() {
	int T;
	cin >> T;

	struct Vector {
		int x;
		int y;

		Vector(int x_, int y_): x(x_), y(y_) {}
		Vector(const Vector& v): x(v.x), y(v.y) {}
		inline bool zero() const {
			return x == 0 && y == 0;
		}
		inline bool parallel(const Vector& v) const {
			return x * v.y == y * v.x;
		}
		inline bool perpendicular(const Vector& v) const {
			return x * v.x + y * v.y == 0;
		}
	};

	struct Line {
		int x1;
		int y1;
		int x2;
		int y2;

		Line() { cin >> x1 >> y1 >> x2 >> y2; }
		Line(int x1_, int y1_, int x2_, int y2_): x1(x1_), y1(y1_), x2(x2_), y2(y2_) {}
		Vector vector() const {
			return Vector(x2 - x1, y2 - y1);
		}
		inline bool parallel(const Line& l) const {
			return vector().parallel(l.vector());
		}
		inline bool rect(const Line& l) const {
			Vector v1(vector());
			Vector v2(l.vector());
			Vector v3(l.x1 - x1, l.y1 - y1);
			Vector v4(l.x2 - x2, l.y2 - y2);
			Vector v5(l.x2 - x1, l.y2 - y1);
			Vector v6(l.x1 - x2, l.y1 - y2);
			// parallel
			if (v1.zero() || v2.zero())
				return false;
			if (! v1.parallel(v2))
				return false;
			// not in the same line
			if (v3.zero() || v1.parallel(v3))
				return false;
			// rect
			if (v3.perpendicular(v1) && v4.perpendicular(v1))
				return true;
			if (v5.perpendicular(v1) && v6.perpendicular(v1))
				return true;
			return false;
		}
		inline bool contain(int x, int y) const {
			return (x == x1 && y == y1) || (x == x2 && y == y2);
		}
		inline bool links(const Line& l1, const Line& l2) const {
			if (l1.contain(x1, y1)) {
				return l2.contain(x2, y2);
			}
			else
				return l1.contain(x2, y2) && l2.contain(x1, y1);
		}
		inline bool operator!=(const Line& l) const {
			if (x1 == l.x1 && y1 == l.y1)
				return !(x2 == l.x2 && y2 == l.y2);
			else
				return !((x1 == l.x2 && y1 == l.y2) && (x2 == l.x1 && y2 == l.y1));
		}
	};

	for (int t = 0; t < T; t++) {
		Line l1;
		Line l2;
		Line l3;
		Line l4;

		if (l1.rect(l2)) {
			if (l3.links(l1, l2) && l4.links(l1, l2) && l3.parallel(l4) && l3 != l4)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
			continue;
		}
		if (l1.rect(l3)) {
			if (l2.links(l1, l3) && l4.links(l1, l3) && l2.parallel(l4) && l2 != l4)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
			continue;
		}
		if (l1.rect(l4)) {
			if (l2.links(l1, l4) && l3.links(l1, l4) && l2.parallel(l3) && l2 != l3)
				cout << "YES" << endl;
			else
				cout << "NO" << endl;
			continue;
		}
		cout << "NO" << endl;
	}
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
