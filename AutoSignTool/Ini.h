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

	static DWORD ReadStringFromIni(
		LPCTSTR lpAppName,           // ����
		LPCTSTR lpKeyName,           // ��������ȡ�ü���ֵ
		LPCTSTR lpDefault,       // ��ָ���ļ������ڣ���ֵ��Ϊ��ȡ��Ĭ��ֵ
		LPTSTR lpReturnedString,     // һ��ָ�򻺳�����ָ�룬���ն�ȡ���ַ���
		DWORD nSize,                 // ָ��lpReturnedStringָ��Ļ������Ĵ�С
		LPCTSTR lpFileName
	);

	static UINT ReadIntFromIni(
		LPCTSTR lpAppName,     // ͬ��
		LPCTSTR lpKeyName,     // ͬ��
		INT nDefault,          // ��ָ���ļ��������ڣ���ֵ��Ϊ��ȡ��Ĭ��ֵ
		LPCTSTR lpFileName
	);

private:
    Ini() {};
    Ini(const Ini &ini) {};
    ~Ini(){};

};

#endif