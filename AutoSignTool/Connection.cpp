#include "Connection.h"
#include "FileManager.h"
#include <cstring>
#include <stdio.h>
#include <locale.h>
#include <iostream>

std::wstring ExeCmd(std::wstring pszCmd);

Connection::Connection(std::wstring szSeverName, std::wstring szPasswd, std::wstring szUserName)
{
	szSeverName = FileManager::PathBackFlashRemove(szSeverName);
    this->szSeverName = szSeverName;
    this->szPasswd = szPasswd;
    this->szUserName = szUserName;
}

BOOL Connection::Connect()
{
    std::wstring strCmdLine = std::wstring(L"net use ") + szSeverName + L" " + szPasswd + L" /user:" + szUserName;
    std::wstring strCmdReturn = ExeCmd(strCmdLine);
	
	std::wcout.imbue(std::locale("chs"));
    if (strCmdReturn.substr(0, 11) == L"����ϵͳ���� 1219") 
    {

    }
	else if (strCmdReturn.substr(0, 6) == L"����ϵͳ����")
    {
		std::wcout << L"[Error 2] �����ļ�������ʧ��\n" << strCmdReturn << std::endl; 
        return FALSE;
    }
    return TRUE;
}

void Connection::DisConnect()
{
	std::wstring strCmdLine = std::wstring(L"net use ") + szSeverName + L" /d /y";
	ExeCmd(strCmdLine);
}


std::wstring Connection::ExeCmd(std::wstring pszCmd)
{
    // ���������ܵ�
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0))
    {
        return TEXT(" ");
    }

    // ���������н���������Ϣ(�����ط�ʽ���������λ�������hWrite
    STARTUPINFO si = {sizeof(STARTUPINFO)};
    GetStartupInfo(&si);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdError = hWrite;
    si.hStdOutput = hWrite;

    // ����������
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, (LPWSTR)pszCmd.c_str(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
    {
        return TEXT("Cannot create process");
    }

    // �����ر�hWrite
    CloseHandle(hWrite);

    // ��ȡ�����з���ֵ
    std::string strRetTmp;
    char buff[1024] = {0};
    DWORD dwRead = 0;
    strRetTmp = buff;
    while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
    {
        strRetTmp += buff;
    }
    CloseHandle(hRead);

    size_t i;
    std::string curLocale = setlocale(LC_ALL, NULL);
    setlocale(LC_ALL, "chs");
    const char* _source = strRetTmp.c_str();
    size_t _dsize = strRetTmp.size() + 1;
    wchar_t* _dest = new wchar_t[_dsize];
    wmemset(_dest, 0x0, _dsize);
    mbstowcs_s(&i, _dest, _dsize, _source, _dsize);
    std::wstring strRet = _dest;
    delete[] _dest;
    setlocale(LC_ALL, curLocale.c_str());

	return strRet;
}