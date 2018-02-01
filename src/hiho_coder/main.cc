
#include <unordered_map>
#include <string>
#include <functional>

#include "hiho_coder.h"


#define DEFINE_FUN(fun_name) g_funs[#fun_name] = fun_name;

std::unordered_map<std::string, std::function<void()>> g_funs;

int main(int argc, char** argv) {
    // add 2 integers
    DEFINE_FUN(p1000)
    // the longest palindrome sub string
    DEFINE_FUN(p1032)

    if (argc > 1) {
        g_funs[argv[1]]();
        return 0;
    }
    return -1;
}