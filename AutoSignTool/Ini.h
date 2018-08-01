#ifndef __INI__
#define __INI__

#include <tchar.h>
#include <Windows.h>
#include <string>
#include <map>

class Ini
{
public:
     BOOL WriteIni( 
         std::wstring strNodeName,   // INI文件[节名]
         std::wstring strKeyName,    // 键名
         std::wstring strValue,      // 键值
         std::wstring strFileName    // INI文件的路径
    );

     std::map<std::wstring, std::wstring>& ReadIni(
         LPCTSTR lpAppName,         // INI文件[节名]
         LPCTSTR lpFileName         // INI文件的路径
     );

	 DWORD ReadStringFromIni(
		LPCTSTR lpAppName,           // 节名
		LPCTSTR lpKeyName,           // 键名，读取该键的值
		LPCTSTR lpDefault,           // 若指定的键不存在，该值作为读取的默认值
		LPTSTR lpReturnedString,     // 一个指向缓冲区的指针，接收读取的字符串
		DWORD dwSize,                 // 指定lpReturnedString指向的缓冲区的大小
		LPCTSTR lpFileName
	);

	 UINT ReadIntFromIni(
		LPCTSTR lpAppName,          // 同上
		LPCTSTR lpKeyName,          // 同上
		INT nDefault,               // 若指定的键名不存在，该值作为读取的默认值
		LPCTSTR lpFileName
	);

    std::map<std::wstring, std::wstring> m_mapInfo;
};

#endif