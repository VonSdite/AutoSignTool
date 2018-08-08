#include <iostream>
#include <sstream>
#include <cstring>
#include <map>

#include "FileManager.h"
#include "CheckThread.h"
#include "AutoSign.h"
#include "Parse.h"

using namespace std;

void AutoSign::run()
{
    if (m_pConnect->Connect())          // 与共享文件夹建立连接
    {
	    m_strDateDirName = FileManager::CreateDateDir(m_pIni->m_mapInfo[L"signInputFile"]);

        CreateSignIni();                // 生成签名配置文件

        UploadOk();                     // 生成upload.ok文件

        GetOutputFile();                // 获取签名成功的文件
    }
}

AutoSign::AutoSign(int argc, TCHAR **argv)
{
    m_pIni = std::tr1::shared_ptr<Ini>(new Ini());
    m_pErrorPrinter = std::tr1::shared_ptr<ErrorPrinter>(new ErrorPrinter());

    ReadFromConfig();                      // 从配置文件读取配置
    ParseArgv(argc, argv);                 // 解析命令行参数

    m_pConnect = std::tr1::shared_ptr<Connection>(new Connection(
        m_pIni->m_mapInfo[L"signInputFile"], 
        m_pIni->m_mapInfo[L"password"], 
        m_pIni->m_mapInfo[L"userName"]
        )
    );
}

AutoSign::~AutoSign()
{
}

wstring AutoSign::GetConfigPath()
{
    // 获取程序目录下config.ini的路径
    TCHAR _szPath[MAX_PATH + 1]={0};
    GetModuleFileName(NULL, _szPath, MAX_PATH);
    (_tcsrchr(_szPath, _T('\\')))[1] = 0;     
    wstring strConfigPath = _szPath;
    return strConfigPath + L"config.ini";
}

void AutoSign::ReadFromConfig()
{
    wstring strConfigPath = GetConfigPath();

    if (!FileManager::FileExist(strConfigPath.c_str()))
	{
		m_pErrorPrinter->PrintIniError();
	}

    m_pIni->ReadIni(L"config.ini", strConfigPath.c_str());  // 读取配置文件

    m_pErrorPrinter->CheckIniConfig(m_pIni);
}

void trim(std::wstring &str, TCHAR ch) 
{
    if (str.empty()) 
        return;

    str.erase(0, str.find_first_not_of(ch));
    str.erase(str.find_last_not_of(ch) + 1);
}

void AutoSign::ParseArgv(int argc, TCHAR **argv)
{
	if (argc != 3)
		m_pErrorPrinter->Print(L"[Error 4] 命令行参数个数不对");
	else
	{
		map<std::wstring, std::wstring> mp;
        mp = Parse::GetPair(argc, argv, L"=");
        if (mp.size() != 2) 
            m_pErrorPrinter->Print(L"[Error 5] 命令行参数格式不对");

        m_strOutputPath = mp[L"output"];
        if (m_strOutputPath.empty())
            m_pErrorPrinter->Print(L"[Error 6] 命令行参数缺少最终输出路径, output=XXX");

        if (m_strOutputPath[m_strOutputPath.length() - 1] != L'\\'
            || m_strOutputPath[m_strOutputPath.length() - 1] != L'/')
            m_strOutputPath += L"\\";

        m_vstrCabPath = Parse::SplitString(mp[L"cab"], L";");
        if (m_vstrCabPath.empty())
            m_pErrorPrinter->Print(L"[Error 8] 命令行参数缺少cab文件路径, cab=XXX");
        
        CheckCabPath();
	}
}

void AutoSign::CheckCabPath()
{
    BOOL fCabValid = FALSE; 
    for (size_t i = 0; i < m_vstrCabPath.size(); ++i)
    {
        if (FileManager::FileExist(m_vstrCabPath[i].c_str()))
        {
            fCabValid = TRUE;
            break;
        }
    }
    if (!fCabValid)
        m_pErrorPrinter->Print(L"[Error 9] 无有效cab文件路径");
}

void AutoSign::CreateSignIni()
{
    wstring strSignInputFile = m_pIni->m_mapInfo[L"signInputFile"] + m_strDateDirName;
    wstring strSignConfigPath = m_pIni->m_mapInfo[L"signInputFile"] + L"\\sign_config.ini";

    for (size_t i = 0; i < m_vstrCabPath.size(); ++i)
    {
        LPTSTR lpFileName = FileManager::GetFileName(m_vstrCabPath[i].c_str());
        if (FileManager::CopyFileTo(m_vstrCabPath[i], strSignInputFile + lpFileName))
        {
            m_pIni->WriteIni(
                lpFileName, L"path", 
                L"\"" + m_strDateDirName + lpFileName + L"\"", strSignConfigPath
            );
            m_pIni->WriteIni(
                lpFileName, L"sign_type", 
                L"\"" + m_pIni->m_mapInfo[L"signType"] + L"\"", strSignConfigPath
            );
        }
        else
        {
            if (!FileManager::FileExist(strSignInputFile.c_str()))
            {
                m_pErrorPrinter->Print(L"[Error 10] " + m_pIni->m_mapInfo[L"signInputFile"] + L" 签名输入文件路径有误");
            }
            wcout << m_vstrCabPath[i] + L" 文件不存在" << endl;
        }
    }
}

void AutoSign::UploadOk()
{
    // 创建upload.ok 表明签名文件上传结束
    FileManager::CreateFile(m_pIni->m_mapInfo[L"signInputFile"] + L"\\upload.ok");
}

void AutoSign::GetOutputFile()
{
    if (!FileManager::FileExist(m_pIni->m_mapInfo[L"signOutputFile"].c_str()))
        m_pErrorPrinter->Print(
            L"[Error 11] " 
            + m_pIni->m_mapInfo[L"signOutputFile"] 
            + L" 签名输出文件路径有误"
        );

    CheckThread *checkThread = new CheckThread(
        m_pIni->m_mapInfo[L"signOutputFile"] + m_strDateDirName, 
        m_pIni->m_mapInfo[L"signOutputFile"] + m_strDateDirName + L"文件正确.txt"
    );
    
    wcout << L"正在签名\n等待";
    std::wistringstream ss(m_pIni->m_mapInfo[L"timeOut"]);
    DWORD dwTimeOut;
    ss >> dwTimeOut;
    checkThread->start(dwTimeOut * 60 * 1000);

    if (checkThread->isSuccess())
    {
        CopyToOutputPath();
		wcout << L"\n[Successful] 签名成功\n";
    }
    else 
    {
		m_pErrorPrinter->Print(L"\n[Error 3] 签名失败, 请重试");
    }

    delete checkThread;
}

void AutoSign::CopyToOutputPath()
{
    if (!FileManager::FileExist(m_strOutputPath.c_str()))
    {
        FileManager::CreateDir(m_strOutputPath);
    }

    for (size_t i = 0; i < m_vstrCabPath.size(); ++i)
    {
        LPTSTR lpFileName = FileManager::GetFileName(m_vstrCabPath[i].c_str());
        FileManager::CopyFileTo(
            m_pIni->m_mapInfo[L"signOutputFile"] + m_strDateDirName + lpFileName, 
            m_strOutputPath + lpFileName
            );
    }
}