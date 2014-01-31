#include "cwst_qt.h"
#include "BanManagement.h"
#include "PrivateIPManagement.h"
#include "PlayerDetails.h"

cwst_qt * cwst_qtRef;
DWORD modulesize;
DWORD server_base;
DWORD max_players_addr;
DWORD dwMaxPlayerAddr2;
DWORD dwRangerSkillFixAddr;
DWORD dwDisconnectFix;
DWORD dwInnTimeResetFixAddr;
DWORD dwJMPBack;
DWORD dwJMPBack2;
bool _scrollVisible = false;

#pragma region Fixes

DWORD GetModuleSize(LPSTR strModuleName)
{
	MODULEENTRY32   lpme= {0};
	DWORD                   dwSize=0;
	DWORD                   PID=GetCurrentProcessId();
	BOOL                    isMod=0;
	char                    chModName[256];

	strcpy_s(chModName,strModuleName);
	_strlwr_s(chModName);

	HANDLE hSnapshotModule=CreateToolhelp32Snapshot(TH32CS_SNAPMODULE ,PID);
	if (hSnapshotModule)
	{
		lpme.dwSize=sizeof(lpme);
		isMod=Module32First(hSnapshotModule,&lpme);
		while(isMod)
		{
			if (strcmp((char*)_wcslwr(lpme.szExePath),chModName))
			{
				dwSize=(DWORD)lpme.modBaseSize;
				CloseHandle(hSnapshotModule);
				return dwSize;
			}
			isMod=Module32Next(hSnapshotModule,&lpme);
		}
	}
	CloseHandle(hSnapshotModule);

	return 0;
}


DWORD FindPattern(DWORD start_offset, DWORD size, BYTE* pattern, char mask[] )
{

	DWORD pos = 0;
	int searchLen = strlen(mask) - 1;
	for( DWORD retAddress = start_offset; retAddress < start_offset + size; retAddress++ )
	{
		if( *(BYTE*)retAddress == pattern[pos] || mask[pos] == '?' ){
			if( mask[pos+1] == '\0' )
				return (retAddress - searchLen);
			pos++;
		}
		else
			pos = 0;
	}
	return NULL;
}

void SetMaxPlayers(BYTE MAX_PLAYER)
{
	std::stringstream ss; 
	if (!max_players_addr)
	{
		max_players_addr = FindPattern(reinterpret_cast<DWORD>(GetModuleHandle(NULL)),modulesize,
			reinterpret_cast<PBYTE>("\xFF\x15\x00\x00\x00\x00\x8B\xC8\xFF\x15\x00\x00\x00\x00\x83\xBD\x6C\xFE\xFF\xFF\x04"),
			"xx????xxxx????xxxxxxx");
		if (!max_players_addr)
		{
			ss << "Max players address 1 not found\n";
			AddLog(ss.str().c_str());
			return;
		}
		max_players_addr += 20;
	}

	WriteProcessMemory(GetCurrentProcess(),(PVOID)max_players_addr,&MAX_PLAYER,1,0);
	ss << "MaxPlayer check 1 found and patched to " << (int)MAX_PLAYER << "\n";
	AddLog(ss.str().c_str());
	ss.str(std::string());
	if (!dwMaxPlayerAddr2)
	{
		dwMaxPlayerAddr2 = FindPattern(reinterpret_cast<DWORD>(GetModuleHandle(NULL)),modulesize,
			reinterpret_cast<PBYTE>("\x83\xFF\x0A\x7F\x1B\x8B\x8D\x00\x00\x00\x00\xEB\xC0"),
			"xxxxxxx????xx");
		if (!dwMaxPlayerAddr2)
		{
			ss << "Max players address 2 not found\n";
			AddLog(ss.str().c_str());
			return;
		}
		dwMaxPlayerAddr2 += 2;
	}

	WriteProcessMemory(GetCurrentProcess(),(PVOID)dwMaxPlayerAddr2,&MAX_PLAYER,1,0);
	ss << "MaxPlayer check 2 found and patched to " << (int)MAX_PLAYER << "\n";
	AddLog(ss.str().c_str());
}

void setupFixes()
{
	modulesize = GetModuleSize("Server.exe");
	server_base = (DWORD)GetModuleHandleA("Server.exe");
}

#pragma endregion Fixes

