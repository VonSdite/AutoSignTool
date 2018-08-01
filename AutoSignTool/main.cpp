#include <Windows.h>
#include <tchar.h>
#include <iostream>

#include "AutoSign.h"
#include "Ini.h"

int _tmain(int argc, TCHAR *argv[])
{
    std::wcout.imbue(std::locale("chs"));	

    AutoSign *autoSign = new AutoSign(argc, argv);
    autoSign->run();
    return 0;
}
