#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

#include <Windows.h>
#include <tchar.h>

class FileManager
{
public:
    static PCTSTR CreateDateDir(PCTSTR targetPath);        // ��������Ŀ¼, ����Ŀ¼·��
private:
    FileManager(){};
    ~FileManager(){};
};

#endif
