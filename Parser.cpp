#include "Parser.hpp"

Parser *Parser::instance = 0;
Parser *Parser::getInstance()
{
    if (!instance)
        instance = new Parser;
    return instance;
}

int Parser::parsing(const vector<string> &line, int i)
{
    Database *db = Database::getInstance();
    string command;
    if (db->getCommandMap().count(line[0]))
    {
        command = line[0];
    }
    else if ((db->getVarTable().count(line[0]) && line[1] == "=") ||
             db->getSymbolTable().count(line[0]) && line[1] == "=")
    {
        command = line[1];
    }
    else
    {
        command = "unknownCommand";
    }
    db->getCommandMap()[command]->doCommand(line, i);
    return db->getCommandMap()[command]->get_i(i);
}