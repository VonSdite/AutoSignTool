#include "FileManager.h"
#include <stdlib.h>
#include <time.h>
#include <strsafe.h>
#include <stdio.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib") 

std::wstring FileManager::CreateDateDir(const std::wstring szTargetPath)
{
    // 设置随机数种子
    static BOOL fSetRand = FALSE;
    if (!fSetRand) 
    {
        srand((DWORD)time(NULL));
    }

    // 获取系统时间
    SYSTEMTIME localTime; 
    GetLocalTime(&localTime);

    // 要创建的目录名
    TCHAR szDirName[200] = {0};
    swprintf_s(szDirName, 200, L"ENTSign_%d%02d%02d_%03d%04x%04x\\", 
        localTime.wYear, localTime.wMonth, 
        localTime.wDay, localTime.wMilliseconds, 
        rand() % 0x10000, rand() % 0x10000);
    std::wstring strDirName = szDirName;

    // 在指定路径创建文件夹
    std::wstring szDir = szTargetPath + strDirName;
   
    CreateDirectory(szDir.c_str(), NULL);

    return strDirName;
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
     HANDLE hWnd = ::CreateFile(        
        lpFileName.c_str(),
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile
    );
    CloseHandle(hWnd);
}

std::wstring FileManager::PathBackFlashRemove(std::wstring path)
{
	if (path.empty()) return path;
	path.erase(path.find_last_not_of(L'\\') + 1);
	path.erase(path.find_last_not_of(L'/') + 1);
	return path;
}

void FileManager::CreateDir(std::wstring path)
{
    std::wstring cmd = std::wstring(L"md ") + path;
    _tsystem(cmd.c_str());
}