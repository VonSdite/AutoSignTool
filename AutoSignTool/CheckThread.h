#ifndef __THREAD__
#define __THREAD__

#include <process.h>
#include <Windows.h>
#include <tchar.h>

class CheckThread 
{  
private:
    std::wstring szFileName1;
    std::wstring szFileName2;

public:  

    CheckThread(std::wstring szFileName1, std::wstring szFileName2);

    static unsigned __stdcall start(void * pThis);

    void run();
};  

#endif