#pragma region Detours
//Prototype detours
SOCKET (WINAPI *pAccept)(SOCKET s, sockaddr *addr, int *addrlen) = NULL;
SOCKET WINAPI MyAccept(SOCKET s, sockaddr *addr, int *addrlen);
//
int (WINAPI *pCloseSocket)(SOCKET s) = NULL;
int WINAPI MyCloseSocket(SOCKET s);
//
int (WINAPI *precv)(SOCKET socket, char* buffer, int length, int flags) = NULL;
int WINAPI MyRecv(SOCKET socket, char* buffer, int length, int flags);
//
int (WINAPI *psend)(SOCKET socket, const char* buffer, int length, int flags) = NULL;
int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags);

void banPlayer(int socket, QString IP)
{

	kickPlayer(socket);
	if (std::find(cwst_qtRef->BlacklistArray.begin(), cwst_qtRef->BlacklistArray.end(), IP.toStdString()) != cwst_qtRef->BlacklistArray.end())
	{
		AddLog("Player already in blacklist, probably shouldn't have got here!\n");
	}
	else
	{

		cwst_qtRef->BlacklistArray.push_back(IP.toStdString());
		std::vector<std::string>::const_iterator iter;
		std::string bannedIPs;
		for (iter= cwst_qtRef->BlacklistArray.begin(); iter!= cwst_qtRef->BlacklistArray.end(); iter++)
		{
			std::string bIP = *iter;
			if (iter != cwst_qtRef->BlacklistArray.begin())
				bannedIPs += ", ";
			bannedIPs += bIP;
		}

		char * cBannedIPs = new char[bannedIPs.size() + 1];
		std::copy(bannedIPs.begin(), bannedIPs.end(), cBannedIPs);
		cBannedIPs[bannedIPs.size()] = '\0'; // don't forget the terminating 0
		CIniWriter iniwriter(".\\CWSTSettings.ini");
		iniwriter.WriteString("IP", "BannedIPs", cBannedIPs); 
		delete[] cBannedIPs;

	}

}

void kickPlayer(int Socket)
{
	bool found = false;
	std::list<Connection*>::iterator p = cwst_qtRef->PublicConnectionsList.begin();
	while(p != cwst_qtRef->PublicConnectionsList.end())
	{
		if((int)((*p)->s) == Socket)
		{
			found = true;
			AddLog("Kicking player...\n");
			SOCKET cs = (*p)->s;
			p = cwst_qtRef->PublicConnectionsList.erase(p);
			pCloseSocket(cs);
			if ((int)cwst_qtRef->PublicConnectionsList.size() == 0)
				break;
		}
		else
			p++;
	}
	p = cwst_qtRef->PrivateConnectionsList.begin();
	while(p != cwst_qtRef->PrivateConnectionsList.end())
	{
		if((int)((*p)->s) == Socket)
		{
			found = true;
			AddLog("Kicking player...\n");
			SOCKET cs = (*p)->s;
			p = cwst_qtRef->PrivateConnectionsList.erase(p);
			pCloseSocket(cs);
			if ((int)cwst_qtRef->PrivateConnectionsList.size() == 0)
				break;
		}
		else
			p++;
	}
	if (!found)
		AddLog("Failed to find player in active connections");
}

