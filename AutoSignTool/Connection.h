#ifndef __CONNECTION__
#define __CONNECTION__

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <WinNetWk.h>

#pragma comment(lib, "Mpr.lib")

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
    NETRESOURCE netResource;

};

#endif