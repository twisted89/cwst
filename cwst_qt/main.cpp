#include "cwst_qt.h"
#include <QtWidgets/QApplication>
#include <windows.h>
#include <QtPlugin>
Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin);

int main()
{
	int argc = 0;
	char *argv[1];
	QApplication a(argc, argv);
	cwst_qt w;
	w.show();
	a.exec();
	exit(0);
}

BOOL WINAPI DllMain(HINSTANCE hInstance,DWORD dwReason,LPVOID)
{
	switch(dwReason)
	{
	case DLL_PROCESS_ATTACH:
		{
			DisableThreadLibraryCalls(hInstance);
			SECURITY_ATTRIBUTES SCAttrib; // Create main thread
			SCAttrib.bInheritHandle = NULL;
			SCAttrib.lpSecurityDescriptor = NULL;
			SCAttrib.nLength = sizeof(SCAttrib);
			if(!CreateThread(&SCAttrib, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL)) // CREATE THREAD
				return false;
		}
		break;
	case DLL_PROCESS_DETACH:
		break;
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return true;
}