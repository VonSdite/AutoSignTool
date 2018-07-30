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
	if (strCmdReturn.substr(0, 6) == L"发生系统错误")
		std::wcout << strCmdReturn << std::endl; 
    return TRUE;
}

void Connection::DisConnect()
{
	std::wstring strCmdLine = std::wstring(L"net use ") + szSeverName + L" /d /y";
	ExeCmd(strCmdLine);
}


std::wstring Connection::ExeCmd(std::wstring pszCmd)
{
    // 创建匿名管道
    SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};
    HANDLE hRead, hWrite;
    if (!CreatePipe(&hRead, &hWrite, &sa, 0))
    {
        return TEXT(" ");
    }

    // 设置命令行进程启动信息(以隐藏方式启动命令并定位其输出到hWrite
    STARTUPINFO si = {sizeof(STARTUPINFO)};
    GetStartupInfo(&si);
    si.dwFlags = STARTF_USESHOWWINDOW | STARTF_USESTDHANDLES;
    si.wShowWindow = SW_HIDE;
    si.hStdError = hWrite;
    si.hStdOutput = hWrite;

    // 启动命令行
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, (LPWSTR)pszCmd.c_str(), NULL, NULL, TRUE, NULL, NULL, NULL, &si, &pi))
    {
        return TEXT("Cannot create process");
    }

    // 立即关闭hWrite
    CloseHandle(hWrite);

    // 读取命令行返回值
    std::string strRetTmp;
    char buff[1024] = {0};
    DWORD dwRead = 0;
    strRetTmp = buff;
    while (ReadFile(hRead, buff, 1024, &dwRead, NULL))
    {
        strRetTmp += buff;
    }
    CloseHandle(hRead);

	LPCSTR pszSrc = strRetTmp.c_str();
	int nLen = MultiByteToWideChar(CP_ACP, 0, buff, -1, NULL, 0);
	if (nLen == 0) 
		return std::wstring(L"");

	wchar_t* pwszDst = new wchar_t[nLen];
	if (!pwszDst) 
		return std::wstring(L"");

	MultiByteToWideChar(CP_ACP, 0, pszSrc, -1, pwszDst, nLen);
	std::wstring strRet(pwszDst);
	delete[] pwszDst;
	pwszDst = NULL;

	return strRet;
}