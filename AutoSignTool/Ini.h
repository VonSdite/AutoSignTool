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

private:
    Ini() {};
    Ini(const Ini &ini) {};
    ~Ini(){};

};

#endif