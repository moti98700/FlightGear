#include "CalculateExpression.hpp"
#include "Database.hpp"
#include "ShuntingYard.cpp"
using namespace std;

double CalculateExpression::calculateExpression(const vector<string> &line, int start)
{
    string mathematicalExpres;
    Database *db = Database::getInstance();
    for (int j = start; j < line.size(); j++)
    {
        if (db->containsSymbol(line[j]))
        {
            mathematicalExpres += to_string(db->getSymbole(line[j]));
        }
        else if (db->containsVar(line[j]))
        {
            mathematicalExpres += to_string(db->getVarValue(line[j]));
        }
        else
        {
            mathematicalExpres += line[j];
        }
    }
    Calculator c;
    return c.calculate(mathematicalExpres);
}