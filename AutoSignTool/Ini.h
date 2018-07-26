#ifndef __INI__
#define __INI__

#include <tchar.h>
#include <Windows.h>
#include <string>

class Ini
{
public:
    static BOOL WriteIni( 
        std::wstring lpNodeName,  // INI�ļ��е�һ���ֶ���[����]�����кܶ������
        std::wstring lpKeyName,   // lpNodeName �µ�һ��������Ҳ�����������ı�����
        std::wstring lpValue,     // ��ֵ,Ҳ��������
        std::wstring lpFileName   // INI�ļ���·��
    );

private:
    Ini() {};
    Ini(const Ini &ini) {};
    ~Ini(){};

};

#endif