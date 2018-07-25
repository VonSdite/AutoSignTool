#include "FileManager.h"
#include <iostream>

using namespace std;


int _tmain(int argc, TCHAR const *argv[])
{
    wcout << FileManager::CreateDateDir(TEXT("\\\\10.91.44.19\\FileServer\\usr\\wangbihong\\input")) << endl;
    return 0;
}
