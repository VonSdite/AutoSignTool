#ifndef __AUTO_SIGN__
#define __AUTO_SIGN__

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include <memory>

#include "Connection.h"
#include "Error.h"
#include "Ini.h"

class AutoSign
{
public:
    AutoSign(int argc, TCHAR **argv);
    ~AutoSign();
    void run();

private:
    std::vector<std::wstring> m_vstrCabPath;    // cab文件的路径

    std::wstring m_strOutputPath;               // 最终签名文件保存的位置
    std::wstring m_strDateDirName;              // 日期目录

    std::tr1::shared_ptr<Ini> m_pIni;           // Ini配置文件信息
    std::tr1::shared_ptr<Connection> m_pConnect;// 共享文件夹连接
    std::tr1::shared_ptr<ErrorPrinter> m_pErrorPrinter;// 错误信息输出者

    std::wstring GetConfigPath();               // 获取配置文件路径
    void ReadFromConfig();                      // 读取配置文件

    void ParseArgv(int argc, TCHAR **argv);     // 解析命令行参数
    void CheckCabPath();                        // 检查cab路径是否有效
    void CopyToOutputPath();                    // 复制到指定付出路径

    void CreateSignIni();                       // 生成签名配置文件ini
    void UploadOk();                            // 生成upload.ok
    void GetOutputFile();                       // 获取签名输出文件
};

#endif