SOCKET WINAPI MyAccept(SOCKET s, sockaddr *addr, int *addrlen)
{
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
	if (cwst_qtRef->UsePublicFirst)
	{
		if (cwst_qtRef->PublicConnectionsList.size() >= (UINT)cwst_qtRef->MaxPublicPlayers)
		{
			if (std::find(cwst_qtRef->PrivateIPArray.begin(), cwst_qtRef->PrivateIPArray.end(), ipstr) != cwst_qtRef->PrivateIPArray.end())
			{
				//AddLog("IP found in private IP list\n");
				if (cwst_qtRef->PrivateConnectionsList.size() >= (UINT)cwst_qtRef->MaxPrivatePlayers)
				{
					//AddLog("Max private players reached, closing socket...\n");
				}
				else
				{
					Accept = true;
					privateIP = true;
				}
			}
			else
			{
				//AddLog("Max players reached, closing socket...\n");
			}
		}
		else
			Accept = true;
	}
	else
	{
		if (std::find(cwst_qtRef->PrivateIPArray.begin(), cwst_qtRef->PrivateIPArray.end(), ipstr) != cwst_qtRef->PrivateIPArray.end())
		{
			//AddLog("IP found in private IP list\n");
			if (cwst_qtRef->PrivateConnectionsList.size() >= (UINT)cwst_qtRef->MaxPrivatePlayers)
			{
				//AddLog("Max private players reached, closing socket...\n");
			}
			else
			{
				Accept = true;
				privateIP = true;
			}
		}
		else
		{
			if (cwst_qtRef->PublicConnectionsList.size() >= (UINT)cwst_qtRef->MaxPublicPlayers)
			{
				//AddLog("Max players reached, closing socket...\n");
			}
			else
				Accept = true;		
		}
	}
	if (std::find(cwst_qtRef->BlacklistArray.begin(), cwst_qtRef->BlacklistArray.end(), ipstr) != cwst_qtRef->BlacklistArray.end())
	{
		//AddLog("IP found in blacklist, closing socket...\n");
		Accept = false;
	}
	if (!Accept)
	{
		closesocket(ClientSocket);
	}
	else
	{
		if (privateIP)
			cwst_qtRef->PrivateConnectionsList.push_back(new Connection(ClientSocket, ipstr));
		else
			cwst_qtRef->PublicConnectionsList.push_back(new Connection(ClientSocket, ipstr));
		QString socketint = QString::number((int)ClientSocket);
		QString IP(ipstr);
		cwst_qtRef->AddPlayer(socketint, IP);
		std::stringstream ss;
		ss << "Client successfully connected with IP: " << ipstr << "\n";
		AddLog(ss.str().c_str());
	}
	return ClientSocket;
}

int WINAPI MyCloseSocket(SOCKET s)
{
	std::list<Connection*>::iterator p = cwst_qtRef->PublicConnectionsList.begin();
	while(p != cwst_qtRef->PublicConnectionsList.end())
	{
		if((*p)->s == s)
		{
			std::stringstream ss;
			ss << (*p)->ipAddress << " disconnected\n";
			AddLog(ss.str().c_str());
			QString qS = QString::number((int)(*p)->s);
			cwst_qtRef->removerowSocket(qS);
			p = cwst_qtRef->PublicConnectionsList.erase(p);
			if ((int)cwst_qtRef->PublicConnectionsList.size() == 0)
				break;
		}
		else
			p++;
	}
	p = cwst_qtRef->PrivateConnectionsList.begin();
	while(p != cwst_qtRef->PrivateConnectionsList.end())
	{
		if((*p)->s == s)
		{
			std::stringstream ss;
			ss << (*p)->ipAddress << " disconnected\n";
			AddLog(ss.str().c_str());
			QString qS = QString::number((int)(*p)->s);
			cwst_qtRef->removerowSocket(qS);
			p = cwst_qtRef->PrivateConnectionsList.erase(p);
			if ((int)cwst_qtRef->PrivateConnectionsList.size() == 0)
				break;
		}
		else
			p++;
	}
	return pCloseSocket(s);
}

//std::ofstream outputlog("Packets.txt");

void LogAndVerboseOutput(const char* functionName, const char* buffer, int length)
{
	/*
	int debugSize = (64 + strlen(functionName) + strlen(buffer));
	char *debugString = new char[debugSize];
	ZeroMemory(debugString, debugSize);
	sprintf_s(debugString, 64, "---------- %s()----------\n", functionName);
	outputlog << debugString;
	for (int i = 0; i < strlen(buffer); i++)
	{
		outputlog << std::hex << (int)buffer[i];
	}
	outputlog << "\n";
	outputlog << "----------$$END$$----------\n";
	delete [] debugString;
	*/
}

int WINAPI MySend(SOCKET socket, const char* buffer, int length, int flags)
{
	LogAndVerboseOutput("Send", buffer, length);
	return psend(socket, buffer, length, flags);
}

