#include <stdio.h>
#include <process.h>

#include "FileManager.h"
#include "CheckThread.h"
#include "Ini.h"
#include "AutoSign.h"

using namespace std;

void AutoSign::run()
{
    if (connect->Connect())         // �빲���ļ��н�������
    {
        //CreateSignIni();            // ����ǩ�������ļ�

        //UploadOk();                 // ����upload.ok�ļ�

        //GetOutputFile();            // ��ȡǩ���ɹ����ļ�

        //connect->DisConnect();      // �Ͽ�����
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
    // ����upload.ok ����ǩ���ļ��ϴ�����
    FileManager::CreateFile(serverInputDirName + szDateDirName + L"upload.ok");
}

void AutoSign::GetOutputFile()
{
    wstring s = serverOutputDirName + L"�ļ���ȷ.txt";
    CheckThread *checkThread = new CheckThread(
        serverOutputDirName + szDateDirName, 
        serverOutputDirName + szDateDirName + L"�ļ���ȷ.txt"
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