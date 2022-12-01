#include <vector>
#include <string>

class Parser
{
private:
    Parser();
    static Parser *instance;

public:
    void ran();
    int parsing(const std::vector<std::string> &line, int i);
    static Parser *getInstance();
};
