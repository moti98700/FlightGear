#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include "Client.hpp"

using namespace std;

Client *Client::instance = 0;
Client *Client::getInstance()
{
	if (!instance)
		instance = new Client();
	return instance;
}

void Client::Connect(int port, const char *ip)
{
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		cout << " Socket creation error" << endl;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if (inet_pton(AF_INET, ip, &serv_addr.sin_addr) <= 0)
	{
		cout << "Invalid address/ Address not supported" << endl;
	}

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		cout << "Connection Failed" << endl;
	}
	else
		cout << "Connection Established" << endl;
}

void Client::Send(char const *command)
{
	auto len = strlen(command);
	auto s = send(sock, command, len, 0);
	if (s != len)
	{
		std::cout << "The send failed";
	}
	char buffer[4096] = {0};
	read(sock, buffer, 4096);
}
