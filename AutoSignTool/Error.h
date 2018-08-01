#ifndef __ERROR__
#define __ERROR__

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <map>

#include "Ini.h"

class ErrorPrinter
{
public:
    void Print(std::wstring strErrorInfo);
    void PrintIniError();
    void CheckIniConfig(std::tr1::shared_ptr<Ini> ini);

    ErrorPrinter();
};

#endif