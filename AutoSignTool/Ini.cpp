#include "Ini.h"

BOOL Ini::WriteIni( 
                   std::wstring lpNodeName, 
                   std::wstring lpKeyName, 
                   std::wstring lpValue,
                   std::wstring lpFileName 
)
{
    return WritePrivateProfileString(lpNodeName.c_str(), lpKeyName.c_str(), lpValue.c_str(), lpFileName.c_str());
}

DWORD Ini::ReadStringFromIni(
			LPCTSTR lpAppName, 
			LPCTSTR lpKeyName, 
			LPCTSTR lpDefault, 
			LPTSTR lpReturnedString, 
			DWORD nSize, 
			LPCTSTR lpFileName
)
{
	return GetPrivateProfileString(lpAppName, lpKeyName, lpDefault, lpReturnedString, nSize, lpFileName);
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