#include "Lexer.hpp"

int main()
{
    Lexer::getInstance()->readTextFile("flightGear.txt");
    for (int i = 0; i <  Lexer::getInstance()->getAllLinesSplitByWord().size(); i++)
    {
        i = Parser::getInstance()->parsing(Lexer::getInstance()->getAllLinesSplitByWord()[i], i);
    }
}






// g++ Database.cpp Commands.cpp Client.cpp Lexer.cpp  Parser.cpp ShuntingYard.cpp Server.cpp Main.cpp -pthread 