#ifndef __CONNECTION__
#define __CONNECTION__

#include <Windows.h>
#include <tchar.h>
#include <string>

class Connection
{
public:
    Connection(std::wstring strSeverName, std::wstring strPasswd, std::wstring strUserName);
    BOOL Connect();

    void DisConnect();

private:
    std::wstring m_strSeverName;
    std::wstring m_strPasswd;
    std::wstring m_strUserName;

	std::wstring ExeCmd(std::wstring strCmdLine);
    
};

#endif