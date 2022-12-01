#pragma once
#include <vector>
#include <string>

class Command
{
public:
    virtual ~Command() = default;
    virtual int doCommand(const std::vector<std::string> &line, int i) = 0;
};
