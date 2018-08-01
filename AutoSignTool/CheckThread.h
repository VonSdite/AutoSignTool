#ifndef __CHECK__THREAD__
#define __CHECK__THREAD__

#include "Thread.h"
#include <string>

class CheckThread : public Thread
{
private:
    std::wstring m_strFileName1;
    std::wstring m_strFileName2;

    BOOL m_fSuccess;

    virtual void run();

public:
    CheckThread(std::wstring strFileName1, std::wstring strFileName2);
    
    BOOL isSuccess() { return m_fSuccess; }
};

#endif