
import sys
import os
import subprocess

def get_case():
    assert len(sys.argv) > 1, "Need an extra argument to specify case"

    case = sys.argv[1]
    cases = [x[:-3] for x in os.listdir("src") if x.endswith(".cc")]
    match = [x for x in cases if x.find(case) >= 0]

    if len(match) == 0:
        print("case '{}' not found".format(case))
        return None
    elif len(match) > 1:
        print("multi cases found matching '{}'".format(case))
        for m in match:
            print("    {}".format(m))
        return None
    else:
        return match[0]

def compile(case):
    if not os.path.exists("build"):
        os.mkdir("build")
    assert os.path.isdir("build")
    os.chdir("build")

    cc_file = "../src/{}.cc".format(case)
    bin_file = "{}.exe".format(case)

    ## check modified time of source file and bin file
    if os.path.exists(bin_file) and os.path.getmtime(bin_file) >= os.path.getmtime(cc_file):
        print("build/{} is up-to-data, no need to rebuild".format(bin_file))
    else:
        CXX = r"C:/Program Files/LLVM/bin/clang++.exe"
        cmd = '"{}" -std=c++14 "{}" -o "{}"'.format(CXX, cc_file, bin_file)
        print(cmd)
        subprocess.call(cmd, shell = True)

    os.chdir("..")

def run(case):
    if not os.path.exists("test"):
        os.mkdir("test")
    assert os.path.isdir("test")
    os.chdir("test")

    bin_file = "../build/{}.exe".format(case)
    subprocess.call('"{}"'.format(bin_file))

    os.chdir("..")

def main():
    case = get_case()
    if case == None:
        return

    compile(case)
    run(case)

if __name__ == "__main__":
    assert sys.version_info.major >= 3, "This script only runs in Python3"
    main()