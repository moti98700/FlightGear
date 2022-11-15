#include <unordered_map>
#include "Database.hpp"

using namespace std;

class Parser
{
private:
    Parser() {Database::getInstance();}
    static Parser *instance;
public:
    int parsing(const vector<string>&line,int i);
    static Parser *getInstance(); 
}; 