#include "Database.hpp"
Database *Database::instance = 0;

Database *Database::getInstance()
{
	if(!instance) {
        instance = new Database();
    }
	return instance;
}

void Database::setSymbolTable(string path,double value)
{
    this->SymbolTable[path] = value;
}
void Database::setVarTable(string varName,string varPath)
{
    this->VarTable[varName] = varPath;
}

void Database::buildCommandMap()
{
    CommandMap["openDataServer"] = new openServerCommand();
    CommandMap["connect"] = new connectCommand();
    CommandMap["var"] = new varCommand();
    CommandMap["="] = new setCommand();
    CommandMap["while"] = new whileCommand();
    CommandMap["print"] = new printCommand();
    CommandMap["sleep"] = new sleepCommand();
    CommandMap["unknownCommand"] = new unknownCommand();
}