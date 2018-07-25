#include "FileManager.h"
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <strsafe.h>

PCTSTR FileManager::CreateDateDir(PCTSTR targetPath)
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
    PTSTR dirName = (PTSTR)malloc(sizeof(TCHAR)*100);
    memset(dirName, 0, sizeof(dirName));
    swprintf_s(
        dirName, 
        100,
        TEXT("ENTSign_%d%02d%02d_%03d%04x%04x\\\0"), 
        localTime.wYear, 
        localTime.wMonth, 
        localTime.wDay,
        localTime.wMilliseconds,
        rand() % 0x10000,
        rand() % 0x10000
    );

    // 在指定路径创建文件夹
    TCHAR dir[361];
    swprintf_s(
        dir,
        361,
        TEXT("%s\\%s"),
        targetPath,
        dirName
    );
    CreateDirectory(dir, NULL);

    return dirName;
}

