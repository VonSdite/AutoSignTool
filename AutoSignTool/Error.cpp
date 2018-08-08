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
    std::wcout << L"[Error 1] �����ļ�sign_cab_config.ini����" << std::endl;
    std::wcout << L"�����ļ�����Ӧ�����ڳ����Ŀ¼��confĿ¼��,��������:" << std::endl 
               << std::endl;
    std::wcout << L"[config.ini]" << std::endl
        << L";��¼�����ļ��е��û���(ѡ��)" << std::endl
        << L"userName=XXX" << std::endl
        << L";��¼�����ļ��е��û�����Ӧ������(ѡ��)" << std::endl
        << L"password=XXX" << std::endl
        << L";ǩ������" << std::endl
        << L"signType=XXX" << std::endl
        << L";ǩ��������������Ŀ¼" << std::endl
        << L"signInputFile=XXX" << std::endl
        << L";ǩ�������������Ŀ¼" << std::endl
        << L"signOutputFile=XXX" << std::endl
        << L";ǩ����ʱֵ(����Ϊ��λ)" << std::endl
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