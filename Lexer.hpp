
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <unistd.h>
#include "Parser.hpp"

using namespace std;

class Lexer
{
private:
    Lexer() {}
    static Lexer *instance;
    vector<vector<string>>allLinesSplitByWord;
    void splitLineByWord(string line);
public:
    void readTextFile(string path);
    static Lexer *getInstance(); 
    vector<vector<string>>getAllLinesSplitByWord();
};
  
    
    
