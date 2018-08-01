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
    std::vector<std::wstring> m_vstrCabPath;    // cab�ļ���·��

    std::wstring m_strOutputPath;               // ����ǩ���ļ������λ��
    std::wstring m_strDateDirName;              // ����Ŀ¼

    std::tr1::shared_ptr<Ini> m_pIni;           // Ini�����ļ���Ϣ
    std::tr1::shared_ptr<Connection> m_pConnect;// �����ļ�������
    std::tr1::shared_ptr<ErrorPrinter> m_pErrorPrinter;// ������Ϣ�����

    std::wstring GetConfigPath();               // ��ȡ�����ļ�·��
    void ReadFromConfig();                      // ��ȡ�����ļ�

    void ParseArgv(int argc, TCHAR **argv);     // ���������в���
    void CheckCabPath();                        // ���cab·���Ƿ���Ч
    void CopyToOutputPath();                    // ���Ƶ�ָ������·��

    void CreateSignIni();                       // ����ǩ�������ļ�ini
    void UploadOk();                            // ����upload.ok
    void GetOutputFile();                       // ��ȡǩ������ļ�
};

#endif