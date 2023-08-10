#include <boost/process.hpp>

#include "utility.h"

using namespace std;
namespace bp = boost::process;

// List files in current directory
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
