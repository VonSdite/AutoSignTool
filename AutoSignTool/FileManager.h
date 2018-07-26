#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

#include <Windows.h>
#include <tchar.h>
#include <string>

class FileManager
{
public:
     // ��������Ŀ¼, ����Ŀ¼·��
    static std::wstring CreateDateDir(std::wstring szTargetPath);       

    // �����ļ���ָ��λ��
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
