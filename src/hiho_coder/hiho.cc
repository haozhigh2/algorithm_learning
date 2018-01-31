
#include <string>
#include <list>
#include <iostream>
using namespace std;

/*
** hiho 166
*/
int hiho166_fun(unsigned n) {
    if (n == 0)
        return 1;
    int num0 = 0;
    while ((n & 1) == 0) {
        num0++;
        n >>= 1;
    }
    int num1 = 0;
    while ((n & 1) == 1) {
        num1++;
        n >>= 1;
    }
    return (num0 * num1 + 1 - num0) * hiho166_fun(n) + num0 * hiho166_fun(n << 1);
}

extern "C" __declspec(dllexport) int hiho166(int argc, char** argv) {
    unsigned n;
    cin >> n;
    while ((n & 1) == 1)
        n >>= 1;
    cout << hiho166_fun(n);
    return 0;
}

/*
** hiho 169
*/
struct Hiho169Node {
    char op;
    int digit;
    Hiho169Node(char op_)
        : op(op_), digit(0)
    {
    }
    Hiho169Node(int digit_)
        : op('0'), digit(digit_)
    {
    }
    Hiho169Node(const Hiho169Node& rhs)
        : op(rhs.op), digit(rhs.digit)
    {
    }
    void Set(int digit_) {
        op = '0';
        digit = digit_;
    }
};

int hiho169_fun(list<Hiho169Node> l) {
    list<Hiho169Node>::iterator it = l.begin();
    for (; it != l.end(); it++) {
        if (it->op == '*' || it->op == '/') {
            it--;
            int n = it->digit;
            it = l.erase(it);
            char op = it->op;
            it = l.erase(it);
            if (op == '*')
                it->digit = n * it->digit;
            else
                it->digit = n / it->digit;
        }
    }
    it = l.begin();
    for (; it != l.end(); it++) {
        if (it->op == '+' || it->op == '-') {
            it--;
            int n = it->digit;
            it = l.erase(it);
            char op = it->op;
            it = l.erase(it);
            if (op == '+')
                it->digit = n + it->digit;
            else
                it->digit = n - it->digit;
        }
    }
    return l.begin()->digit;
}

extern "C" __declspec(dllexport) int hiho169(int argc, char** argv) {
    string s;
    cin >> s;
    list<Hiho169Node> l;

    unsigned i = 0;
    while (i < s.size()) {
        if (s[i] >= '0' && s[i] <= '9') {
            int n = 0;
            while (i < s.size() && s[i] >= '0' && s[i] <= '9') {
                n = n * 10 + (s[i] - '0');
                i += 1;
            }
            l.push_back(Hiho169Node(n));
            continue;
        }
        if (s[i] == ')') {
            list<Hiho169Node> l_tmp;
            while (l.back().op != '(') {
                l_tmp.push_front(l.back());
                l.pop_back();
            }
            l.pop_back();
            l.push_back(Hiho169Node(hiho169_fun(l_tmp)));
        }
        else {
            l.push_back(Hiho169Node(s[i]));
        }
        i += 1;
    }
    cout << hiho169_fun(l);
    return 0;
}