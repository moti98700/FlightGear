#include <vector>
#include <string>
#include "ABCCommands.hpp"
#include "CalculateExpression.hpp"

class OpenServerCommand : public Command
{
public:
    int doCommand(const std::vector<std::string> &line, int i);
};

class ConnectCommand : public Command
{
public:
    int doCommand(const std::vector<std::string> &line, int i);
};

class VarCommand : public Command, public CalculateExpression
{
public:
    int doCommand(const std::vector<std::string> &line, int i);
};

class SetCommand : public Command, public CalculateExpression
{
public:
    int doCommand(const std::vector<std::string> &line, int i);
};

class PrintCommand : public Command, public CalculateExpression
{
public:
    int doCommand(const std::vector<std::string> &line, int i);
};
class SleepCommand : public Command
{
public:
    int doCommand(const std::vector<std::string> &line, int i);
};

class UnknownCommand : public Command
{
public:
    int doCommand(const std::vector<std::string> &line, int i);
};
