#include "Commands.hpp"
#include <unordered_map>

using namespace std;

class Database
{
private:
    Database() {buildCommandMap();}
    static Database *instance;
    unordered_map<string, Command *> CommandMap;
    unordered_map<string, double> SymbolTable;
    unordered_map<string, string> VarTable;
    void buildCommandMap();

public:
    void setSymbolTable(string,double);
    void setVarTable(string varName,string varPath);
    unordered_map<string, Command *> getCommandMap(){return CommandMap;}
    unordered_map<string, double> getSymbolTable(){return SymbolTable;}
    unordered_map<string, string> getVarTable(){return VarTable;}
    static Database *getInstance();
};