#include <unistd.h>
#include <iostream>
#include "Commands.hpp"
#include "Database.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "CalculateExpression.hpp"

using namespace std;

int OpenServerCommand::doCommand(const vector<string> &line, int i)
{
    int port = stoi(line[1]);
    const char *ip = "127.0.0.1";
    Server::getInstance()->Connect(port, ip);
    return i;
}

int ConnectCommand::doCommand(const vector<string> &line, int i)
{
    int port = stoi(line[2]);
    const char *ip = "127.0.0.1";
    Client::getInstance()->Connect(port, ip);
    return i;
}

int VarCommand::doCommand(const vector<string> &line, int i)
{
    Database *db = Database::getInstance();
    if (line.size() > 3)
    {
        if (line[3] == "bind" && line[2] == "=" && line.size() > 4)
        {

            string varPath = line[4];
            varPath.pop_back();
            varPath.erase(0, 1);
            db->setVar(line[1], varPath);
            cout << line[1] << "Path: " << varPath << endl;
        }

        else if (line[2] == "=")
        {
            double resultOfExpression = calculateExpression(line, 3);
            db->setSymbolTable(line[1], resultOfExpression);
        }
        else
        {
            cout << "line: " + i << "invalid line" << endl;
        }
    }
    else
    {
        cout << "line: " + i << "invalid line" << endl;
    }
    return i;
}

int PrintCommand::doCommand(const vector<string> &line, int i)
{
    if (line[1][0] == '"')
    {

        cout << line[1] << endl;
    }
    else
    {
        string ExpressionToPrint;
        for (int i = 1; i < line.size(); i++)
        {
            ExpressionToPrint += line[i];
        }
        double resultOfExpression = calculateExpression(line, 1);
        cout << ExpressionToPrint << " = " << resultOfExpression << endl;
    }
    return i;
}

int SetCommand::doCommand(const vector<string> &line, int i)
{
    if (line.size() > 2)
    {
        Database *db = Database::getInstance();
        double resultOfExpression = calculateExpression(line, 2);
        if (db->containsSymbol(line[0]))
        {
            db->setSymbolTable(line[0], resultOfExpression);
        }
        else
        {
            string set = "set " + db->getVar(line[0]) + " " +
                         to_string(resultOfExpression) + "\r\n";
            char *setChar = &set[0];
            Client::getInstance()->Send(setChar);
        }
    }
    else
    {
        cout << "line: " + i << "invalid line" << endl;
    }
    return i;
}

int SleepCommand::doCommand(const vector<string> &line, int i)
{
    cout << "Waiting " << line[1] << " Milliseconds" << endl;
    int sleepValue = stoi(line[1]);
    sleep(sleepValue / 1000);
    return i;
}

int UnknownCommand::doCommand(const vector<string> &line, int i)
{
    cout << "Unknown Command: " << line[0] << endl;
    return i;
}
