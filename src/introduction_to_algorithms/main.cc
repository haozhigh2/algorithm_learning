#include <unordered_map>
#include <string>
#include <functional>
#include <iostream>
using namespace std;

#include "introduction_to_algorithms.h"

#define DEFINE_FUN(fun_name) g_funs[#fun_name] = fun_name;

unordered_map<string, function<void()>> g_funs;

int main(int argc, char** argv) {

    // sort
    DEFINE_FUN(c2_s1_insertion_sort)
    DEFINE_FUN(c2_s3_merge_sort)
    DEFINE_FUN(c6_s4_heap_sort)

    DEFINE_FUN(p2_4_inversions)
    DEFINE_FUN(e4_1_maximum_subarray)

	if (argc == 1) {
		cout << "##  Matched Functions:" << endl;
		for (auto& it : g_funs)
			cout << "    " << it.first << endl;
		return 0;
	}

	string fun_name = argv[1];

	// try to find a complete match
	for (auto& it : g_funs)
		if (fun_name == it.first) {
			cout << "##  Running: " << fun_name << endl;
			g_funs[it.first]();
			return 0;
		}

	// find partial matches
	// find partial matches
	unsigned num_partial_matches = 0;
	string match_name;
	for (auto& it : g_funs)
		if (it.first.find(fun_name) != string::npos) {
			num_partial_matches += 1;
			match_name = it.first;
		}

	if (num_partial_matches == 1) {
		cout << "##  Running: " << match_name << endl;
		g_funs[match_name]();
		return 0;
	}
	else {
		cout << "##  Matched Functions:" << endl;
		for (auto& it : g_funs)
			if (it.first.find(fun_name) != string::npos)
				cout << "    " << it.first << endl;
	}

    return 0;
}
