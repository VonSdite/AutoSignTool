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