#include "FileManager.h"
#include <stdlib.h>
#include <time.h>
#include <strsafe.h>
#include <sstream>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib") 

std::wstring FileManager::CreateDateDir(const std::wstring szTargetPath)
{
    // 设置随机数种子
    static BOOL isSetRand = FALSE;
    if (!isSetRand) 
    {
        srand((DWORD)time(NULL));
    }

    // 获取系统时间
    SYSTEMTIME localTime; 
    GetLocalTime(&localTime);

    // 要创建的目录名
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

    // 在指定路径创建文件夹
    std::wstring szDir = szTargetPath + szDirName;
   
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
	/*WIN32_FIND_DATA wfd;
	HANDLE hFind = FindFirstFile(lpFilePath, &wfd);
	return (hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);*/
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