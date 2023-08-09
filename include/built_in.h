#pragma once
#ifndef BUILT_IN_H
#define BUILT_IN_H
#include <vector>
#include <string>
#include <tuple>
#include <functional>

struct BuiltIn
{
    std::string name;
    std::string intro;
    std::vector<std::string> args;
    std::function<int(std::vector<std::string>)> f;
    std::string help_msg();
};

std::tuple<int, bool> exec_if_builtin(std::vector<std::string>);

#endif