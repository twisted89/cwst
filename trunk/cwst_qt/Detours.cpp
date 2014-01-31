#include "cwst_qt.h"

#pragma region Detours
//My Detour methods

SOCKET WINAPI MyAccept(SOCKET s, sockaddr *addr, int *addrlen)
{
	/*
	SOCKET ClientSocket = pAccept(s, addr, addrlen);
	//Get IP
	socklen_t len;
	struct sockaddr_storage saddr;
	char ipstr[INET6_ADDRSTRLEN];
	int port;
	len = sizeof saddr;
	getpeername(ClientSocket, (struct sockaddr*)&saddr, &len);
	// deal with both IPv4 and IPv6:
	if (saddr.ss_family == AF_INET) {
		struct sockaddr_in *ClientSocket = (struct sockaddr_in *)&saddr;
		port = ntohs(ClientSocket->sin_port);
		inet_ntop(AF_INET, &ClientSocket->sin_addr, ipstr, sizeof ipstr);
	} else { // AF_INET6
		struct sockaddr_in6 *ClientSocket = (struct sockaddr_in6 *)&saddr;
		port = ntohs(ClientSocket->sin6_port);
		inet_ntop(AF_INET6, &ClientSocket->sin6_addr, ipstr, sizeof ipstr);
	}
	//Accept connection logic
	bool Accept = false;
	bool privateIP = false;
	AddLog("Client IP: " + ipstr + "\n");
	if (UsePublicFirst)
	{
		if (PublicConnectionsList.size() >= (UINT)MaxPublicPlayers)
		{
			if (std::find(PrivateIPArray.begin(), PrivateIPArray.end(), ipstr) != PrivateIPArray.end())
			{
				spl << "IP found in private IP list\n";
				if (PrivateConnectionsList.size() >= (UINT)MaxPrivatePlayers)
				{
					spl << "Max private players reached, closing socket...\n";
				}
				else
				{
					Accept = true;
					privateIP = true;
				}
			}
			else
			{
				spl << "Max players reached, closing socket...\n";
			}
		}
		else
			Accept = true;
	}
	else
	{
		if (std::find(PrivateIPArray.begin(), PrivateIPArray.end(), ipstr) != PrivateIPArray.end())
		{
			spl << "IP found in private IP list\n";
			if (PrivateConnectionsList.size() >= (UINT)MaxPrivatePlayers)
			{
				spl << "Max private players reached, closing socket...\n";
			}
			else
			{
				Accept = true;
				privateIP = true;
			}
		}
		else
		{
			if (PublicConnectionsList.size() >= (UINT)MaxPublicPlayers)
			{
				spl << "Max players reached, closing socket...\n";
			}
			else
				Accept = true;		
		}
	}
	if (std::find(BlacklistArray.begin(), BlacklistArray.end(), ipstr) != BlacklistArray.end())
	{
		spl << "IP found in blacklist, closing socket...\n";
		Accept = false;
	}
	if (!Accept)
	{
		closesocket(ClientSocket);
	}
	else
	{
		if (privateIP)
			PrivateConnectionsList.push_back(new Connection(ClientSocket, ipstr));
		else
			PublicConnectionsList.push_back(new Connection(ClientSocket, ipstr));
	}
	return ClientSocket;
	*/
	return pAccept(s, addr, addrlen);
}

int WINAPI MyCloseSocket(SOCKET s)
{
	return pCloseSocket(s);
}

int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags)
{
	return psend(socket, buffer, length, flags);
}


int WINAPI MyRecv(SOCKET socket, char* buffer, int length, int flags)
{
	return precv(socket, buffer, length, flags);
}

__declspec(dllexport) void cwst_qt::DetourAndErrorCheck(PVOID* pFunctionToDetour, PVOID pReplacement,
														const char* functionName)
{
	char* debugString = new char[256];
	ZeroMemory(debugString, 256);
	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());
	DetourAttach(pFunctionToDetour, pReplacement);
	int errorCode = DetourTransactionCommit();
	if(errorCode == NO_ERROR)
	{
		sprintf_s(debugString, 255, "Address of %s: 0x%x\n"
			"Address of replacement function: 0x%x\n"
			"%s() was detoured successfully\n", functionName, pFunctionToDetour,
			pReplacement, functionName);
		//AddLog(debugString);
	}
	else
	{

		if(errorCode == ERROR_INVALID_DATA)
			ui.tb_log->append("ERROR_INVALID_DATA returned\n");
		else if(errorCode == ERROR_INVALID_OPERATION)
			AddLog("ERROR_INVALID_OPERATION returned\n");
		else
			AddLog("Other error code returned\n");
		sprintf_s(debugString, 255, "%s() was not able to be detoured\n"
			"Address of %s: 0x%x\n"
			"Address of replacement function: 0x%x\n", functionName,
			functionName, pFunctionToDetour, pReplacement);
		//AddLog(debugString);
	}
	delete [] debugString;
}

void cwst_qt::CheckAndDetach(PVOID* pDetouredFunction, PVOID pReplacement,
							 const char* functionName)
{
	if(pDetouredFunction != NULL)
	{
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)pDetouredFunction, pReplacement);
		DetourTransactionCommit();
	}
	else
	{
		int errorSize = 64 + strlen(functionName);
		char* errorString = new char[errorSize];
		ZeroMemory(errorString, 32);
		sprintf_s(errorString, errorSize, "%s could not be detached\n"
			"Was it detoured in the first place?\n");
		AddLog(errorString);
		delete [] errorString;
	}
}

#pragma region Detours