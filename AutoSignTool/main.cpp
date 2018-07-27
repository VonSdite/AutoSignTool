#include <Windows.h>
#include <tchar.h>

#include "AutoSign.h"

int _tmain(int argc, TCHAR const *argv[])
{
    AutoSign *autoSign = new AutoSign(argc, argv);
    autoSign->run();
    return 0;
}
