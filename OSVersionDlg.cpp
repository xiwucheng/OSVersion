// OSVersionDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "OSVersion.h"
#include "OSVersionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COSVersionDlg 对话框




COSVersionDlg::COSVersionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COSVersionDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COSVersionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COSVersionDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// COSVersionDlg 消息处理程序

BOOL COSVersionDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	SMInfoW infoW;
	if (GetSMBIOSInfo(&infoW) > 0)
	{
		SetDlgItemText(IDC_EDIT1,infoW.wszVendor);
		SetDlgItemText(IDC_EDIT2,infoW.wszBIOSReleaseDate);
		SetDlgItemText(IDC_EDIT3,infoW.wszSkuNumber);
		SetDlgItemText(IDC_EDIT4,infoW.wszManufacturer);
		SetDlgItemText(IDC_EDIT5,infoW.wszUUID);
		SetDlgItemText(IDC_EDIT6,infoW.wszProductName);
		SetDlgItemText(IDC_EDIT7,infoW.wszSerialNumber);
		SetDlgItemText(IDC_EDIT8,infoW.wszEnClosureType);
		SetDlgItemText(IDC_EDIT9,infoW.wszOSVersion);
	}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void COSVersionDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR COSVersionDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


int COSVersionDlg::GetSMBIOSInfo(SMInfoW* lpInfoW)
{

	if (lpInfoW == NULL)
	{
		return -1;
	}

	DWORD iSignature='RSMB';
	//DWORD iSignature='ACPI';
	DWORD iSigId = 0;//'TDSX';//PCAF,TDSR,TDSX,PDSR,TDSD
	RawSMBIOSData *pData;
	SMInfo info={0};
	int length;
	char* szTemp=NULL;
	char buff[4096]={0};
	int iBuffersize = GetSystemFirmwareTable(iSignature,iSigId,0,0);
	if (iBuffersize <= 0)
	{
		return 0;
	}
	GetSystemFirmwareTable(iSignature,iSigId,buff,iBuffersize);
	pData = (RawSMBIOSData*)buff;
	szTemp = buff + 8;
	while (szTemp < buff + pData->Length)
	{
		if (*szTemp == 0)
		{
			szTemp += *(szTemp+1);
			strcpy_s(info.szVendor,255,szTemp);
			szTemp += strlen(szTemp) + 1;
			strcpy_s(info.szBIOSVersion,255,szTemp);
			szTemp += strlen(szTemp) + 1;
			strcpy_s(info.szBIOSReleaseDate,255,szTemp);
			while (*szTemp)
			{
				szTemp += strlen(szTemp) + 1;
			}
			szTemp++;

		}
		else if (*szTemp == 1)
		{
			sprintf(info.szUUID,"%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X%02X",(BYTE)*(szTemp+8),(BYTE)*(szTemp+9),(BYTE)*(szTemp+10),(BYTE)*(szTemp+11),
				(BYTE)*(szTemp+12),(BYTE)*(szTemp+13),(BYTE)*(szTemp+14),(BYTE)*(szTemp+15),(BYTE)*(szTemp+16),(BYTE)*(szTemp+17),(BYTE)*(szTemp+18),(BYTE)*(szTemp+19),(BYTE)*(szTemp+20),(BYTE)*(szTemp+21)
				,(BYTE)*(szTemp+22),(BYTE)*(szTemp+23));
			szTemp += *(szTemp+1);
			strcpy_s(info.szManufacturer,255,szTemp);
			szTemp += strlen(szTemp) + 1;
			strcpy_s(info.szProductName,255,szTemp);
			szTemp += strlen(szTemp) + 1;
			strcpy_s(info.szVersion,255,szTemp);
			szTemp += strlen(szTemp) + 1;
			strcpy_s(info.szSerialNumber,255,szTemp);
			szTemp += strlen(szTemp) + 1;
			strcpy_s(info.szSkuNumber,255,szTemp);
			szTemp += strlen(szTemp) + 1;
			strcpy_s(info.szFamily,255,szTemp);
			while (*szTemp)
			{
				szTemp += strlen(szTemp) + 1;
			}
			szTemp++;
		}
		else if (*szTemp == 3)
		{
			info.nEnClosureType = *(szTemp+5);
			szTemp += *(szTemp+1);
			while (*szTemp)
			{
				szTemp += strlen(szTemp) + 1;
			}
			szTemp++;
			//break;
		}
		else
		{
			szTemp += *(szTemp+1);
			if (*szTemp == 0)
			{
				szTemp += 2;
				continue;
			}
			while (*szTemp)
			{
				szTemp += strlen(szTemp) + 1;
			}
			szTemp++;
		}
	}
	CFile fp;
	BOOL bX64;
	IsWow64Process(GetCurrentProcess(),&bX64);
	CString szPath;
	if (bX64)
	{
		szPath = L"c:\\windows\\sysnative\\oem\\version.txt";
	}
	else
	{
		szPath = L"c:\\windows\\system32\\oem\\version.txt";
	}
	BOOL ret = fp.Open(szPath,CFile::modeRead|CFile::typeBinary);
	if (ret)
	{
		DWORD len = fp.GetLength();
		char* buf = new char[len+1];
		fp.Read(buf,len);
		fp.Close();
		char* p = strchr(buf,':');
		*strstr(buf,"\r\n") = 0;
		strcpy_s(info.szOSVersion,255,p+1);
		delete buf;
	}
	mbstowcs(lpInfoW->wszVendor,info.szVendor,255);
	mbstowcs(lpInfoW->wszBIOSVersion,info.szBIOSVersion,255);
	mbstowcs(lpInfoW->wszBIOSReleaseDate,info.szBIOSReleaseDate,255);
	mbstowcs(lpInfoW->wszUUID,info.szUUID,255);
	mbstowcs(lpInfoW->wszManufacturer,info.szManufacturer,255);
	mbstowcs(lpInfoW->wszProductName,info.szProductName,255);
	mbstowcs(lpInfoW->wszVersion,info.szVersion,255);
	mbstowcs(lpInfoW->wszSerialNumber,info.szSerialNumber,255);
	mbstowcs(lpInfoW->wszSkuNumber,info.szSkuNumber,255);
	mbstowcs(lpInfoW->wszFamily,info.szFamily,255);
	mbstowcs(lpInfoW->wszOSVersion,info.szOSVersion,255);
	switch(info.nEnClosureType)
	{
	case 3:
		_tcscpy_s(lpInfoW->wszEnClosureType,255,L"台式机");
		break;
	case 10:
		_tcscpy_s(lpInfoW->wszEnClosureType,255,L"笔记本");
		break;
	case 13:
		_tcscpy_s(lpInfoW->wszEnClosureType,255,L"一体台式机");
		break;
	case 30:
		_tcscpy_s(lpInfoW->wszEnClosureType,255,L"标准平板");
		break;
	case 31:
		_tcscpy_s(lpInfoW->wszEnClosureType,255,L"可翻转平板");
		break;
	case 32:
		_tcscpy_s(lpInfoW->wszEnClosureType,255,L"二合一平板");
		break;
	default:
		_tcscpy_s(lpInfoW->wszEnClosureType,255,L"未知电脑");
		break;
	}
	return 1;
}
