#ifndef __CONNECTION__
#define __CONNECTION__

#include <Windows.h>
#include <tchar.h>
#include <string>

class Connection
{
public:
    Connection(std::wstring severName, std::wstring passwd, std::wstring userName);

    BOOL Connect();
    void DisConnect();

private:
    std::wstring szSeverName;
    std::wstring szPasswd;
    std::wstring szUserName;

	std::wstring ExeCmd(std::wstring strCmdLine);

};

#endif