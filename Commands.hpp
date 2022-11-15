#include <vector>
#include <iostream>
#include "Server.hpp"
#include "Client.hpp"

using namespace std;


class Command
{
public:
    virtual void doCommand(const vector<string> &line, int i) = 0;
    double getVarValue(string var);
    virtual int get_i(int i){return i;}
    void mathematicalExpression(const vector<string> &line,int size,string &mathematicalExpres);

};

class openServerCommand : public Command
{
public:
    void doCommand(const vector<string> &line, int i);
};

class connectCommand : public Command
{
public:
    void doCommand(const vector<string> &line, int i);
};

class varCommand : public Command
{
public:
    void doCommand(const vector<string> &line, int i);
    bool checkIfPathIsValid(string varPath);
};

class setCommand : public Command
{
public:
    void doCommand(const vector<string> &line, int i);
};
   
class printCommand : public Command
{
public:
    void doCommand(const vector<string> &line, int i);
};

class whileCommand : public Command
{

public:
    void doCommand(const vector<string> &line, int i);
    int numberLineOfElementInTextFile(const vector<vector<string>>&allLinesSplitByWord,string element,int i);
    bool checkCondition(double x, string op, string yString);
    static int sizeLoop ;
    int get_i(int i){return i + 1 + sizeLoop;}
};   

class sleepCommand : public Command
{
public:
    void doCommand(const vector<string> &line, int i);
};

class unknownCommand : public Command
{
public:
    void doCommand(const vector<string> &line, int i);
};