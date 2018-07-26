#include "Connection.h"
#include <cstring>
#include <stdio.h>

Connection::Connection(std::wstring szSeverName, std::wstring szPasswd, std::wstring szUserName)
{
    this->szSeverName = szSeverName;
    this->szPasswd = szPasswd;
    this->szUserName = szUserName;

    memset(&netResource, 0, sizeof(netResource));
    
}

BOOL Connection::Connect()
{
    netResource.dwDisplayType = RESOURCEDISPLAYTYPE_DIRECTORY;
    netResource.dwScope = RESOURCE_CONNECTED;
    netResource.dwType = RESOURCETYPE_ANY;
    netResource.dwUsage = 0;
    netResource.lpComment = TEXT("");
    netResource.lpLocalName = TEXT("Z:");                  // 映射成本地驱动器Z:
    netResource.lpProvider= NULL;
    netResource.lpRemoteName = (LPWSTR)szSeverName.c_str();  // \\servername\共享资源名

    DWORD dwFlags = CONNECT_UPDATE_PROFILE;
    DWORD dw = WNetAddConnection2(&netResource, szPasswd.c_str(), szUserName.c_str(), dwFlags);

    if (dw == ERROR_SESSION_CREDENTIAL_CONFLICT)
    {
        return TRUE;
    }
    else if(dw != NO_ERROR)
    {
        _tprintf(TEXT("[Error] The password or the user name for the login shared folder is incorrect.\nOr shared resource folder path is incorrect.\n"));
        DisConnect();
        return FALSE;
    }
    
    return TRUE;
}

void Connection::DisConnect()
{
    //断开共享连接
    WNetCancelConnection2(netResource.lpLocalName, CONNECT_UPDATE_PROFILE, true);
    WNetCancelConnection2(netResource.lpRemoteName, CONNECT_UPDATE_PROFILE, true);
}