int WINAPI MyRecv(SOCKET socket, char* buffer, int length, int flags)
{
	int returnVal = precv(socket, buffer, length, flags);
	LogAndVerboseOutput("Receive", buffer, length);
	if (length > 250)
	{
		char uncompressed[4450];

		ULONG ucompSize = 4450;
		ULONG compSize = length;

		// Inflate
		uncompress((Bytef *)uncompressed, &ucompSize, (Bytef *)buffer, compSize); //4386

		if (atoi(uncompressed + 4) != 0)
			return returnVal;
		
		std::ofstream f("profile.hex", std::ios_base::out | std::ios_base::binary);
		f.write(uncompressed, sizeof(uncompressed));
		f.close();
		

		PlayerProfile pp = *(new PlayerProfile());
		BinaryReader br = *(new BinaryReader((byte *)&uncompressed));
		pp.Read(br);

		///////
		// Max level check
		///////

		if (cwst_qtRef->ui.cb_MaxLvlCheck->isChecked())
		{
			if (pp.Level > cwst_qtRef->ui.cb_MaxLevel->currentIndex())
			{
				AddLog("Detected a player above max level, attempting to kick...");
				MyCloseSocket(socket);
			}
		}

		//AddLog((*p)->ipAddress); AddLog("->"); AddLog(username.c_str()); AddLog("\n");
		QString s = QString::number((int)socket);
		cwst_qtRef->Addusername(s, pp.Name.c_str());

		bool found = false;
		std::list<Connection*>::iterator p = cwst_qtRef->PublicConnectionsList.begin();
		while(p != cwst_qtRef->PublicConnectionsList.end())
		{
			if((*p)->s == socket)
			{
				found = true;
				(*p)->profile = pp;
				break;
			}
			else
				p++;
		}
		if (!found)
		{
			p = cwst_qtRef->PrivateConnectionsList.begin();
			while(p != cwst_qtRef->PrivateConnectionsList.end())
			{
				if((*p)->s == socket)
				{
					(*p)->profile = pp;
					break;
				}
				else
					p++;
			}
		}

	}
	return returnVal;
}

void SetupDetours()
{
	DetourRestoreAfterWith();	//Start finding function pointers
	pAccept = (SOCKET (WINAPI *)(SOCKET , sockaddr* , int*))
		DetourFindFunction("Ws2_32.dll", "accept");
	pCloseSocket = (int (WINAPI *)(SOCKET))
		DetourFindFunction("Ws2_32.dll", "closesocket");
	psend = (int (WINAPI *)(SOCKET, const char*, int, int))
		DetourFindFunction("Ws2_32.dll", "send");
	precv = (int (WINAPI *)(SOCKET, char*, int, int))
		DetourFindFunction("Ws2_32.dll", "recv");
	DetourAndErrorCheck(&(PVOID&)pAccept, MyAccept, "accept"); //Begin detouring
	DetourAndErrorCheck(&(PVOID&)pCloseSocket, MyCloseSocket, "closesocket");
	DetourAndErrorCheck(&(PVOID&)psend, MySend, "send");
	DetourAndErrorCheck(&(PVOID&)precv, MyRecv, "recv");
}

