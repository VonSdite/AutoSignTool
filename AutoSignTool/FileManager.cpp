#include "FileManager.h"
#include <stdlib.h>
#include <time.h>
#include <strsafe.h>
#include <sstream>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib") 

std::wstring FileManager::CreateDateDir(const std::wstring szTargetPath)
{
    // �������������
    static BOOL isSetRand = FALSE;
    if (!isSetRand) 
    {
        srand((DWORD)time(NULL));
    }

    // ��ȡϵͳʱ��
    SYSTEMTIME localTime; 
    GetLocalTime(&localTime);

    // Ҫ������Ŀ¼��
    std::wstringstream ss;
    ss << L"ENTSign_" 
        << localTime.wYear
        << localTime.wMonth
        << localTime.wDay
        << localTime.wMilliseconds
        << L"_"
        << rand() % 0x10000
        << rand() % 0x10000
        << L"\\";
    std::wstring szDirName = ss.str();

    // ��ָ��·�������ļ���
    std::wstring szDir = szTargetPath + L"\\" + szDirName;
   
    CreateDirectory(szDir.c_str(), NULL);

    return szDirName;
}

BOOL FileManager::CopyFileTo( 
         std::wstring lpExistingFileName, 
         std::wstring lpNewFileName, 
         BOOL bFailIfExists
)
{
    return CopyFile(lpExistingFileName.c_str(), lpNewFileName.c_str(), bFailIfExists);
}

BOOL FileManager::FileExist(LPCTSTR lpFilePath)
{
    return PathFileExists(lpFilePath);
}

LPTSTR FileManager::GetFileName(LPCTSTR lpPath)
{
    return PathFindFileName(lpPath);
}

void FileManager::CreateFile(
     std::wstring lpFileName, 
     DWORD dwDesiredAccess /* = GENERIC_WRITE */, 
     DWORD dwShareMode /* = NULL */, 
     LPSECURITY_ATTRIBUTES lpSecurityAttributes /* = NULL */, 
     DWORD dwCreationDisposition /* = CREATE_ALWAYS */, 
     DWORD dwFlagsAndAttributes /* = FILE_ATTRIBUTE_NORMAL */, 
     HANDLE hTemplateFile /* = NULL */
)
{
    ::CreateFile(        
        lpFileName.c_str(),
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile
    );
}