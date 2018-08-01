#include "Ini.h"
#include <string.h>

BOOL Ini::WriteIni( 
                   std::wstring strNodeName, 
                   std::wstring strKeyName, 
                   std::wstring strValue,
                   std::wstring strFileName 
)
{
    return WritePrivateProfileString(strNodeName.c_str(), strKeyName.c_str(), strValue.c_str(), strFileName.c_str());
}

std::map<std::wstring, std::wstring>& Ini::ReadIni(LPCTSTR lpAppName, LPCTSTR lpFileName)
{
    TCHAR szReturnedString[32767];
    DWORD dwSize = 32767;
    DWORD dwRet = GetPrivateProfileSection(lpAppName, szReturnedString, dwSize, lpFileName);

    LPTSTR lpReturnedString = szReturnedString;
    int len = _tcslen(lpReturnedString);
    while (len)
    {
        std::wstring str = lpReturnedString;
        std::wstring::size_type pos;

        pos = str.find(L"=");

        m_mapInfo[str.substr(0, pos)] = str.substr(pos+1);
        lpReturnedString += str.size() + 1;
        len = _tcslen(lpReturnedString);
    }
    return m_mapInfo;
}

DWORD Ini::ReadStringFromIni(
			LPCTSTR lpAppName, 
			LPCTSTR lpKeyName, 
			LPCTSTR lpDefault, 
			LPTSTR lpReturnedString, 
			DWORD dwSize, 
			LPCTSTR lpFileName
)
{
	return GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, lpReturnedString, dwSize, lpFileName);
}

UINT Ini::ReadIntFromIni( 
			LPCTSTR lpAppName, 
			LPCTSTR lpKeyName, 
			INT nDefault, 
			LPCTSTR lpFileName 
)
{
	return GetPrivateProfileInt(lpAppName, lpKeyName, nDefault, lpFileName);
}