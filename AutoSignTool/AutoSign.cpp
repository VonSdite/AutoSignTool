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
    if (bConfigExist && connect->Connect())  // 与共享文件夹建立连接
    {
		szDateDirName = FileManager::CreateDateDir(serverInputDirName);

        CreateSignIni();            // 生成签名配置文件

        UploadOk();                 // 生成upload.ok文件

        GetOutputFile();            // 获取签名成功的文件

        connect->DisConnect();      // 断开连接
    }
	else 
	{
		std::wcout.imbue(std::locale("chs"));	
		wcout << L"[Error 2] 共享文件夹连接失败" << endl;
	}

}

AutoSign::AutoSign(int argc, TCHAR const **argv)
{
	bConfigExist = ReadFromConfig(); // 从配置文件读取配置
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
		wcout << L"[Error 1] 找不到配置文件config.ini" << endl;
		wcout << L"配置文件内容应保存在程序根目录,内容如下:" << endl
			<< ";;;;;;;;;;;;;;;;;;;;;;;;;;;;;" << endl;
		wcout << L"[config.ini]" << endl
			<< L";登录共享文件夹的用户名" << endl
			<< L"userName=XXX" << endl
			<< L";登录共享文件夹的用户名对应的密码" << endl
			<< L"password=XXX" << endl
			<< L";签名类型" << endl
			<< L"signType=XXX" << endl
			<< L";签名服务器的输入目录" << endl
			<< L"signInputFile=XXX" << endl
			<< L";签名服务器的输出目录" << endl
			<< L"signOutputFile=XXX" << endl
			<< L";签名超时值(分钟为单位)" << endl
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
		wcout << L"[Error 4] 命令行参数个数不对" << endl;
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
    
	std::wcout.imbue(std::locale("chs"));	
	wcout << L"正在签名\n";
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
		wcout << L"\n[Successful] 签名成功\n";
    }
    else 
    {
		wcout << L"\n[Error 3] 签名失败, 请重试\n";
    }

    delete checkThread;
}