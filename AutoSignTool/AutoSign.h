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

    std::wstring serverInputDirName; // ǩ������Ŀ¼
    std::wstring serverOutputDirName; // ǩ�����Ŀ¼
    Connection *connect;             // �����ļ�������
    std::wstring szSignType;         // ǩ������
    std::wstring szDateDirName;      // ǩ������Ŀ¼

    void CreateSignIni();            // ����ǩ�������ļ�ini
    void UploadOk();                 // ����upload.ok
    void GetOutputFile();            // ��ȡǩ������ļ�
};

#endif