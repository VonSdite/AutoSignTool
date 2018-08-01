#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

#include <Windows.h>
#include <tchar.h>
#include <string>

class FileManager
{
public:
     // ��������Ŀ¼, ����Ŀ¼·��
    static std::wstring CreateDateDir(std::wstring strTargetPath);       

    // �����ļ���ָ��λ��
    static BOOL CopyFileTo(
        std::wstring strExistingFileName,
        std::wstring strNewFileName,
        BOOL fFailIfExists = FALSE
    );

    static BOOL FileExist(LPCTSTR lpFilePath);

    static LPTSTR GetFileName(LPCTSTR lpPath);

    static void CreateFile(
        std::wstring strFileName,
        DWORD dwDesiredAccess = GENERIC_WRITE,
        DWORD dwShareMode = NULL,
        LPSECURITY_ATTRIBUTES lpSecurityAttributes = NULL,
        DWORD dwCreationDisposition = CREATE_ALWAYS,
        DWORD dwFlagsAndAttributes = FILE_ATTRIBUTE_NORMAL,
        HANDLE hTemplateFile = NULL);

	static std::wstring PathBackFlashRemove(std::wstring strPath);

    static void CreateDir(std::wstring strPath);

private:
    FileManager(){};
    FileManager(const FileManager &){};
};

#endif
