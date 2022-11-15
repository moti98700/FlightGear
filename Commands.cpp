#include "Lexer.hpp"
#include "ShuntingYard.cpp"
#include <unordered_map>

using namespace std;
double Command::getVarValue(string var)
{
    string varPath = Database::getInstance()->getVarTable()[var];
    double varValue = Database::getInstance()->getSymbolTable()[varPath];
    return varValue;
}

void Command::mathematicalExpression(const vector<string> &line, int start, string &mathematicalExpres)
{
    Database *db = Database::getInstance();
    for (int j = start; j < line.size(); j++)
    {

        if (db->getSymbolTable().count(line[j]))
        {
            mathematicalExpres += to_string((db->getSymbolTable()[line[j]]));
        }
        else if (db->getVarTable().count(line[j]))
        {
            mathematicalExpres += to_string(getVarValue(line[j]));
        }
        else
        {
            mathematicalExpres += line[j];
        }
    }
}

void openServerCommand::doCommand(const vector<string> &line, int i)
{
    int port = stoi(line[1]);
    const char *ip = "127.0.0.1";
    Server::getInstance()->Connect(port, ip);
}

void connectCommand::doCommand(const vector<string> &line, int i)
{
    int port = stoi(line[2]);
    const char *ip = "127.0.0.1";
    Client::getInstance()->Connect(port, ip);
}

void varCommand::doCommand(const vector<string> &line, int i)
{
    if (line.size() > 3)
    {
        if (line[3] == "bind" && line[2] == "=" && line.size() > 4)
        {

            string varPath = line[4];
            varPath.pop_back();
            varPath.erase(0, 1);
            Database::getInstance()->setVarTable(line[1], varPath);
            cout << line[1] << "Path: " << varPath << endl;
        }

        else if (line[2] == "=")
        {
            string mathematicalExpres;
            mathematicalExpression(line, 3, mathematicalExpres);
            Calculator c;
            double resultOfMathematicalExpressio = c.calculate(mathematicalExpres);
            Database::getInstance()->setSymbolTable(line[1], resultOfMathematicalExpressio);
        }
        else
        {
            cout << "line: " + i << "invalid line" << endl;
        }
    }
    else
    {
        cout << "line: " + i << "invalid line" << endl;
    }
}

int whileCommand::sizeLoop;

void whileCommand::doCommand(const vector<string> &line, int i)
{
    int loopEnd;
    loopEnd = numberLineOfElementInTextFile(Lexer::getInstance()->getAllLinesSplitByWord(), "}", i);
    vector<vector<string>> lineWhile;
    for (int j = i + 1; j < loopEnd; j++)
    {
        lineWhile.push_back(Lexer::getInstance()->getAllLinesSplitByWord()[j]);
    }
    sizeLoop = lineWhile.size();

    while (checkCondition(getVarValue(line[1]), line[2], line[3]))
    {
        for (int j = 0; j < lineWhile.size(); j++)
        {
            Parser::getInstance()->parsing(lineWhile[j], i);
        }
    }
}

int whileCommand::numberLineOfElementInTextFile(const vector<vector<string>> &allLinesSplitByWord, string element, int i)
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

bool whileCommand::checkCondition(double x, string op, string yString)
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

void printCommand::doCommand(const vector<string> &line, int i)
{
    if (line[1][0] == '"')
    {

        cout << line[1] << endl;
    }
    else
    {
        string ExpressionToPrint;
        for (int i = 1; i < line.size(); i++)
        {
            ExpressionToPrint += line[i];
        }
        string mathematicalExpres;
        mathematicalExpression(line, 1, mathematicalExpres);
        Calculator c;
        double resultOfMathematicalExpressio = c.calculate(mathematicalExpres);
        cout << ExpressionToPrint << " = " << resultOfMathematicalExpressio << endl;
    }
}

void setCommand::doCommand(const vector<string> &line, int i)
{
    if (line.size() > 2)
    {
        Database *db = Database::getInstance();
        string mathematicalExpres;
        mathematicalExpression(line, 2, mathematicalExpres);
        Calculator c;
        double resultOfMathematicalExpressio = c.calculate(mathematicalExpres);
        if (db->getSymbolTable().count(line[0]))
        {
            db->setSymbolTable(line[0], resultOfMathematicalExpressio);
        }
        else
        {
            string set = "set " + db->getVarTable()[line[0]] + " " +
                         to_string(resultOfMathematicalExpressio) + "\r\n";
            char *setChar = &set[0];
            Client::getInstance()->Send(setChar);
        }
    }
    else
    {
        cout << "line: " + i << "invalid line" << endl;
    }
}

void sleepCommand::doCommand(const vector<string> &line, int i)
{
    cout << "Waiting " << line[1] << " Milliseconds" << endl;
    int sleepValue = stoi(line[1]);
    sleep(sleepValue / 1000);
}

void unknownCommand::doCommand(const vector<string> &line, int i)
{
    cout << "Unknown Command: " << line[0] << endl;
}