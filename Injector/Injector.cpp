#pragma region Includes
#include <windows.h>
#include <tlhelp32.h>
#include <shlwapi.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "IniReader.h"
#include <time.h>
#pragma comment(lib, "User32.lib")
#pragma endregion Includes

#pragma region Defines

#pragma endregion Defines

#pragma region Vars
HANDLE hChildProcess;
DWORD procID;

#pragma endregion Vars

#pragma region Injection

void enableDebugPrivileges() {
	HANDLE hcurrent=GetCurrentProcess();
	HANDLE hToken;
	BOOL bret=OpenProcessToken(hcurrent,40,&hToken);
	LUID luid;
	bret=LookupPrivilegeValue(NULL,"SeDebugPrivilege",&luid);
	TOKEN_PRIVILEGES NewState,PreviousState;
	DWORD ReturnLength;
	NewState.PrivilegeCount =1;
	NewState.Privileges[0].Luid =luid;
	NewState.Privileges[0].Attributes=2;
	AdjustTokenPrivileges(hToken,FALSE,&NewState,28,&PreviousState,&ReturnLength);
}

BOOL Inject(DWORD pID, const char * DLL_NAME)
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

	LoadLibAddy = (LPVOID)GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");

	// Allocate space in the process for our DLL
	RemoteString = (LPVOID)VirtualAllocEx(Proc, NULL, strlen(DLL_NAME), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	// Write the string name of our DLL in the memory allocated
	WriteProcessMemory(Proc, (LPVOID)RemoteString, DLL_NAME, strlen(DLL_NAME), NULL);

	// Load our DLL
	CreateRemoteThread(Proc, NULL, NULL, (LPTHREAD_START_ROUTINE)LoadLibAddy, (LPVOID)RemoteString, NULL, NULL);

	CloseHandle(Proc);
	return true;
}

DWORD GetTargetThreadIDFromProcName(const char * ProcName)
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

#pragma endregion Injection

void killProcessByName(const char *filename)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof (pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (strcmp(pEntry.szExeFile, filename) == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD) pEntry.th32ProcessID);
			if (hProcess != NULL)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}

void ExecuteServer() 
{ 
	BOOL bWorked;
	STARTUPINFO suInfo;
	PROCESS_INFORMATION procInfo;
	char * m_Process = "Server.exe";

	memset (&suInfo, 0, sizeof(suInfo));
	suInfo.cb = sizeof(suInfo);

	bWorked = ::CreateProcess(m_Process,
		NULL,      // can also be NULL
		NULL,
		NULL,
		FALSE,
		0, //CREATE_NEW_CONSOLE
		NULL,
		NULL,
		&suInfo,
		&procInfo);

	hChildProcess = procInfo.hProcess;
	procID = procInfo.dwProcessId;

	if (procInfo.dwThreadId == NULL)
	{
		::MessageBox( 0, "Failed to find/Create Server.exe", "Launch Error", MB_OK);
	}

	// Close any unnecessary handles.
	CloseHandle(procInfo.hThread);
} 

bool fexists(const char *filename)
{
	std::ifstream ini(filename, std::ios::binary);
	if (!ini)
	{
		return false;
	}
	return true;
}

BOOL WINAPI HandlerRoutine( DWORD dwCtrlType )
{
	return dwCtrlType == CTRL_CLOSE_EVENT;
}

int main(int argc, char * argv[])
{
	std::ofstream outputlog("debuglog.txt");
	//SetConsoleCtrlHandler(HandlerRoutine, true);
	if (!fexists(".\\CWSTSettings.ini"))
		printf("Can't find CWSTSettings.ini, loading defaults.\n");
	if (!fexists("cwst.dll"))
	{
		printf("Cant find cwst.dll in the current directory, shutting down...\n");
		system("PAUSE");
	}
	CIniReader iniReader(".\\CWSTSettings.ini");
	bool autorestart = iniReader.ReadBoolean("Settings", "Autorestart", true); 
	while (true)
	{
		killProcessByName("Server.exe");
		ShowWindow( GetConsoleWindow(), SW_SHOW );
		ExecuteServer();
		//Sleep(2000);
		DWORD pID = GetTargetThreadIDFromProcName("Server.exe");
		if (pID == 0)
		{
			printf("Server.exe isn't running!\n");
			system("PAUSE");
			break;
		}
		else
		{
			// Get the dll's full path name
			char buf[MAX_PATH] = {0};
			GetFullPathName("cwst.dll", MAX_PATH, buf, NULL);
			// Inject our main dll
			if(!Inject(pID, buf))
			{
				printf("DLL failed to inject into Server.exe! Closing server...\n");
				TerminateProcess(hChildProcess, 0);
				system("PAUSE");
				break;
			}else{
				 //printf("DLL injected successfully!\n");
				//ShowWindow( GetConsoleWindow(), SW_HIDE );
			}
		}
		WaitForSingleObject(hChildProcess, INFINITE);
		killProcessByName("Server.exe");
		DWORD exitcode;
		BOOL rc = GetExitCodeProcess(hChildProcess, &exitcode);
		printf("Exited with code %d \n", exitcode);
		outputlog << "Exited with code " << exitcode << "\n";
		if (exitcode == 0 || exitcode != 0 && autorestart == false)
			break;
		printf("Server crashed, restarting...\n");
		outputlog << "Server crashed, restarting...\n";
	}
	return 0;
}

