#ifndef __FILE_MANAGER__
#define __FILE_MANAGER__

#include <Windows.h>
#include <tchar.h>

class FileManager
{
public:
    static PCTSTR CreateDateDir(PCTSTR targetPath);        // 创建日期目录, 返回目录路径
private:
    FileManager(){};
    ~FileManager(){};
};

#endif
