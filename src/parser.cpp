#include <sstream>
#include <regex>
#include <boost/algorithm/string/replace.hpp>
#include <iostream>

#include "parser.h"
#include "utility.h"

using namespace std;

static char single_wildcards[] = {'*', '?', '#'};

// Return true if given string is a pattern string.
bool contains_wildcards(string str)
{
    // Detect *, ?, #
    for (auto ch : str)
        for (auto w : single_wildcards)
            if (ch == w)
                return true;
    // Detect []
    bool detected = false;
    for (auto ch : str)
    {
        if (ch == '[')
        {
            if (detected) // illegal
                return false;
            detected = true;
        }
        else if (ch == ']' && detected)
            return true;
    }
    return false;
}

// Parse tokens from input string, support wildcards.
vector<string> parse_cmd(const string &line)
{
    vector<string> toks;
    stringstream sstream(line);
    string cur_tok;
    while (sstream >> cur_tok)
    {
        if (!contains_wildcards(cur_tok))
            toks.push_back(cur_tok);
        else
        {
            boost::replace_all(cur_tok, "?", ".");
            boost::replace_all(cur_tok, "*", ".*");
            const regex e(cur_tok);
            vector<string> file_list = list_cur_dir();
            for (auto filename : file_list)
                if (regex_match(filename, e))
                    toks.push_back(filename);
        }
    }
    return toks;
}