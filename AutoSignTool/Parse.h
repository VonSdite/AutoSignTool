#ifndef __PARSE__
#define __PARSE__

#include <map>
#include <string>
#include <vector>
#include <Windows.h>
#include <tchar.h>

class Parse
{
public:
    static std::map<std::wstring, std::wstring> GetPair(int argc, TCHAR **argv, LPTSTR splitString);

    static std::vector<std::wstring> SplitString(const std::wstring s, const std::wstring c);

private:
    Parse() {};
    Parse(const Parse &parse) {};
};

#endif