#include "cwst_qt.h"
#include <fstream>

DWORD SearchPattern	(char* chPattern,DWORD dwFrom ,DWORD dwTo)
{
	DWORD dwOffset 			= dwFrom;
	DWORD dwSize 				= strlen(chPattern)-1;
	DWORD dwFoundAddress 		= 0;

	char * pEnd = chPattern;
	while(1)
	{
		char &chMyposition =* (char*)dwOffset;

		if ((pEnd[1] != 'x'))
		{
			char chTemp = (char)strtoul(pEnd, &pEnd, 0x10);

			if (chTemp == chMyposition)
			{
				if (dwFoundAddress == 0)
				{
					dwFoundAddress = dwOffset;
				}
			}

			else
			{
				pEnd = chPattern;
				if (dwFoundAddress != 0)
					dwOffset = dwFoundAddress;
				dwFoundAddress=0;
			}
		}

		else
		{
			pEnd = &pEnd[2];
		}

		dwOffset++;

		if (((DWORD)pEnd-(DWORD)chPattern >= dwSize) || (dwOffset>=dwTo))
			break;
	}
	return dwFoundAddress;
}

LPVOID MemCpyEx (LPVOID lpDestination, LPVOID lpSource, int nLen)
{
	DWORD dwOldDestProt = 0;
	DWORD dwOldSrcProt	= 0;

	VirtualProtect	(lpDestination, nLen, PAGE_EXECUTE_READWRITE, &dwOldDestProt);
	VirtualProtect	(lpSource, nLen, PAGE_EXECUTE_READWRITE, &dwOldSrcProt);
	memcpy			(lpDestination, lpSource, nLen);
	VirtualProtect	(lpDestination, nLen, dwOldDestProt, NULL);
	VirtualProtect	(lpSource, nLen, dwOldSrcProt, NULL);

	return lpDestination;
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


bool validateIpAddress(const std::string ipAddress)
{
	struct sockaddr_in sa;
	int result = inet_pton(AF_INET, ipAddress.c_str(), &(sa.sin_addr));
	return result != 0;
}

bool is_empty(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}

bool addNL(char * wFile)
{
	FILE *hFile = fopen(wFile, "ab");
	fseek(hFile, -1, SEEK_END);
	char cLastChar = fgetc(hFile);
	if(cLastChar != '\n')
		return true;
	return false;
}

std::string getDateFilename(void)
{
	time_t now;
	char the_date[20];
	the_date[0] = '\0';
	now = time(NULL);
	if (now != -1)
	{
		strftime(the_date, 20, "%d%m%Y_%H%M%S", gmtime(&now));
	}
	return std::string(".\\Logs\\") + std::string(the_date) + ".log";
}

std::string getTimestamp(void)
{
	time_t now;
	char the_date[20];
	the_date[0] = '\0';
	now = time(NULL);
	if (now != -1)
	{
		strftime(the_date, 20, "[%H:%M:%S] ", gmtime(&now));
	}
	return std::string(the_date);
}