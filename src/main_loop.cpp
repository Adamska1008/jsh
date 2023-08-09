#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unistd.h>
#include <termios.h>
#include <boost/process.hpp>
#include <readline/readline.h>
#include <readline/history.h>

#include "common.h"

using namespace std;
namespace bp = boost::process;
namespace bf = boost::filesystem;

static string prompt = DEFAULT_PROMPT;

string lsh_readline()
{
    string line_read = readline(prompt.c_str());
    if (!line_read.empty())
        add_history(line_read.c_str());
    return line_read;
}

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
        auto cmd = parse_cmd(line);
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