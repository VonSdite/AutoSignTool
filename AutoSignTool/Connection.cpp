#include "Connection.h"
#include <cstring>
#include <stdio.h>
#include <iostream>

std::wstring ExeCmd(std::wstring pszCmd);

Connection::Connection(std::wstring szSeverName, std::wstring szPasswd, std::wstring szUserName)
{
    this->szSeverName = szSeverName;
    this->szPasswd = szPasswd;
    this->szUserName = szUserName;
}

BOOL Connection::Connect()
{
    std::wstring strCmdLine = std::wstring(L"net use ") + szSeverName + L" " + szPasswd + L" /user:" + szUserName;
    std::wstring strCmdReturn = ExeCmd(L"net use \\\\10.91.44.19\\FileServer\\usr\\wangbihong\\input ops123! /user:administrator");
    std::wcout << strCmdReturn << std::endl; 
    return TRUE;
}

void Connection::DisConnect()
{

}


std::wstring ExeCmd(std::wstring pszCmd)
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
    std::wstring strRet;
    std::string strRetTmp;
    char buff[1024] = {0};
    DWORD dwRead = 0;
    strRetTmp = buff;
    while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
    {
        strRetTmp += buff;
    }
    CloseHandle(hRead);

    int nLen = (int)strRetTmp.length();    
    strRet.resize(nLen, L' ');

    MultiByteToWideChar(CP_ACP,0,(LPCSTR)strRetTmp.c_str(),nLen,(LPWSTR)strRet.c_str(),nLen);

    return strRet;
}