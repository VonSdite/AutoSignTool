#ifndef __CHECK__THREAD__
#define __CHECK__THREAD__

#include "Thread.h"
#include <string>

class CheckThread : public Thread
{
private:
    std::wstring szFileName1;
    std::wstring szFileName2;

    BOOL bSuccess;

    virtual void run();

public:
    CheckThread(std::wstring szFileName1, std::wstring szFileName2);
    
    BOOL isSuccess() { return bSuccess; }
};

#endif