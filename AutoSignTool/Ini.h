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
         std::wstring strNodeName,   // INI�ļ�[����]
         std::wstring strKeyName,    // ����
         std::wstring strValue,      // ��ֵ
         std::wstring strFileName    // INI�ļ���·��
    );

     std::map<std::wstring, std::wstring>& ReadIni(
         LPCTSTR lpAppName,         // INI�ļ�[����]
         LPCTSTR lpFileName         // INI�ļ���·��
     );

	 DWORD ReadStringFromIni(
		LPCTSTR lpAppName,           // ����
		LPCTSTR lpKeyName,           // ��������ȡ�ü���ֵ
		LPCTSTR lpDefault,           // ��ָ���ļ������ڣ���ֵ��Ϊ��ȡ��Ĭ��ֵ
		LPTSTR lpReturnedString,     // һ��ָ�򻺳�����ָ�룬���ն�ȡ���ַ���
		DWORD dwSize,                 // ָ��lpReturnedStringָ��Ļ������Ĵ�С
		LPCTSTR lpFileName
	);

	 UINT ReadIntFromIni(
		LPCTSTR lpAppName,          // ͬ��
		LPCTSTR lpKeyName,          // ͬ��
		INT nDefault,               // ��ָ���ļ��������ڣ���ֵ��Ϊ��ȡ��Ĭ��ֵ
		LPCTSTR lpFileName
	);

    std::map<std::wstring, std::wstring> m_mapInfo;
};

#endif