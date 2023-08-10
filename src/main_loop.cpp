#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <boost/process.hpp>
#include <readline/history.h>

#include "common.h"
#include "readline.h"
#include "parser.h"

using namespace std;
namespace bp = boost::process;
namespace bf = boost::filesystem;



// Launch a sub process.
int jsh_launch(const string &path, const vector<string> &args)
{
    bf::path p = bp::search_path(path);
    bp::child c(p, args);
    c.wait();
    return 0;
}

// Execute commands, support only single command currently
// Commands can be: 
// + Builtins
// + Programs
int jsh_execute(const vector<string> &cmd)
{
    if (cmd.empty())
        return 0;
    else if (auto [status, builtin] = exec_if_builtin(cmd); builtin)
        return status;
    else
        return jsh_launch(cmd[0], vector<string>(cmd.begin() + 1, cmd.end()));
}

// Basic loop in jsh
int jsh_loop()
{
    string line;
    while (true)
    {
        line = jsh_readline();
        vector<string> cmd = parse_cmd(line);
        while (!cmd.empty() && cmd.back() == "\\")
        {
            cmd.pop_back();
            line = jsh_readline();
            vector<string> next = parse_cmd(line);
            cmd.reserve(cmd.size() + next.size());
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