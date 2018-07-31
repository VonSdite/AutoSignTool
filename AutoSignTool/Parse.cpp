#include "Parse.h"
#include <string.h>
#include <stdlib.h>

std::vector<std::wstring> Parse::SplitString(const std::wstring s, const std::wstring c)
{
    std::vector<std::wstring> v;
    std::wstring::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::wstring::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
    return v;
}


std::map<std::wstring, std::wstring> Parse::GetPair(int argc, TCHAR **argv, LPTSTR splitString)
{
    std::map<std::wstring, std::wstring> mp;
    for (int i = 1; i < argc; ++i)
    {
        std::vector<std::wstring> tmp = SplitString(argv[i], splitString);
        if (tmp.size() != 2)
        {
            continue;
        }
        mp[tmp[0]] = tmp[1];
    }
    return mp;
}