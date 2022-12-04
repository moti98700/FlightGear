#pragma once
#include <vector>
#include <string>

class Command
{
public:
    virtual int doCommand(const std::vector<std::string> &line, int i) = 0;
    virtual ~Command() = default;
};
