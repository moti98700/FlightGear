#include "Database.hpp"
#include "WhileCommand.hpp"
#include "Commands.hpp"

using namespace std;
Database *Database::instance = 0;

Database *Database::getInstance()
{
    if (!instance)
    {
        instance = new Database();
    }
    return instance;
}
Database::Database()
{
    buildCommandMap();
}

void Database::setSymbolTable(string const &path, double value)
{
    this->SymbolTable[path] = value;
}

void Database::setVar(string const &varName, string varPath)
{
    this->VarTable[varName] = varPath;
}

double Database::getSymbole(string const &puth)
{
    return SymbolTable[puth];
}

string Database::getVar(string const &var)
{
    return VarTable[var];
}

double Database::getVarValue(const std::string &var)
{
    return SymbolTable[getVar(var)];
}

Command *Database::getCommand(const std::string &command)
{
    return CommandMap[command];
}

bool Database::containsMap(string const &command)
{
    if (CommandMap.count(command))
    {
        return true;
    }
    return false;
}

bool Database::containsVar(string const &command)
{
    if (VarTable.count(command))
    {
        return true;
    }
    return false;
}

bool Database::containsSymbol(string const &command)
{
    if (SymbolTable.count(command))
    {
        return true;
    }
    return false;
}

void Database::buildCommandMap()
{
    CommandMap["openDataServer"] = new OpenServerCommand();
    CommandMap["connect"] = new ConnectCommand();
    CommandMap["var"] = new VarCommand();
    CommandMap["="] = new SetCommand();
    CommandMap["while"] = new WhileCommand();
    CommandMap["print"] = new PrintCommand();
    CommandMap["sleep"] = new SleepCommand();
    CommandMap["unknownCommand"] = new UnknownCommand();
}
