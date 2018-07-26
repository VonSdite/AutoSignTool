#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

#include <Windows.h>
#include <tchar.h>
#include <string>

class FileManager
{
public:
     // 创建日期目录, 返回目录路径
    static std::wstring CreateDateDir(std::wstring szTargetPath);       

    // 拷贝文件到指定位置
    static BOOL CopyFileTo(
        std::wstring lpExistingFileName,
        std::wstring lpNewFileName,
        BOOL    bFailIfExists = FALSE
    );

    static BOOL FileExist(LPCTSTR lpFilePath);

    static LPTSTR GetFileName(LPCTSTR lpPath);

    static void CreateFile(
        std::wstring lpFileName,
        DWORD dwDesiredAccess = GENERIC_WRITE,
        DWORD dwShareMode = NULL,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL,
        DWORD dwCreationDisposition = CREATE_ALWAYS,
        DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
        HANDLE hTemplateFile = NULL);

private:
    FileManager(){};
    FileManager(const FileManager &){};
    ~FileManager(){};
};

#endif
