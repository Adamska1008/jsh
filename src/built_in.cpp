#include <unordered_map>
#include <unistd.h>
#include <sstream>
#include <iostream>

#include "built_in.h"
#include "common.h"

using namespace std;

string BuiltIn::help_msg()
{
    stringstream sstream;
    sstream << this->name << "\t";
    for (const auto &arg : this->args)
        sstream << arg << " ";
    sstream << '\t';
    sstream << this->intro;
    return sstream.str();
}

inline int jsh_exit(vector<string> args)
{
    return JSH_EXIT;
}

int jsh_cd(vector<string> args)
{
    string dir;
    if (args.size() == 1)
        dir = JSH_HOME;
    else
        dir = args[1];
    return chdir(dir.c_str());
}

int jsh_help(vector<string>);

static const unordered_map<string, BuiltIn> built_in = {
    {"cd", BuiltIn{"cd", "change directory", {"[dir]"}, jsh_cd}},
    {"exit", BuiltIn{"exit", "exit jsh", {}, jsh_exit}},
    {"help", BuiltIn{"help", "show help information", {}, jsh_help}},
};

int jsh_help(vector<string> args)
{
    for (auto [k, b] : built_in)
        cout << b.help_msg() << endl;
    return 0;
}

tuple<int, bool> exec_if_builtin(vector<string> args)
{
    for (auto [k, b] : built_in)
        if (args[0] == k)
            return {b.f(args), true};
    return {0, false};
}
