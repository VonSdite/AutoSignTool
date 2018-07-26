#include "CheckThread.h"

#include <wstring>
#include "FileManager.h"

CheckThread::CheckThread(std::wstring szFileName1, std::wstring szFileName2)  
{  
    this->szFileName1 = szFileName1;
    this->szFileName2 = szFileName2;
}  

static unsigned __stdcall CheckThread::start(void * pThis)  
{  
    CheckThread * pthX = (CheckThread*)pThis;  
    pthX->run();           
    return 1;                           
}  

void CheckThread::run()
{
    while (!FileManager::FileExist(szFileName1))
    {
        _tprintf(L".");
        Sleep(5000);
    }

    if (!FileManager::FileExist((szFileName2)))
    {

    }
}