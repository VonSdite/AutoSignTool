#ifndef __INI__
#define __INI__

#include <tchar.h>
#include <Windows.h>
#include <string>

class Ini
{
public:
    static BOOL WriteIni( 
        std::wstring lpNodeName,  // INI文件中的一个字段名[节名]可以有很多个节名
        std::wstring lpKeyName,   // lpNodeName 下的一个键名，也就是里面具体的变量名
        std::wstring lpValue,     // 键值,也就是数据
        std::wstring lpFileName   // INI文件的路径
    );

	static DWORD ReadStringFromIni(
		LPCTSTR lpAppName,           // 节名
		LPCTSTR lpKeyName,           // 键名，读取该键的值
		LPCTSTR lpDefault,       // 若指定的键不存在，该值作为读取的默认值
		LPTSTR lpReturnedString,     // 一个指向缓冲区的指针，接收读取的字符串
		DWORD nSize,                 // 指定lpReturnedString指向的缓冲区的大小
		LPCTSTR lpFileName
	);

	static UINT ReadIntFromIni(
		LPCTSTR lpAppName,     // 同上
		LPCTSTR lpKeyName,     // 同上
		INT nDefault,          // 若指定的键名不存在，该值作为读取的默认值
		LPCTSTR lpFileName
	);

private:
    Ini() {};
    Ini(const Ini &ini) {};
    ~Ini(){};

};

#endif