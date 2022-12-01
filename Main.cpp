#include "Lexer.hpp"
#include "Parser.hpp"

int main()
{
    auto lexer = Lexer::getInstance();
    lexer->readTextFile("flightGear.txt");
    auto parser = Parser::getInstance();
    parser->ran();
}
