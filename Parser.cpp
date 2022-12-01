#include "Parser.hpp"
#include "Lexer.hpp"
#include "Database.hpp"

using namespace std;

Parser::Parser()
{
    Database::getInstance();
    
}

Parser *Parser::instance = 0;
Parser *Parser::getInstance()
{
    if (!instance)
        instance = new Parser();
    return instance;
}

void Parser::ran()
{
    auto lexer = Lexer::getInstance();
    for (int i = 0; i < lexer->getAllLinesSplitByWord().size(); i++)
    {
        i = parsing(lexer->getAllLinesSplitByWord()[i], i);
    }
}

int Parser::parsing(const vector<string> &line, int i)
{
    Database *db = Database::getInstance();
    string command;
    if (db->containsMap(line[0]))
    {
        command = line[0];
    }
    else if ((db->containsVar(line[0]) && line[1] == "=") ||
             db->containsSymbol(line[0]) && line[1] == "=")
    {
        command = line[1];
    }
    else
    {
        command = "unknownCommand";
    }
    auto cmd = db->getCommand(command);
    return cmd->doCommand(line, i);
}
