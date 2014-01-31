#include "ServerExec.h"

PCWSTR ServerExec::VariantFromString(const CString& str)
{
	PCWSTR psz = T2CW(str);
	return psz;
}

void ServerExec::enableDebugPrivileges() {
	HANDLE hcurrent=GetCurrentProcess();
	HANDLE hToken;
	BOOL bret=OpenProcessToken(hcurrent,40,&hToken);
	LUID luid;
	bret=LookupPrivilegeValueA(NULL,"SeDebugPrivilege",&luid);
	TOKEN_PRIVILEGES NewState,PreviousState;
	DWORD ReturnLength;
	NewState.PrivilegeCount =1;
	NewState.Privileges[0].Luid =luid;
	NewState.Privileges[0].Attributes=2;
	AdjustTokenPrivileges(hToken,FALSE,&NewState,28,&PreviousState,&ReturnLength);
}

BOOL ServerExec::Inject(DWORD pID, const char * DLL_NAME)
{
	enableDebugPrivileges();
	HANDLE Proc;
	//HMODULE hLib;
	char buf[50] = {0};
	LPVOID RemoteString, LoadLibAddy;

	if(!pID)
		return false;

	Proc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);
	if(!Proc)
	{
		sprintf(buf, "OpenProcess() failed: %d", GetLastError());
		//MessageBox(NULL, buf, "Loader", MB_OK);
		printf(buf);
		return false;
	}

	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA");

	// Allocate space in the process for our DLL
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	// Write the string name of our DLL in the memory allocated
	WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, strlen(DLL_NAME), NULL);

	// Load our DLL
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);

	CloseHandle(Proc);
	return true;
}

DWORD ServerExec::GetTargetThreadIDFromProcName(PCWSTR ProcName)
{
	PROCESSENTRY32 pe;
	HANDLE thSnapShot;
	BOOL retval, ProcFound = false;

	thSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(thSnapShot == INVALID_HANDLE_VALUE)
	{
		//MessageBox(NULL, "Error: Unable to create toolhelp snapshot!", "2MLoader", MB_OK);
		printf("Error: Unable to create toolhelp snapshot!");
		return false;
	}

	pe.dwSize = sizeof(PROCESSENTRY32);

	retval = Process32First(thSnapShot, &pe);
	while(retval)
	{
		if(StrStrI(pe.szExeFile, ProcName))
		{
			return pe.th32ProcessID;
		}
		retval = Process32Next(thSnapShot, &pe);
	}
	return 0;
}

BOOL ServerExec::ExecuteServer() 
{ 
	BOOL bWorked;
	STARTUPINFOA suInfo;
	PROCESS_INFORMATION procInfo;
	char * m_Process = "Server.exe";

	memset (&suInfo, 0, sizeof(suInfo));
	suInfo.cb = sizeof(suInfo);

	bWorked = ::CreateProcessA(m_Process,
		NULL,      // can also be NULL
		NULL,
		NULL,
		FALSE,
		CREATE_NO_WINDOW, //CREATE_NEW_CONSOLE
		NULL,
		NULL,
		&suInfo,
		&procInfo);

	hChildProcess = procInfo.hProcess;
	procID = procInfo.dwProcessId;

	if (procInfo.dwThreadId == NULL)
	{
		::MessageBoxA( 0, "Failed to find/Create Server.exe, shutting down...", "Launch Error", MB_OK);
		return false;
	}

	// Close any unnecessary handles.
	CloseHandle(procInfo.hThread);
	return true;
} 

void ServerExec::Start()
{
	while (autorestart)
	{
		LogFunc("Starting Server...\n");
		//Sleep(2000);
		ExecuteServer();
		DWORD pID = GetTargetThreadIDFromProcName(VariantFromString("Server.exe"));
		if (pID == 0)
		{
			LogFunc("Failed to find a running Server.exe process, aborting...!\n");
			break;
		}
		else
		{
			// Get the dll's full path name
			char buf[MAX_PATH] = {0};
			GetFullPathNameA("cwst_qt.dll", MAX_PATH, buf, NULL);
			// Inject our main dll
			if(!Inject(pID, buf))
			{
				LogFunc("DLL failed to inject into Server.exe! Closing server...\n");
				TerminateProcess(hChildProcess, 0);
				break;
			}else{
				LogFunc("DLL injected successfully!\n");
			}
		}
		WaitForSingleObject(hChildProcess, INFINITE);
		DWORD exitcode;
		BOOL rc = GetExitCodeProcess(hChildProcess, &exitcode);
		if (exitcode == 0 || exitcode != 0 && autorestart == false)
		{
			LogFunc("Server Stopped.\n");
			break;
		}
		LogFunc("Server Crashed! Restarting...\n");
	}
}

void ServerExec::Stop()
{
	autorestart = false;
	TerminateProcess(hChildProcess, 0);
	autorestart = true;
}


ServerExec::ServerExec(void (*pLogFunc)(QString))
{
	LogFunc = pLogFunc;
	autorestart = true;
}


ServerExec::~ServerExec(void)
{
}
