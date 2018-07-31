#include <process.h>
#include <iostream>
#include <cstring>
#include <map>

#include "FileManager.h"
#include "CheckThread.h"
#include "Ini.h"
#include "AutoSign.h"
#include "Parse.h"

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

AutoSign::AutoSign(int argc, TCHAR **argv)
{
	bConfigExist = ReadFromConfig(); // �������ļ���ȡ����
	if (bConfigExist)
	{
		ParseArgv(argc, argv);
		connect = new Connection(serverInputDirName, szRemotePassword, szRemoteUserName);
	}
}

AutoSign::~AutoSign()
{
    delete connect;
}

BOOL AutoSign::ReadFromConfig()
{
    if (!FileManager::FileExist(L".\\config.ini"))
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

void trim(std::wstring &s, TCHAR ch) 
{
    if (s.empty()) 
    {
        return ;
    }

    s.erase(0, s.find_first_not_of(ch));
    s.erase(s.find_last_not_of(ch) + 1);
}

void AutoSign::ParseArgv(int argc, TCHAR **argv)
{
	std::wcout.imbue(std::locale("chs"));	
	if (argc != 3)
	{
		wcout << L"[Error 4] �����в�����������" << endl;
        exit(-1);
	}
	else
	{
		map<std::wstring, std::wstring> mp;
        mp = Parse::GetPair(argc, argv, L"=");
        if (mp.size() != 2) 
        {
            wcout << L"[Error 5] �����в�����ʽ����" << endl;
            exit(-1);
        }
        szOutputPath = mp[L"output"];
        if (szOutputPath.empty())
        {
            wcout << L"[Error 6] �����в���ȱ���������·��, output=XXX" << endl;
            exit(-1);
        }
        //if (szOutputPath[0] != L'\"' || szOutputPath[szOutputPath.size()-1] != L'\"')
        //{
        //    wcout << L"[Error 7] ·��Ӧʹ��Ӣ��˫����������" << endl;
        //    exit(-1);
        //}
        //trim(szOutputPath, L'\"');

        arrCabPath = Parse::SplitString(mp[L"cab"], L";");
        if (arrCabPath.empty())
        {
            wcout << L"[Error 8] �����в���ȱ��cab�ļ�·��, cab=XXX" << endl;
            exit(-1);
        }
        //for (size_t i = 0; i < arrCabPath.size(); ++i)
        //{
        //    if (arrCabPath[i][0] != L'\"'|| arrCabPath[i][arrCabPath[i].size()-1] != L'\"')
        //    {
        //        wcout << L"[Error 7] ·��Ӧʹ��Ӣ��˫����������" << endl;
        //        exit(-1);
        //    }
        //    trim(arrCabPath[i], L'\"');
        //}

	}
}

void AutoSign::CreateSignIni()
{
    for (size_t i = 0; i < arrCabPath.size(); ++i)
    {
        LPTSTR lpFileName = FileManager::GetFileName(arrCabPath[i].c_str());
        if (FileManager::CopyFileTo(
            arrCabPath[i], 
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
        for (size_t i = 0; i < arrCabPath.size(); ++i)
        {
            LPTSTR lpFileName = FileManager::GetFileName(arrCabPath[i].c_str());
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
