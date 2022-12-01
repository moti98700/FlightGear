#include "WhileCommand.hpp"
#include "Database.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace std;

int WhileCommand::doCommand(const vector<string> &line, int i)
{
    auto db = Database::getInstance();
    auto lexer = Lexer::getInstance();
    int loopEnd;
    loopEnd = numberLineOfElementInTextFile(lexer->getAllLinesSplitByWord(), "}", i);
    vector<vector<string>> lineWhile;
    for (int j = i + 1; j < loopEnd; j++)
    {
        lineWhile.push_back(lexer->getAllLinesSplitByWord()[j]);
    }

    auto ws = lineWhile.size();

    while (checkCondition(db->getVarValue(line[1]), line[2], line[3]))
    {
        for (int j = 0; j < ws; j++)
        {
            Parser::getInstance()->parsing(lineWhile[j], i);
        }
    }

    return i + ws;
}

int WhileCommand::numberLineOfElementInTextFile(const vector<vector<string>> &allLinesSplitByWord, string element, int i)
{
    for (int j = i + 1; j < allLinesSplitByWord.size(); j++)
    {
        if (allLinesSplitByWord[j][0] == element)
        {
            return j;
        }
    }
    return 0;
}

bool WhileCommand::checkCondition(double x, string op, string yString)
{
    double y = stod(yString);
    if ((op == "==") && (x == y))
        return true;
    else if ((op == "!=") && (x != y))
        return true;
    else if ((op == "<") && (x < y))
        return true;
    else if ((op == ">") && (x > y))
        return true;
    else if ((op == "<=") && (x <= y))
        return true;
    else if ((op == ">=") && (x >= y))
        return true;
    else
        return false;
}