#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <termios.h>
#include <boost/process.hpp>
#include <readline/history.h>

#include "common.h"
#include "readline.h"

using namespace std;
namespace bp = boost::process;
namespace bf = boost::filesystem;

// Extrack tokens from input string.
vector<string> parse_cmd(const string &line)
{
    vector<string> toks;
    stringstream sstream(line);
    string cur_tok;
    while (sstream >> cur_tok)
        toks.push_back(cur_tok);
    return toks;
}

// Launch a sub process.
int jsh_launch(const string &path, const vector<string> &args)
{
    bf::path p = bp::search_path(path);
    bp::child c(p, args);
    c.wait();
    return 0;
}

int jsh_execute(const vector<string> &cmd)
{
    if (cmd.empty())
        return 0;
    else if (auto [status, builtin] = exec_if_builtin(cmd); builtin)
        return status;
    else
        return jsh_launch(cmd[0], vector<string>(cmd.begin() + 1, cmd.end()));
}

int jsh_loop()
{
    string line;
    while (true)
    {
        line = lsh_readline();
        vector<string> cmd = parse_cmd(line);
        while (!cmd.empty() && cmd.back() == "\\")
        {
            cmd.pop_back();
            line = lsh_readline();
            vector<string> next = parse_cmd(line);
            cmd.insert(cmd.end(), next.begin(), next.end());
        }
        int status = jsh_execute(cmd);
        if (status == JSH_EXIT)
            break;
    }
    return 0;
}

int main()
{
    using_history();
    // TODO: read config file
    jsh_loop();
    return EXIT_SUCCESS;
}