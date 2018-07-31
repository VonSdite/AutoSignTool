#include <Windows.h>
#include <tchar.h>

#include "AutoSign.h"
#include "Ini.h"

int _tmain(int argc, TCHAR *argv[])
{
    AutoSign *autoSign = new AutoSign(argc, argv);
    autoSign->run();
    return 0;
}
