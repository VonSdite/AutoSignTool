#include "FileManager.h"
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <strsafe.h>

PCTSTR FileManager::CreateDateDir(PCTSTR targetPath)
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

    // ��ָ��·�������ļ���
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

