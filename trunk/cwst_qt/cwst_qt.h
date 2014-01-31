#ifndef CWST_QT_H
#define CWST_QT_H

#include <Winsock2.h>
#include <ws2tcpip.h>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QScrollBar>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QTableWidget>
#include <QTreeWidget>
#include <QVector>
#include <QLabel>
#include <QList>
#include "ui_cwst_qt.h"
#include <windows.h>
#include <detours.h>
#include <string>
#include <boost/thread.hpp>
#include <boost/algorithm/string.hpp>
#include <QWindow>
#include <QAbstractEventDispatcher>
#include <QtGui/5.1.0/QtGui/qpa/qplatformnativeinterface.h>
#include "INI/IniReader.h"
#include "INI/IniWriter.h"
#include "Connection.h"
#include <zlib.h>
#include <sstream>
#include <psapi.h>
#include <TlHelp32.h>
#include <fstream>
#include <QElapsedTimer>
#include "PlayerProfile.h"
#include "BinaryReader.h"
#include <boost/lexical_cast.hpp>


class cwst_qt : public QMainWindow
{
	Q_OBJECT
public: //vars
	bool autorestart;
	HWND hwndDlg;
	int MaxPublicPlayers;
	int MaxPrivatePlayers;
	int MaxLevel;
	bool UsePublicFirst;
	bool RunWebInterface;
	bool LoggingEnabled;
	bool MaxPlayers;
	bool RangerSkillFix;
	bool DisconnectFix;
	bool InnResetFix;
	bool AlwaysDaytime;
	HANDLE daylightthread;
	QElapsedTimer * uptime;
	std::vector<std::string> BlacklistArray;
	std::vector<std::string> PrivateIPArray;
	std::list<Connection*> PublicConnectionsList;
	std::list<Connection*> PrivateConnectionsList;
	Ui::cwst_qtClass ui;
	QLabel * statuslabel;
	QLabel * uptimelabel;
	cwst_qt(QWidget *parent = 0);
	~cwst_qt();
	void cwst_qt::AddPlayer(QString username, QString IPaddress);
	void cwst_qt::Addusername(QString Socket, QString username);
	void cwst_qt::removerowIP(QString IP);
	void cwst_qt::removerowSocket(QString IP);
private:
	QStandardItemModel model;
	QStringList horizontalHeader;
	HANDLE hChildProcess;
	DWORD procID;
	QMenu * context;
	QAction * Ban;
	QAction * Kick;
	QAction * Details;
	QAction *a;
	void cwst_qt::InitialSetup();
	void cwst_qt::ReadSettings();
	private slots:
		void contextMenuEvent(const QPoint &pos);
		void Exit();
		void PrivateSlotsChanged(int max);
		void PublicSlotsChanged(int max);
		void MaxLevelChanged(int max);
		void MaxLevelCheckChanged(bool checked);
		void showBansForm();
		void showPrivateIpsForm();
		void maxPchanged(bool checked);
		void usepubfirstchanged(bool checked);
		void alwaysDaylight(bool checked);
protected:
	void closeEvent(QCloseEvent *event);
};

//Prototypes
DWORD SearchPattern	(char* chPattern,DWORD dwFrom ,DWORD dwTo);
bool validateIpAddress(const std::string ipAddress);
LPVOID MemCpyEx (LPVOID lpDestination, LPVOID lpSource, int nLen);
bool fexists(const char *filename);
bool is_empty(std::ifstream& pFile);
bool addNL(char * wFile);
std::string getDateFilename(void);
std::string getTimestamp(void);
void SetupDetours();
__declspec(dllexport) void DetourAndErrorCheck(PVOID* pFunctionToDetour, PVOID pReplacement, const char* functionName);
void CheckAndDetach(PVOID* pDetouredFunction, PVOID pReplacement, const char* functionName);

void setupFixes();
void SetMaxPlayers(BYTE MAX_PLAYER);

void AddLog(char * logstring);
void AddLog(QString logstring);
void kickPlayer(int Socket);
void banPlayer(int socket, QString IP);
void StatusUpdate();
void DaylightThread();
bool validateIpAddress(const std::string ipAddress);
//

#endif // CWST_QT_H
