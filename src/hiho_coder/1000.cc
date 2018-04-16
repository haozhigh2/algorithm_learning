#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <map>
#include <list>
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

int p1032_fun(const string& s0) {
	string s;
	s.resize(s0.size() * 2 + 1);

	for (unsigned i = 0; i < s0.size(); i++) {
		s[i * 2] = '#';
		s[i * 2 + 1] = s0[i];
	}
	s[s0.size() * 2] = '#';

	vector<int> r;	// max redius centered at each index
	r.resize(s.size(), 0);
	int m = 0;  // id of the number with the right most wing
	int N = static_cast<int>(s.size());
	for (int i = 1; i < N; i++) {
		if (i >= m + r[m]) {
			while (i - r[i] - 1 >= 0 && i + r[i] + 1 < N && s[i - r[i] - 1] == s[i + r[i] + 1])
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
				while (i - r[i] - 1 >= 0 && i + r[i] + 1 < N && s[i - r[i] - 1] == s[i + r[i] + 1])
					r[i] += 1;
			}
		}

		if (i + r[i] > m + r[m])
			m = i;
	}

	int p = 0;  // id of the number with the biggest radius
	for (int i = 0; i < N; i++)
		p = max(p, r[i]);
	return p;
}

void p1032() {
	int N;
	cin >> N;
	string s;
	for (int i = 0; i < N; i++) {
		cin >> s;
		cout << p1032_fun(s) << endl;
	}
	/*
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
	*/
}

void p1038() {
	int I;	// number of items
	int N;	// total number of needs available
	vector<int> ns;	// need for each item
	vector<int> vs;	// value for each item
	vector<int> data0;
	vector<int> data1;

	cin >> I >> N;
	ns.resize(I);
	vs.resize(I);
	for (int i = 0; i < I; i++) {
		cin >> ns[i] >> vs[i];
	}

	data0.resize(N + 1, 0);
	data1.resize(N + 1, 0);
	for (int i = 0; i < I; i++) {
		for (int n = 0; n <= N; n++) {
			if (n >= ns[i]) {
				data1[n] = max(data0[n], vs[i] + data0[n - ns[i]]);
			}
			else {
				data1[n] = data0[n];
			}
		}
		data0.swap(data1);
	}
	cout << data0[N];
}