__declspec(dllexport) void DetourAndErrorCheck(PVOID* pFunctionToDetour, PVOID pReplacement,
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
			AddLog("ERROR_INVALID_DATA returned\n");
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

void CheckAndDetach(PVOID* pDetouredFunction, PVOID pReplacement,
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

#pragma region Settings

void cwst_qt::ReadSettings()
{
	if (!fexists(".\\CWSTSettings.ini"))
		AddLog("Can't find CWSTSettings.ini, loading defaults.\n");
	CIniReader iniReader(".\\CWSTSettings.ini");
	MaxPublicPlayers = iniReader.ReadInteger("Settings", "MaxPublicSlots", 4); 
	if (MaxPublicPlayers > 1000 || MaxPublicPlayers < 0)
	{
		AddLog("Invalid MaxPublicSlots value, using default.");
		MaxPublicPlayers = 4;
	}
	ui.cb_publicSlots->setCurrentIndex(MaxPublicPlayers);
	MaxPrivatePlayers = iniReader.ReadInteger("Settings", "MaxPrivateSlots", 4); 
	if (MaxPrivatePlayers > 1000 || MaxPrivatePlayers < 0)
	{
		AddLog("Invalid MaxPrivateSlots value, using default.");
		MaxPrivatePlayers = 4;
	}
	ui.cb_privateSlots->setCurrentIndex(MaxPrivatePlayers);
	MaxLevel = iniReader.ReadInteger("Settings", "MaxLevel", 100); 
	if (MaxLevel > 1000 || MaxLevel < 0)
	{
		AddLog("Invalid MaxLevel value, using default.");
		MaxLevel = 100;
	}
	ui.cb_MaxLevel->setCurrentIndex(MaxLevel);
	ui.cb_MaxLvlCheck->setChecked(iniReader.ReadBoolean("Settings", "MaxLevelEnabled", false));
	UsePublicFirst = iniReader.ReadBoolean("Settings", "UsePublicSlotsFirst", false);
	RunWebInterface = iniReader.ReadBoolean("Settings", "RunWebInterface", false);
	LoggingEnabled = iniReader.ReadBoolean("Settings", "EnableLogs", false);
	MaxPlayers = iniReader.ReadBoolean("Settings", "MaxPlayers", true);
	AlwaysDaytime = iniReader.ReadBoolean("Settings", "AlwaysDaytime", false);
	ui.cb_maxPlayersfix->setChecked(MaxPlayers);
	ui.cb_usePublicFirst->setChecked(UsePublicFirst);
	ui.cb_daylight->setChecked(AlwaysDaytime);
	std::string bannedIPs = iniReader.ReadString("IP", "BannedIPs", "");
	std::string privateIPs = iniReader.ReadString("IP", "PrivateIPs", "");
	boost::split(BlacklistArray, bannedIPs, boost::is_any_of(", "), boost::token_compress_on);
	boost::split(PrivateIPArray, privateIPs, boost::is_any_of(", "), boost::token_compress_on);
}

#pragma endregion Settings

#pragma region Log
QTextEdit * tbLog;
void AddLog(QString logstring)
{
	bool doScroll = (cwst_qtRef->ui.tb_log->verticalScrollBar()->sliderPosition() == cwst_qtRef->ui.tb_log->verticalScrollBar()->maximum()) || (cwst_qtRef->ui.tb_log->verticalScrollBar()->maximum() < 24);

	QTextCursor c = cwst_qtRef->ui.tb_log->textCursor();
	c.beginEditBlock();
	c.movePosition(QTextCursor::End);
	c.insertText(QString::fromStdString(getTimestamp()) + logstring);
	c.endEditBlock();

	if( doScroll )
	{
		cwst_qtRef->ui.tb_log->verticalScrollBar()->setValue(cwst_qtRef->ui.tb_log->verticalScrollBar()->maximum());        
	}

	_scrollVisible = cwst_qtRef->ui.tb_log->verticalScrollBar()->isVisible();
	//tb_log->append(logstring);
}

void AddLog(char * logstring)
{
	int test1 = cwst_qtRef->ui.tb_log->verticalScrollBar()->sliderPosition();
	int test2 = cwst_qtRef->ui.tb_log->verticalScrollBar()->maximum();
	bool doScroll = (cwst_qtRef->ui.tb_log->verticalScrollBar()->sliderPosition() == cwst_qtRef->ui.tb_log->verticalScrollBar()->maximum()) || (cwst_qtRef->ui.tb_log->verticalScrollBar()->maximum() < 24);

	QTextCursor c = cwst_qtRef->ui.tb_log->textCursor();
	c.beginEditBlock();
	c.movePosition(QTextCursor::End);
	QString qs;
	c.insertText(QString::fromStdString(getTimestamp()) + qs.fromLocal8Bit(logstring));
	c.endEditBlock();

	if( doScroll )
	{
		cwst_qtRef->ui.tb_log->verticalScrollBar()->setValue(cwst_qtRef->ui.tb_log->verticalScrollBar()->maximum());        
	}
	//tb_log->append(logstring);
}
#pragma endregion Log

#pragma region Form

void cwst_qt::maxPchanged(bool checked)
{
	if (checked)
		SetMaxPlayers((byte)127);
	else
		SetMaxPlayers((byte)30);
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteBoolean("Settings", "MaxPlayers", checked); 
}

void cwst_qt::usepubfirstchanged(bool checked)
{
	UsePublicFirst = checked;
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteBoolean("Settings", "UsePublicSlotsFirst", checked); 
	if (checked)
		AddLog("Use public slots first enabled\n");
	else
		AddLog("Use public slots first disabled\n");
}

void cwst_qt::MaxLevelCheckChanged(bool checked)
{
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteBoolean("Settings", "MaxLevelEnabled", checked); 
	ui.cb_MaxLevel->setEnabled(checked);
	if (checked)
		AddLog("Max level check enabled\n");
	else
		AddLog("Max level check disabled\n");
}

void cwst_qt::alwaysDaylight(bool checked)
{
	AlwaysDaytime = checked;
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteBoolean("Settings", "AlwaysDaytime", checked); 
	if (AlwaysDaytime)
	{
		WaitForSingleObject(daylightthread, INFINITE);
		SECURITY_ATTRIBUTES SCAttrib; // thread settings
		SCAttrib.bInheritHandle = NULL;
		SCAttrib.lpSecurityDescriptor = NULL;
		SCAttrib.nLength = sizeof(SCAttrib);
		daylightthread = CreateThread(&SCAttrib, NULL, (LPTHREAD_START_ROUTINE)DaylightThread, NULL, NULL, NULL); // CREATE THREAD
		AddLog("Always daylight enabled\n");
	}
	else
	{
		WaitForSingleObject(daylightthread, INFINITE);
		AddLog("Always daylight disabled\n");
	}
}

void DaylightThread()
{
	char daytimePacket[12];
	int Id = 5;
	int Day = 1;
	unsigned int Time = (uint)(60 * 60 * 12 * 1000);
	memcpy(daytimePacket, &Id, 4);
	memcpy(daytimePacket+4, &Day, 4);
	memcpy(daytimePacket+8, &Time, 4);
	while (true)
	{
		std::list<Connection*>::iterator p = cwst_qtRef->PublicConnectionsList.begin();
		while(p != cwst_qtRef->PublicConnectionsList.end())
		{
			send((*p)->s, daytimePacket, 12, 0);			
			p++;
		}
		p = cwst_qtRef->PrivateConnectionsList.begin();
		while(p != cwst_qtRef->PrivateConnectionsList.end())
		{
			send((*p)->s, daytimePacket, 12, 0);	
			p++;
		}
		for (int i = 0; i < 60; i++)
		{
			if (!cwst_qtRef->AlwaysDaytime)
				return;
			Sleep(1000);
			i++;
		}
	}
}

void StatusUpdate()
{
	std::stringstream ss;
	QString Title;
	QString qUptime;
	long miliseconds;
	while (true)
	{
		ss.str(std::string());
		ss << "Public Players " << cwst_qtRef->PublicConnectionsList.size() << "/" << cwst_qtRef->MaxPublicPlayers << " - Private Players " << cwst_qtRef->PrivateConnectionsList.size() << "/" << cwst_qtRef->MaxPrivatePlayers;
		Title = (ss.str().c_str()); // Changes console title
		cwst_qtRef->statuslabel->setText(Title);
		ss.str(std::string());
		miliseconds = cwst_qtRef->uptime->elapsed();
		ss << "Server Uptime " << (int) miliseconds / (1000*60*60) << ":" << (int)(miliseconds % (1000*60*60)) / (1000*60) << ":" << (int) ((miliseconds % (1000*60*60)) % (1000*60)) / 1000;
		qUptime = (ss.str().c_str()); // Changes console title
		cwst_qtRef->uptimelabel->setText(qUptime);		
		Sleep(1000);	
	}
}

void cwst_qt::removerowSocket(QString Socket)
{
	QList<QTableWidgetItem*> items = ui.gv_players->findItems(Socket, Qt::MatchExactly);
	QMap<int, int> rowsMap;
	for(int i = 0; i < items.count(); i++)
	{
		rowsMap[(*items.at(i)).row()] = -1; //garbage value
	}
	QList<int> rowsList = rowsMap.uniqueKeys();
	qSort(rowsList);
	//Now go through your table and delete rows in descending order as content would shift up and hence cannot do it in ascending order with ease.
	for(int i = rowsList.count() - 1; i >= 0; i--)
	{
		ui.gv_players->removeRow(rowsList.at(i));
	}
}

void cwst_qt::removerowIP(QString IP)
{
	QList<QTableWidgetItem*> items = ui.gv_players->findItems(IP, Qt::MatchExactly);
	QMap<int, int> rowsMap;
	for(int i = 0; i < items.count(); i++)
	{
		rowsMap[(*items.at(i)).row()] = -1; //garbage value
	}
	QList<int> rowsList = rowsMap.uniqueKeys();
	qSort(rowsList);
	//Now go through your table and delete rows in descending order as content would shift up and hence cannot do it in ascending order with ease.
	for(int i = rowsList.count() - 1; i >= 0; i--)
	{
		ui.gv_players->removeRow(rowsList.at(i));
	}
}

void cwst_qt::Addusername(QString Socket, QString username)
{
	QList<QTableWidgetItem*> items = ui.gv_players->findItems(Socket, Qt::MatchExactly);
	QMap<int, int> rowsMap;
	for(int i = 0; i < items.count(); i++)
	{
		rowsMap[(*items.at(i)).row()] = -1; //garbage value
	}
	QList<int> rowsList = rowsMap.uniqueKeys();
	qSort(rowsList);
	//Now go through your table and delete rows in descending order as content would shift up and hence cannot do it in ascending order with ease.
	for(int i = rowsList.count() - 1; i >= 0; i--)
	{
		ui.gv_players->setItem(rowsList.at(i), 0, new QTableWidgetItem(username));
	}
}


void cwst_qt::AddPlayer(QString socket, QString IPaddress)
{
	int row = ui.gv_players->rowCount();
	ui.gv_players->insertRow( row);
	ui.gv_players->setItem(row, 1, new QTableWidgetItem(IPaddress));
	ui.gv_players->setItem(row, 2, new QTableWidgetItem(socket));
}

void cwst_qt::PrivateSlotsChanged(int max)
{
	MaxPrivatePlayers = max;
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteInteger("Settings", "MaxPrivateSlots", max); 
}

void cwst_qt::PublicSlotsChanged(int max)
{
	MaxPublicPlayers = max;
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteInteger("Settings", "MaxPublicSlots", max); 
}

void cwst_qt::MaxLevelChanged(int max)
{
	MaxLevel = max;
	CIniWriter iniwriter(".\\CWSTSettings.ini");
	iniwriter.WriteInteger("Settings", "MaxLevel", max); 
}

void cwst_qt::showBansForm()
{
	BanManagement dialog(this);
	dialog.exec();
}

void cwst_qt::showPrivateIpsForm()
{
	PrivateIPManagement dialog(this);
	dialog.exec();
}

void cwst_qt::Exit()
{
	exit(0);
}

void cwst_qt::contextMenuEvent(const QPoint &pos)
{   
	QList<QModelIndex> indexes = ui.gv_players->selectionModel()->selectedRows();
	if (indexes.count() < 1)
		return;
	if (indexes.count() == 1 && ui.gv_players->item(indexes[0].row(), 0) && ui.gv_players->item(indexes[0].row(), 0)->text().isEmpty() == false)
		Details->setEnabled(true);
	else
		Details->setEnabled(false);
	a = context->exec(ui.gv_players->viewport()->mapToGlobal(pos));
	if (a == Ban)
	{	
		QModelIndex row;
		foreach (row , indexes)
		{
			QString playersocket  = ui.gv_players->item(row.row(), 2)->text();
			QString playerIP  = ui.gv_players->item(row.row(), 1)->text();
			ui.gv_players->removeRow(row.row());
			banPlayer(playersocket.toInt(), playerIP);
		}
	}
	else if (a == Kick)
	{
		QModelIndex row;
		foreach (row , indexes)
		{
			QString playersocket  = ui.gv_players->item(row.row(), 2)->text();
			ui.gv_players->removeRow(row.row());
			kickPlayer(playersocket.toInt());
		}
	}
	else if (a == Details)
	{
		QString playersocket  = ui.gv_players->item(indexes[0].row(), 2)->text();
		PlayerProfile * PP;
		bool found = false;
		std::list<Connection*>::iterator p = PublicConnectionsList.begin();
		while(p != PublicConnectionsList.end())
		{
			if((int)((*p)->s) == playersocket.toInt())
			{
				found = true;
				PP = &(*p)->profile;
				break;
			}
			else
				p++;
		}
		if (!found)
		{
			p = PrivateConnectionsList.begin();
			while(p != PrivateConnectionsList.end())
			{
				if((int)((*p)->s) == playersocket.toInt())
				{
					found = true;
					PP = &(*p)->profile;
					break;
				}
				else
					p++;
			}
		}
		if (found)
		{		
			PlayerDetails dialog(PP, this);
			dialog.exec();
		}
	}
}


void cwst_qt::InitialSetup()
{
	qRegisterMetaType<QVector<QVector<int>>>("qvectorInt");
	qRegisterMetaType<QTextCursor>("QTextCursor");

	context = new QMenu(this);
	Ban = context->addAction(tr("Ban"));    
	Kick = context->addAction(tr("Kick"));   
	Details = context->addAction(tr("Player Details"));   
	ui.gv_players->setContextMenuPolicy(Qt::CustomContextMenu);
	connect(ui.gv_players, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(contextMenuEvent(QPoint)));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(Exit()));
	connect(ui.actionManage_Bans, SIGNAL(triggered()), this, SLOT(showBansForm()));
	connect(ui.actionManage_Private_IP_s, SIGNAL(triggered()), this, SLOT(showPrivateIpsForm()));
	connect(ui.cb_maxPlayersfix, SIGNAL(toggled(bool)), this, SLOT(maxPchanged(bool)));
	//connect(ui.cb_DisconnectFix, SIGNAL(toggled(bool)), this, SLOT(disconnectchanged(bool)));
	//connect(ui.cb_RangerSkillFix, SIGNAL(toggled(bool)), this, SLOT(rangerchanged(bool)));
	//connect(ui.cb_InnResetFix, SIGNAL(toggled(bool)), this, SLOT(innchanged(bool))); 
	connect(ui.cb_usePublicFirst, SIGNAL(toggled(bool)), this, SLOT(usepubfirstchanged(bool)));
	connect(ui.cb_daylight, SIGNAL(toggled(bool)), this, SLOT(alwaysDaylight(bool)));
	connect(ui.cb_MaxLvlCheck, SIGNAL(toggled(bool)), this, SLOT(MaxLevelCheckChanged(bool)));

	ui.gv_players->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.gv_players->setColumnCount(3);
	//ui.gv_players->insertRow(0);
	ui.gv_players->setHorizontalHeaderItem(0, new QTableWidgetItem("Player"));
	ui.gv_players->setHorizontalHeaderItem(1, new QTableWidgetItem("IP"));
	ui.gv_players->setHorizontalHeaderItem(2, new QTableWidgetItem("Socket"));
	//ui.gv_players->resizeRowsToContents();
	//ui.gv_players->resizeColumnsToContents();
	ui.gv_players->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	statuslabel = new QLabel("");
	statuslabel->setAlignment(Qt::AlignHCenter);
	ui.statusBar->addPermanentWidget(cwst_qtRef->statuslabel, 1);
	uptimelabel = new QLabel("");
	uptimelabel->setAlignment(Qt::AlignRight);
	ui.statusBar->addPermanentWidget(cwst_qtRef->uptimelabel, 1);
	QStringList nums;
	for (int i = 0; i < 1001; i++)
	{
		nums << QString::number(i);
	}
	ui.cb_publicSlots->addItems(nums);
	ui.cb_privateSlots->addItems(nums);
	ui.cb_MaxLevel->addItems(nums);

	AddLog("========= CWST ==========\n");
}

cwst_qt::cwst_qt(QWidget *parent)
	: QMainWindow(parent)
{
	cwst_qtRef = this;
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
	uptime = new QElapsedTimer();
	uptime->start();
	tbLog = ui.tb_log;
	ui.setupUi(this);
	InitialSetup();
	setupFixes();
	ReadSettings();
	SECURITY_ATTRIBUTES SCAttrib; // thread settings
	SCAttrib.bInheritHandle = NULL;
	SCAttrib.lpSecurityDescriptor = NULL;
	SCAttrib.nLength = sizeof(SCAttrib);
	CreateThread(&SCAttrib, NULL, (LPTHREAD_START_ROUTINE)StatusUpdate, NULL, NULL, NULL); // CREATE THREAD
	connect(ui.cb_privateSlots , SIGNAL(currentIndexChanged(int)),this,SLOT(PrivateSlotsChanged(int)));
	connect(ui.cb_publicSlots, SIGNAL(currentIndexChanged(int)), this, SLOT(PublicSlotsChanged(int)));
	connect(ui.cb_MaxLevel, SIGNAL(currentIndexChanged(int)), this, SLOT(MaxLevelChanged(int)));
	SetupDetours();
	//boost::thread* pThread = new boost::thread(&ServerExec::Start, serverex );       // pointer to instance of class

}

void cwst_qt::closeEvent(QCloseEvent *event) {
}

cwst_qt::~cwst_qt()
{

}

#pragma endregion Form


