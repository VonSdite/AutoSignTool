#ifndef __AUTO_SIGN__
#define __AUTO_SIGN__

#include <Windows.h>
#include <tchar.h>
#include <string>
#include "Connection.h"

class AutoSign
{
public:
    AutoSign(int argc, TCHAR const **argv);
    ~AutoSign();
    void run();

private:
    TCHAR const **argv;
    int argc;

    // 以下从配置文件读入
    std::wstring szRemoteUserName;   // 登录共享文件夹用户名
    std::wstring szRemotePassword;   // 登录共享文件夹的密码
    std::wstring szSignType;         // 签名类型
    DWORD nTimeOut;                  // 超时值
    std::wstring serverInputDirName; // 签名输入目录
    std::wstring serverOutputDirName;// 签名输出目录


    Connection *connect;             // 共享文件夹连接
    std::wstring szDateDirName;      // 日期目录
    std::wstring szOutputPath;       // 最终签名文件保存的位置


    void CreateSignIni();            // 生成签名配置文件ini
    void UploadOk();                 // 生成upload.ok
    void GetOutputFile();            // 获取签名输出文件
};

#endif