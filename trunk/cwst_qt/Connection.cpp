#include "Connection.h"

bool Connection::isSocket(SOCKET sock)
{
	if(s == sock)
		return true;
	else
		return false;
}

Connection::Connection(SOCKET sock, char * address)
{
	s = sock;
	strcpy_s(ipAddress, address);
	//ipAddress = address;
}


Connection::~Connection(void)
{
}

