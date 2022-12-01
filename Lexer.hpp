#include <vector>
#include <string>

class Lexer
{
private:
    Lexer() {}
    static Lexer *instance;
    std::vector<std::vector<std::string>> allLinesSplitByWord;
    std::vector<std::string> splitLineByWord(std::string &line);

public:
    void readTextFile(const std::string &path);
    static Lexer *getInstance();
    std::vector<std::vector<std::string>> getAllLinesSplitByWord();
};
