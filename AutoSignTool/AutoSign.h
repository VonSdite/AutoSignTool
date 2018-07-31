#ifndef __AUTO_SIGN__
#define __AUTO_SIGN__

#include <Windows.h>
#include <tchar.h>
#include <string>
#include <vector>
#include "Connection.h"

class AutoSign
{
public:
    AutoSign(int argc, TCHAR **argv);
    ~AutoSign();
    void run();

private:
	BOOL bConfigExist;
	std::vector<std::wstring> arrCabPath;				// cab�ļ���·��
	std::wstring szOutputPath;							// ����ǩ���ļ������λ��

	BOOL ReadFromConfig();								// ��ȡ�����ļ�
	void ParseArgv(int argc, TCHAR **argv);		// ���������в���

    // ���´������ļ�����
    std::wstring szRemoteUserName;   // ��¼�����ļ����û���
    std::wstring szRemotePassword;   // ��¼�����ļ��е�����
    std::wstring szSignType;         // ǩ������
    DWORD nTimeOut;                  // ��ʱֵ
    std::wstring serverInputDirName; // ǩ������Ŀ¼
    std::wstring serverOutputDirName;// ǩ�����Ŀ¼


    Connection *connect;             // �����ļ�������
    std::wstring szDateDirName;      // ����Ŀ¼
    

    void CreateSignIni();            // ����ǩ�������ļ�ini
    void UploadOk();                 // ����upload.ok
    void GetOutputFile();            // ��ȡǩ������ļ�
};

#endif