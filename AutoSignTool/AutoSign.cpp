#include <process.h>
#include <iostream>
#include <cstring>

#include "FileManager.h"
#include "CheckThread.h"
#include "Ini.h"
#include "AutoSign.h"

using namespace std;

void AutoSign::run()
{
    if (bConfigExist && connect->Connect())  // �빲���ļ��н�������
    {
		szDateDirName = FileManager::CreateDateDir(serverInputDirName);

        CreateSignIni();            // ����ǩ�������ļ�

        UploadOk();                 // ����upload.ok�ļ�

        GetOutputFile();            // ��ȡǩ���ɹ����ļ�

        connect->DisConnect();      // �Ͽ�����
    }
	else 
	{
		std::wcout.imbue(std::locale("chs"));	
		wcout << L"[Error 2] �����ļ�������ʧ��" << endl;
	}

}

AutoSign::AutoSign(int argc, TCHAR const **argv)
{
	bConfigExist = ReadFromConfig(); // �������ļ���ȡ����
	if (bConfigExist)
	{
		ParseArgv(argc, argv);
		connect = new Connection(serverInputDirName, szRemotePassword, szRemoteUserName);
		
		szOutputPath = L"C:\\Users\\Sdite\\Desktop\\test\\";
	}
}

AutoSign::~AutoSign()
{
    delete connect;
}

BOOL AutoSign::ReadFromConfig()
{
    if (!FileManager::FileExist(L"E:/1Code/Repositories/C++/AutoSignTool/Debug/config.ini"))
	{
		std::wcout.imbue(std::locale("chs"));	
		wcout << L"[Error 1] �Ҳ��������ļ�config.ini" << endl;
		wcout << L"�����ļ�����Ӧ�����ڳ����Ŀ¼,��������:" << endl
			<< ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << endl;
		wcout << L"[config.ini]" << endl
			<< L";��¼�����ļ��е��û���" << endl
			<< L"userName=XXX" << endl
			<< L";��¼�����ļ��е��û�����Ӧ������" << endl
			<< L"password=XXX" << endl
			<< L";ǩ������" << endl
			<< L"signType=XXX" << endl
			<< L";ǩ��������������Ŀ¼" << endl
			<< L"signInputFile=XXX" << endl
			<< L";ǩ�������������Ŀ¼" << endl
			<< L"signOutputFile=XXX" << endl
			<< L";ǩ����ʱֵ(����Ϊ��λ)" << endl
			<< L"timeOut=5" << endl;
		return FALSE;
	}

	TCHAR buffer[1000];	
	memset(buffer, 0, sizeof(buffer));

	Ini::ReadStringFromIni(L"config.ini", L"userName", L"", buffer, 1000, L".\\config.ini");
	szRemoteUserName = buffer;

	Ini::ReadStringFromIni(L"config.ini", L"password", L"", buffer, 1000, L".\\config.ini");
	szRemotePassword = buffer;

	Ini::ReadStringFromIni(L"config.ini", L"signType", L"", buffer, 1000, L".\\config.ini");
	szSignType = buffer;

	Ini::ReadStringFromIni(L"config.ini", L"signInputFile", L"", buffer, 1000, L".\\config.ini");
	serverInputDirName = buffer;
	serverInputDirName += L"\\";

	Ini::ReadStringFromIni(L"config.ini", L"signOutputFile", L"", buffer, 1000, L".\\config.ini");
	serverOutputDirName = buffer;
	serverOutputDirName += L"\\";

	nTimeOut = Ini::ReadIntFromIni(L"config.ini", L"timeOut", 5, L".\\config.ini") * 60 * 1000;

	return TRUE;
}

void AutoSign::ParseArgv(int argc, TCHAR const **argv)
{
	std::wcout.imbue(std::locale("chs"));	
	if (argc != 3)
	{
		wcout << L"[Error 4] �����в�����������" << endl;
	}
	else
	{
		wstring cabPath = argv[1];
		szOutputPath = argv[2];

	}
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
    
	std::wcout.imbue(std::locale("chs"));	
	wcout << L"����ǩ��\n";
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
		wcout << L"\n[Successful] ǩ���ɹ�\n";
    }
    else 
    {
		wcout << L"\n[Error 3] ǩ��ʧ��, ������\n";
    }

    delete checkThread;
}