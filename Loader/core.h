#ifndef CORE_H
#define CORE_H
#include <windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <libloaderapi.h>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")
#include <QThread>
#include "tchar.h"
#include <memory>
#include <type_traits>
#include <QVector>
#include <QString>
#include <QProcess>
#include <QDir>
#include <Psapi.h>
#include <fileapi.h>
#include <io.h>
#include <WinBase.h>
#include <QDateTime>
#include <QEventLoop>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkInterface>
#include <QUrlQuery>
#include <winnt.h>
#include "Injection.h"

class config {


public:
     //MAIN/////////////////////////////////////////////////////////////
     bool ProtectAgainStart = true;//protection against starting the program while the copy of the program is running
     //UPDATE/////////////////////////////////////////////////////////////
     QString version = "1.0.0";//current version of the loader
     bool ShowUpdateWindow = false;//show update window, if not then auto-update occurs in the background
     bool AutoUpdateDisable = false;//Disable auto-update
     QString UrlToVersionFile = "";//link to the root folder where the version is displayed
     QString UrlToUpdatedFile = "";//link to updated file
     //LogIn TAB/////////////////////////////////////////////////////////////
     QString UrlToCheckLisencePHP = "";
     bool UsingKeySystem = false;//key system
     bool HideKeyField = true;//Hide key field after entering it|Only if the key system is active
     //-----/////////////////////////////////////////////////////////////



};

namespace core {
enum RequestMethod
{
    POST,
    GET
};
QString MD5Hash(QString file);
void ShowMessageBox(HWND hhh, QString Text, QString Title, int nButtons = MB_OK | MB_ICONERROR);
bool ProcessIsRun(QString processname);
bool WindowSearchW(QString windowname);
bool WindowSearch(const char * str);
bool WindowSearchС(QString _classname);
QString Request(RequestMethod requestMethod, QString url, QStringList value);
 QString GETRequest(QString url);
 QString GetRandomString();
 QString POSTRequest(QString url, QStringList key, QStringList value);
QString stringEncrypt(QString strInput, QString strPassword);
QString stringDecrypt(QString strInput, QString strPassword);
HWND findwind(const char * str);
void resource_extract(QString resource_way , QString savefile);
DWORD FindProcessId(QString processName);
bool InjectDll(QString _pName, QString _dllPath);
std::string string_to_hex(const std::string& in);
void encryptionFunc(std::string& nString, DWORD key);
}



#endif // CORE_H
