
#include <unordered_map>
#include <string>
#include <functional>

#include "hiho_coder.h"


#define DEFINE_FUN(fun_name) g_funs[#fun_name] = fun_name;

std::unordered_map<std::string, std::function<void()>> g_funs;

int main(int argc, char** argv) {
    DEFINE_FUN(p1000)
    DEFINE_FUN(p1032)
    DEFINE_FUN(p1049)
    DEFINE_FUN(p1374)

    if (argc > 1) {
        g_funs[argv[1]]();
        return 0;
    }
    return -1;
}