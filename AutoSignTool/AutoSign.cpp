#include <stdio.h>
#include <process.h>

#include "FileManager.h"
#include "CheckThread.h"
#include "Ini.h"
#include "AutoSign.h"

using namespace std;

void AutoSign::run()
{
    if (connect->Connect())         // 与共享文件夹建立连接
    {
        //CreateSignIni();            // 生成签名配置文件

        //UploadOk();                 // 生成upload.ok文件

        //GetOutputFile();            // 获取签名成功的文件

        //connect->DisConnect();      // 断开连接
    }

}

AutoSign::AutoSign(int argc, TCHAR const **argv)
{
    this->argc = argc;
    this->argv = argv;

    szRemoteUserName = L"administrator";
    szRemotePassword = L"ops123!";
    szSignType = L"360sp,ms";
    nTimeOut = 300 * 1000;
    serverInputDirName = L"\\\\10.91.44.19\\FileServer\\usr\\wangbihong\\input\\"; 
    serverOutputDirName = L"\\\\10.91.44.19\\FileServer\\usr\\wangbihong\\output\\";

    connect = new Connection(serverInputDirName, szRemotePassword, szRemoteUserName);

    szDateDirName = FileManager::CreateDateDir(serverInputDirName);

    szOutputPath = L"C:/Users/wangbihong/DeskTop/test/";
    
}

AutoSign::~AutoSign()
{
    delete connect;
}

void AutoSign::CreateSignIni()
{
    for (int i = 1; i < argc; ++i)
    {
        LPTSTR lpFileName = FileManager::GetFileName(argv[i]);
        if (FileManager::CopyFileTo(
            argv[i], 
            serverInputDirName + szDateDirName + lpFileName
            )
        )
        {
            Ini::WriteIni(
                lpFileName, 
                L"path", 
                L"\"" + szDateDirName + lpFileName + L"\"",
                serverInputDirName + szDateDirName + L"sign_config.ini"
                );
            Ini::WriteIni(
                lpFileName, 
                L"sign_type", 
                L"\"" + szSignType + L"\"",
                serverInputDirName + szDateDirName + L"sign_config.ini"
                );
        }
    }
}

void AutoSign::UploadOk()
{
    // 创建upload.ok 表明签名文件上传结束
    FileManager::CreateFile(serverInputDirName + szDateDirName + L"upload.ok");
}

void AutoSign::GetOutputFile()
{
    wstring s = serverOutputDirName + L"文件正确.txt";
    CheckThread *checkThread = new CheckThread(
        serverOutputDirName + szDateDirName, 
        serverOutputDirName + szDateDirName + L"文件正确.txt"
    );
    
    checkThread->start(nTimeOut);
    if (checkThread->isSuccess())
    {
        for (int i = 1; i < argc; ++i)
        {
            LPTSTR lpFileName = FileManager::GetFileName(argv[i]);
            FileManager::CopyFileTo(
                serverOutputDirName + szDateDirName + lpFileName, 
                szOutputPath + lpFileName
            );
        }
        _tprintf(L"\nDigital signature success\n");
    }
    else 
    {
        _tprintf(L"\nDigital signature failed. Please try again.\n");
    }

    delete checkThread;
}