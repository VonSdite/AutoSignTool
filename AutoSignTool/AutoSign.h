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
    void run();

private:
    TCHAR const **argv;
    int argc;

    std::wstring serverInputDirName; // 签名输入目录
    std::wstring serverOutputDirName; // 签名输出目录
    Connection *connect;             // 共享文件夹连接
    std::wstring szSignType;         // 签名类型
    std::wstring szDateDirName;      // 签名输入目录

    void CreateSignIni();            // 生成签名配置文件ini
    void UploadOk();                 // 生成upload.ok
    void GetOutputFile();            // 获取签名输出文件
};

#endif