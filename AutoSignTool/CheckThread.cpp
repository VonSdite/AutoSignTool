#include "CheckThread.h"
#include "FileManager.h"
#include <stdio.h>

CheckThread::CheckThread(std::wstring szFileName1, std::wstring szFileName2)  
{  
    this->szFileName1 = szFileName1;
    this->szFileName2 = szFileName2;
    this->bSuccess = FALSE;
}  

void CheckThread::run()
{
    while (!FileManager::FileExist(szFileName1.c_str()))
    {
        _tprintf(L".");
        Sleep(3000);
    }

    if (!FileManager::FileExist(szFileName2.c_str()))
    {
        return ;
    }
    
    this->bSuccess = TRUE;
}