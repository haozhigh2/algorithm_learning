
#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>
using namespace std;

#include "../../include/hiho_coder.h"


#define DEFINE_FUN(fun_name) g_funs[#fun_name] = fun_name;

unordered_map<string, function<void()>> g_funs;

int main(int argc, char** argv) {
    DEFINE_FUN(p1000)
    DEFINE_FUN(p1014)
	DEFINE_FUN(p1015)
    DEFINE_FUN(p1032)
	DEFINE_FUN(p1038)
	DEFINE_FUN(p1040)
	DEFINE_FUN(p1043)
    DEFINE_FUN(p1049)
    DEFINE_FUN(p1374)

	DEFINE_FUN(hiho168)
	DEFINE_FUN(hiho169)

    if (argc > 1) {
        g_funs[argv[1]]();
        return 0;
    }
	else {
		cout << "Supported functions:" << endl;
		unordered_map<string, function<void()>>::iterator it;
		for (it = g_funs.begin(); it != g_funs.end(); it++) {
			cout << "    " << it->first << endl;
		}
	}
    return -1;
}
