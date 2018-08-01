#include "CheckThread.h"
#include "FileManager.h"
#include <stdio.h>

CheckThread::CheckThread(std::wstring strFileName1, std::wstring strFileName2)  
{  
    this->m_strFileName1 = strFileName1;
    this->m_strFileName2 = strFileName2;
    this->m_fSuccess = FALSE;
}  

void CheckThread::run()
{
    while (!FileManager::FileExist(m_strFileName1.c_str()))
    {
        _tprintf(L".");
        Sleep(3000);
    }

    if (!FileManager::FileExist(m_strFileName2.c_str()))
    {
        return ;
    }
    
    this->m_fSuccess = TRUE;
}