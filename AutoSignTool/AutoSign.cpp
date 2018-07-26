#include <iostream>
#include <stdio.h>
#include <process.h>

#include "FileManager.h"
#include "Ini.h"
#include "AutoSign.h"

using namespace std;

AutoSign::AutoSign(int argc, TCHAR const **argv)
{
    this->argc = argc;
    this->argv = argv;

    serverInputDirName = L"\\\\10.91.44.19\\FileServer\\usr\\wangbihong\\input"; 
    serverOutputDirName = L"\\\\10.91.44.19\\FileServer\\usr\\wangbihong\\output";

    connect = new Connection(serverInputDirName, L"ops123!", L"administrator");

    szSignType = L"360sp,ms";

    szDateDirName = FileManager::CreateDateDir(serverInputDirName);

}

void AutoSign::run()
{
    if (connect->Connect())         // 与共享文件夹建立连接
    {
        CreateSignIni();            // 生成签名配置文件
        
        UploadOk();                 // 生成upload.ok文件
        
        connect->DisConnect();      // 断开连接
    }
    else 
    {
        wcout << TEXT("Connect Failed!") << endl;
    }

}

void AutoSign::CreateSignIni()
{
    for (int i = 1; i < argc; ++i)
    {
        LPTSTR lpFileName = FileManager::GetFileName(argv[i]);
        if (FileManager::CopyFileTo(
            argv[i], 
            serverInputDirName + L"\\" + szDateDirName + lpFileName
            )
            )
        {
            Ini::WriteIni(
                lpFileName, 
                L"path", 
                L"\"" + szDateDirName + lpFileName + L"\"",
                serverInputDirName + L"\\" + szDateDirName + L"sign_config.ini"
                );
            Ini::WriteIni(
                lpFileName, 
                L"sign_type", 
                L"\"" + szSignType + L"\"",
                serverInputDirName + L"\\" + szDateDirName + L"sign_config.ini"
                );
        }
    }
}

void AutoSign::UploadOk()
{
    // 创建upload.ok 表明签名文件上传结束
    FileManager::CreateFile(serverInputDirName + L"\\" + szDateDirName + L"upload.ok");
}

void AutoSign::GetOutputFile()
{
    
}