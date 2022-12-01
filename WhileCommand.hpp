#include <vector>
#include <string>
#include "ABCCommands.hpp"

class WhileCommand : public Command
{

public:
    int doCommand(const std::vector<std::string> &line, int i);
    int numberLineOfElementInTextFile(const std::vector<std::vector<std::string>> &allLinesSplitByWord, std::string element, int i);
    bool checkCondition(double x, std::string op, std::string yString);
};