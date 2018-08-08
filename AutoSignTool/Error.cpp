#include "Error.h"
#include <iostream>

ErrorPrinter::ErrorPrinter()
{
}

void ErrorPrinter::Print(std::wstring strErrorInfo)
{
    std::wcout << strErrorInfo << std::endl;
    exit(-1);
}

void ErrorPrinter::PrintIniError()
{
    std::wcout << L"[Error 1] 配置文件sign_cab_config.ini有误" << std::endl;
    std::wcout << L"配置文件内容应保存在程序根目录的conf目录下,内容如下:" << std::endl 
               << std::endl;
    std::wcout << L"[config.ini]" << std::endl
        << L";登录共享文件夹的用户名(选填)" << std::endl
        << L"userName=XXX" << std::endl
        << L";登录共享文件夹的用户名对应的密码(选填)" << std::endl
        << L"password=XXX" << std::endl
        << L";签名类型" << std::endl
        << L"signType=XXX" << std::endl
        << L";签名服务器的输入目录" << std::endl
        << L"signInputFile=XXX" << std::endl
        << L";签名服务器的输出目录" << std::endl
        << L"signOutputFile=XXX" << std::endl
        << L";签名超时值(分钟为单位)" << std::endl
        << L"timeOut=5" << std::endl;
    exit(-1);
}

void ErrorPrinter::CheckIniConfig(std::tr1::shared_ptr<Ini> ini)
{
    if ( ini->m_mapInfo[L"signType"].empty()
        || ini->m_mapInfo[L"signInputFile"].empty()
        || ini->m_mapInfo[L"signOutputFile"].empty()
        || ini->m_mapInfo[L"timeOut"].empty())
    {
        PrintIniError();
    }

    if (ini->m_mapInfo[L"signInputFile"].find_last_not_of(L'/') 
        || ini->m_mapInfo[L"signInputFile"].find_last_not_of(L'\\'))
        ini->m_mapInfo[L"signInputFile"] += L"\\";

    if (ini->m_mapInfo[L"signOutputFile"].find_last_not_of(L'/')
        || ini->m_mapInfo[L"signOutputFile"].find_last_not_of(L'\\'))
        ini->m_mapInfo[L"signOutputFile"] += L"\\";
}