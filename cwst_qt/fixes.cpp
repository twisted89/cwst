#include <iostream>
#include <Windows.h>
#include <psapi.h>
#include <TlHelp32.h>
#include <fcntl.h>
#include <io.h>

char dlldir[320];
char *GetDirectoryFile(const char *filename)
{
	static char path[320];
	strcpy_s(path, dlldir);
	strcat_s(path, filename);
	return path;
}

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


void MakeJMP(BYTE *pAddress, DWORD dwJumpTo, DWORD dwLen)
{
	DWORD dwOldProtect, dwBkup, dwRelAddr;
	VirtualProtect(pAddress, dwLen, PAGE_EXECUTE_READWRITE, &dwOldProtect);
	dwRelAddr = (DWORD) (dwJumpTo - (DWORD) pAddress) - 5;
	*pAddress = 0xE9;
	*((DWORD *)(pAddress + 0x1)) = dwRelAddr;
	for(DWORD x = 0x5; x < dwLen; x++) *(pAddress + x) = 0x90;
	VirtualProtect(pAddress, dwLen, dwOldProtect, &dwBkup);

	return;

}
DWORD g_dwCodeCaveAddr= FindPattern(reinterpret_cast<DWORD>(GetModuleHandle(NULL)),GetModuleSize("Server.exe"),
									reinterpret_cast<PBYTE>("\x81\xC1\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x8D\x4D\xA8\xC6\x45\xFC\x01\xE8\x00\x00\x00\x00"),
									"xx????x????xxxxxxxx????");

DWORD dwJMPBack=(g_dwCodeCaveAddr+6);
DWORD dwJMPBack2=(g_dwCodeCaveAddr+11);
__declspec(naked) void CrashFix()
{
	__asm
	{
		add     ecx, 90h
			cmp             ecx,0x90
			JNE             ZERO
			JMP             [dwJMPBack2]
ZERO:
		JMP             [dwJMPBack]
	}
}


void LoadFixes()
{
	SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);

	const BYTE MAX_PLAYER= 250;

	DWORD server_base = (DWORD)GetModuleHandleA("Server.exe");


	DWORD max_players_addr = FindPattern(reinterpret_cast<DWORD>(GetModuleHandle(NULL)),GetModuleSize("Server.exe"),
		reinterpret_cast<PBYTE>("\xFF\x15\x00\x00\x00\x00\x8B\xC8\xFF\x15\x00\x00\x00\x00\x83\xBD\x6C\xFE\xFF\xFF\x04"),
		"xx????xxxx????xxxxxxx");
	printf("MaxPlayerAddress found at %x\n",max_players_addr);
	max_players_addr += 20;

	if (max_players_addr)
	{
		char* max_players = (char*)(max_players_addr);
		WriteProcessMemory(GetCurrentProcess(),(PVOID)max_players_addr,&MAX_PLAYER,1,0);

		printf("Max players set to %d\n",(int)*max_players);
	}
	else
		printf("Max players address not found\n");


	DWORD dwMaxPlayerAddr2 = FindPattern(reinterpret_cast<DWORD>(GetModuleHandle(NULL)),GetModuleSize("Server.exe"),
		reinterpret_cast<PBYTE>("\x83\xFF\x0A\x7F\x1B\x8B\x8D\x00\x00\x00\x00\xEB\xC0"),
		"xxxxxxx????xx");
	printf("MaxPlayerAddress2 found at %x\n",dwMaxPlayerAddr2);
	dwMaxPlayerAddr2 += 2;

	if (dwMaxPlayerAddr2)
	{
		char* szMaxPlayers = (char*)(dwMaxPlayerAddr2);
		WriteProcessMemory(GetCurrentProcess(),(PVOID)dwMaxPlayerAddr2,&MAX_PLAYER,1,0);

		printf("Max players2 set to %d\n",(int)*szMaxPlayers);
	}
	else
		printf("Max players2 address not found\n");


	DWORD dwRangerSkillFixAddr= FindPattern(reinterpret_cast<DWORD>(GetModuleHandle(NULL)),GetModuleSize("Server.exe"),
		reinterpret_cast<PBYTE>("\x79\x09\x8B\x84\x8E\x00\x00\x00\x00\x85\xC0\x75\x1B\x80\x7E\x60\x00"),
		"xxxxx????xxxxxxxx");
	if(dwRangerSkillFixAddr)
	{
		printf("RangeSkillFixAddress found at %x\n",dwRangerSkillFixAddr);
		WriteProcessMemory(GetCurrentProcess(),(PVOID)dwRangerSkillFixAddr,"\xEB",1,0);
	}
	else
		printf("RangeSkillFixAddress signature not found\n");

	DWORD dwDisconnectFix= FindPattern(reinterpret_cast<DWORD>(GetModuleHandle(NULL)),GetModuleSize("Server.exe"),
		reinterpret_cast<PBYTE>("\x8B\x01\xFF\x50\x08\x8B\x4E\x10\x85\xC9\x74\x15\x8B\x11\x3B\xCE\x0F\x95\xC0\x0F\xB6\xC0\x50\xFF\x52\x10\xC7\x46\x00\x00\x00\x00\x00"),
		"xxxxxxxxxxxxxxxxxxxxxxxxxxxx?????");
	if(dwDisconnectFix)
	{
		dwDisconnectFix+=5;
		printf("dwDisconnectFix found at %x\n",dwDisconnectFix);
		WriteProcessMemory(GetCurrentProcess(),(PVOID)dwDisconnectFix,"\xEB\x3f\x90",3,0);
	}
	else
		printf("dwDisconnectFix signature not found\n");



	if(g_dwCodeCaveAddr)
	{
		MakeJMP((BYTE*)(g_dwCodeCaveAddr),(DWORD)CrashFix,0x6);
	}
	else
		printf("CodeCaveAddr signature not found\n");
}