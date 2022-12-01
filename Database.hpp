#include "ABCCommands.hpp"
#include <string>
#include <unordered_map>

class Database
{
private:
    Database(); 
    static Database *instance;
    std::unordered_map<std::string, Command *> CommandMap;
    std::unordered_map<std::string, double> SymbolTable;
    std::unordered_map<std::string, std::string> VarTable;
    void buildCommandMap();

public:
    void setSymbolTable(std::string const &, double);
    void setVar(std::string const &varName, std::string varPath);
    std::string getVar(std::string const &);
    double getSymbole(std::string const &);
    Command *getCommand(std::string const &);
    double getVarValue(std::string const &);
    bool containsSymbol(std::string const &);
    bool containsMap(std::string const &);
    bool containsVar(std::string const &);
    static Database *getInstance();
};
