// OSVersion.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

typedef struct 
{
	BYTE Used20CallingMethod;
	BYTE SMBIOSMajorVersion;
	BYTE SMBIOSMinorVersion;
	BYTE DmiRevision;
	DWORD Length;
	BYTE SMBIOSTableData[1];
}RawSMBIOSData;

typedef struct
{
	char szVendor[255];
	char szBIOSVersion[255];
	char szBIOSReleaseDate[255];
	char szUUID[255];
	char szManufacturer[255];
	char szProductName[255];
	char szVersion[255];
	char szSerialNumber[255];
	char szSkuNumber[255];
	char szFamily[255];
	char nEnClosureType;
	char szOSVersion[255];

}SMInfo;
typedef struct
{
	wchar_t wszVendor[255];
	wchar_t wszBIOSVersion[255];
	wchar_t wszBIOSReleaseDate[255];
	wchar_t wszUUID[255];
	wchar_t wszManufacturer[255];
	wchar_t wszProductName[255];
	wchar_t wszVersion[255];
	wchar_t wszSerialNumber[255];
	wchar_t wszSkuNumber[255];
	wchar_t wszFamily[255];
	wchar_t wszEnClosureType[255];
	wchar_t wszOSVersion[255];

}SMInfoW;
// COSVersionApp:
// �йش����ʵ�֣������ OSVersion.cpp
//

class COSVersionApp : public CWinApp
{
public:
	COSVersionApp();
	HANDLE m_hMutex;

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
	virtual int ExitInstance();
};

extern COSVersionApp theApp;