void p1039() {
	int N;
	cin >> N;

	auto f = [](string& s0) {
		int len = s0.size();
		string s;
		while (true) {
			s.resize(0);
			s.reserve(s0.size());

			int i = 0;
			while (i < (int)s0.size()) {
				if (i == (int)s0.size() - 1) {
					s.push_back(s0[i++]);
				}
				else if (s0[i + 1] != s0[i]) {
					s.push_back(s0[i++]);
				}
				else {
					int j = i + 1;
					while (j < (int)s0.size() && s0[j] == s0[i])
						j++;
					i = j;
				}
			}

			if (s.size() == s0.size())
				break;
			s.swap(s0);
		}
		return int(len - s.size());
	};

	string s;
	string s0;
	for (int n = 0; n < N; n++) {
		cin >> s0;

		int result = 0;
		for (int i = 0; i <= (int)s0.size(); i++)
			for (int j = 0; j < 3; j++) {
				s.resize(s0.size() + 1);
				int k;
				for (k = 0; k < i; k++)
					s[k] = s0[k];
				s[i] = 'A' + j;
				for (k = i + 1; k <= (int)s0.size(); k++)
					s[k] = s0[k - 1];
				result = max(result, f(s));
			}
		cout << result << endl;
	}
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

void p1041() {
	int T;
	cin >> T;

	struct Node {
		list<int> next;
		int parent;

		Node(): parent(0) {}
	};

	Node nodes[101];		// first element is not used
	int paths[101][100];	// first element is not used
	int path_size[101];		// first element is not used
	bool visited[101];		// first element is not used

	for (int t = 0; t < T; t++) {
		int N;
		cin >> N;

		// init data for each data set
		for (int n = 0; n <= N; n++) {
			nodes[n].next.clear();
			nodes[n].parent = 0;
			path_size[n] = 0;
			visited[n] = false;
		}

		// input graph 
		int a, b;
		for (int n = 1; n < N; n++) {
			cin >> a >> b;
			nodes[a].next.push_back(b);
			nodes[b].next.push_back(a);
		}

		// establish tree
		//function<void(int, int)> fe = [&](int id, int p_id) {
		//	Node& node = nodes[id];
		//	node.parent = p_id;
		//	node.next.remove(p_id);
		//	for (auto it = node.next.begin(); it != node.next.end(); it++)
		//		fe(*it, id);
		//};
		//for (auto it = nodes[1].next.begin(); it != nodes[1].next.end(); it++)
		//	fe(*it, 1);
		deque<int> ids;
		deque<int> p_ids;
		ids.push_back(1);
		p_ids.push_back(0);
		while (ids.size() > 0) {
			int id = ids.front();
			int p_id = p_ids.front();
			ids.pop_front();
			p_ids.pop_front();
			if (p_id != 0) {
				nodes[id].parent = p_id;
				nodes[id].next.remove(p_id);
			}
			cout << "    " << id << " " << p_id << endl;
			for (auto it = nodes[id].next.begin(); it != nodes[id].next.end(); it++) {
				ids.push_back(*it);
				p_ids.push_back(id);
			}
		}

		// establish paths for each element
		for (int n = 1; n <= N; n++) {
			int n_tmp = n;
			while (n_tmp != 0) {
				paths[n][path_size[n]] = n_tmp;
				path_size[n] ++;
				n_tmp = nodes[n_tmp].parent;
			}

			// reverse path
			for (int x = 0; x < path_size[n]; x++) {
				int size_tmp = paths[n][x];
				paths[n][x] = paths[n][path_size[n] - 1 - x];
				paths[n][path_size[n] - 1 - x] = size_tmp;
			}
		}

		// input requested path
		int m;
		cin >> m;

		// visit to first city
		int id;		// city id
		int id_pre;	// previous city id in the requested path
		cin >> id;
		for (int i = 0; i < path_size[id]; i++)
			visited[paths[id][i]] = true;

		//cout << endl;
		//for (int n = 1; n <= N; n++)
		//	cout << visited[n] << ' ';
		//cout << endl;

		// visit city one by one in the requested path
		bool pass = true;
		for (int x = 1; x < m; x++) {
			id_pre = id;
			cin >> id;
			//cout << endl << "    " << id_pre << " " << id << endl;
			if (visited[id]) {
				pass = false;
				break;
			}

			// find last common city on paths of city ms[m] and city ms[m - 1]
			int i = -1;
			while (i + 1 < path_size[id_pre] &&
					i + 1 < path_size[id] &&
					paths[id_pre][i + 1] == paths[id][i + 1])
				i ++;

			// function to visit all cities below a city id
			//function<void(int)> f = [&](int id) {
			//	visited[id] = true;
			//	for (auto it = nodes[id].next.begin(); it != nodes[id].next.end(); it++)
			//		f(*it);
			//};

			// visit path to city id
			for (int i2 = i + 1; i2 < path_size[id]; i2++)
				visited[paths[id][i2]] = true;
			// visit all cities from last common city to id_pre branch
			if (i + 1 < path_size[id_pre]) {
				vector<int> ids;
				ids.push_back(paths[id_pre][i + 1]);
				while (ids.size() > 0) {
					int idd = ids.back();
					ids.pop_back();
					visited[idd] = true;
					for (auto it = nodes[idd].next.begin(); it != nodes[idd].next.end(); it++)
						ids.push_back(*it);
				}
			}
				//f(paths[id_pre][i + 1]);

			//cout << endl;
			//for (int n = 1; n <= N; n++)
			//	cout << visited[n] << ' ';
			//cout << endl;
		}

		if (pass)
			cout << "YES" << endl;
		else
			cout << "NO" << endl;
	}
}

void p1043() {
	int I;	// number of items
	int N;	// total number of needs available
	vector<int> ns;	// need for each item
	vector<int> vs;	// value for each item
	vector<int> data0;
	vector<int> data1;

	cin >> I >> N;
	ns.resize(I);
	vs.resize(I);
	for (int i = 0; i < I; i++) {
		cin >> ns[i] >> vs[i];
	}

	data0.resize(N + 1, 0);
	data1.resize(N + 1, 0);
	for (int i = 0; i < I; i++) {
		for (int n = 0; n <= N; n++) {
			int n_tmp = n;
			int v_tmp = 0;
			data1[n] = data0[n_tmp];
			while (n_tmp >= ns[i]) {
				data1[n] = max(data1[n], v_tmp + vs[i] + data0[n_tmp - ns[i]]);
				n_tmp -= ns[i];
				v_tmp += vs[i];
			}
		}
		data0.swap(data1);
	}
	cout << data0[N];
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
