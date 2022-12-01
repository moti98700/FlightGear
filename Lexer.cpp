#include "Lexer.hpp"
#include <fstream>

using namespace std;

Lexer *Lexer::instance = 0;
Lexer *Lexer::getInstance()
{
    if (!instance)
        instance = new Lexer;
    return instance;
}
vector<vector<string>> Lexer::getAllLinesSplitByWord()
{
    return allLinesSplitByWord;
}

void Lexer::readTextFile(const string &path)
{
    vector<string> allLines;
    string line;
    ifstream file;
    file.open(path);
    while (file)
    {
        getline(file, line);
        allLines.push_back(line);
    }
    for (int i = 0; i < allLines.size(); i++)
    {

        vector<string> linvect = splitLineByWord(allLines[i]);
        allLinesSplitByWord.push_back(linvect);
    }
}

vector<string> Lexer::splitLineByWord(string &line)
{
    while (line[0] == ' ')
    {
        line.erase(0, 1);
    }
    vector<string> lineSplitByWord;
    string word = "";
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ' ')
        {
            lineSplitByWord.push_back(word);
            word = "";
        }
        else
        {
            word = word + line[i];
        }
    }
    lineSplitByWord.push_back(word);
    return lineSplitByWord;
}
