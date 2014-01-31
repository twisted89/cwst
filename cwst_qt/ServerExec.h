#include <windows.h>
#include <TlHelp32.h>
#include <Shlwapi.h>
#include <atlstr.h>
#include <QString>
#pragma once
class ServerExec
{
public://Vars
	bool autorestart;
private:
	HANDLE hChildProcess;
	DWORD procID;
	void (*LogFunc)(QString);
public:	//Methods
	ServerExec(void (*pLogFunc)(QString));
	~ServerExec(void);
	void ServerExec::Start();
	void ServerExec::Stop();
private:
	void ServerExec::ServerRun();
	BOOL ServerExec::ExecuteServer();
	DWORD ServerExec::GetTargetThreadIDFromProcName(PCWSTR ProcName);
	BOOL ServerExec::Inject(DWORD pID, const char * DLL_NAME);
	void ServerExec::enableDebugPrivileges();
	PCWSTR ServerExec::VariantFromString(const CString& str);
};

