#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <vector>
#include <thread>
#include "Server.hpp"
#include "Database.hpp"

using namespace std;

Server *Server::instance = 0;
Server *Server::getInstance()
{
	if (!instance)
		instance = new Server;
	return instance;
}

void Server::Connect(int port, const char *ip)
{
	t1 = thread(&Server::launchFG, this);

	cout << "Waiting for the Simulator..." << endl;

	struct sockaddr_in address;
	int addrlen = sizeof(address);

	// Creating socket file descriptor
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	// Forcefully attaching socket to the port PORT
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
	{
		perror("setsockopt");
		exit(EXIT_FAILURE);
	}
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);

	// Forcefully attaching socket to the port PORT
	if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
	if (listen(server_fd, 3) < 0)
	{
		perror("listen");
		exit(EXIT_FAILURE);
	}
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
	{
		perror("accept");
		exit(EXIT_FAILURE);
	}
	t2 = thread(&Server::ListeningToSimulator, this);
}

void Server::launchFG()
{
	system("fgfs --telnet=socket,in,10,127.0.0.1,5402,tcp --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small");
}

void Server::ListeningToSimulator()
{
	int valread = 0;
	char c;
	string buffer;
	while (true)
	{
		bool ok = true;
		buffer.clear();
		c = {0};
		while (c != '\n')
		{
			valread = read(new_socket, &c, 1);
			if (valread < 0)
			{

				ok = !ok;
				break;
			}
			buffer += c;
		}

		if (ok)
		{
			vector<double> values;
			SplitLine(buffer, values);
			for (int i = 0; i < values.size(); i++)
			{
				Database::getInstance()->setSymbolTable(paths[i], values[i]);
			}
		}
	}
}

void Server::SplitLine(string line, vector<double> &values) // split a line into words
{
	string temp = "";
	for (int i = 0; i < line.length(); ++i)
	{
		if (line[i] == ',')
		{
			values.push_back(stod(temp));
			temp = "";
		}
		else
		{
			temp.push_back(line[i]);
		}
	}
	values.push_back(stod(temp));
};
