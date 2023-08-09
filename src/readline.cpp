#include "readline.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <boost/process.hpp>

using namespace std;
namespace bp = boost::process;

char **character_name_completion(const char *, int, int);
char *character_name_generator(const char *, int);

string lsh_readline()
{
    rl_attempted_completion_function = character_name_completion;
    string line_read = readline(prompt.c_str());
    if (!line_read.empty())
        add_history(line_read.c_str());
    return line_read;
}

char **character_name_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, character_name_generator);
}

vector<string> list_cur_dir()
{
    bp::ipstream is;
    bp::child c("ls", bp::std_out > is);
    vector<string> out;
    string tmp;
    while (is >> tmp)
        out.push_back(tmp);
    return out;
}

char *character_name_generator(const char *text, int state)
{
    static size_t list_index, len;
    static vector<string> ls;
    const char *name;

    if (!state)
    {
        list_index = 0;
        len = strlen(text);
        ls = list_cur_dir();
    }

    while (list_index < ls.size())
    {
        name = ls[list_index++].c_str();
        if (strncmp(name, text, len) == 0)
            return strdup(name);
    }

    return nullptr;
}
