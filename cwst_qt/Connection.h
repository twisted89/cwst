#include <Winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include "PlayerProfile.h"
#pragma once
class Connection
{
public:
	bool Connection::isSocket(SOCKET sock);
	Connection(SOCKET sock, char * address);
	~Connection(void);
	SOCKET s;
	char ipAddress[64];
	char * playerName[255];
	PlayerProfile profile;
};

