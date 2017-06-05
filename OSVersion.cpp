// OSVersion.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "OSVersion.h"
#include "OSVersionDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COSVersionApp

BEGIN_MESSAGE_MAP(COSVersionApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// COSVersionApp ����

COSVersionApp::COSVersionApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� COSVersionApp ����

COSVersionApp theApp;


// COSVersionApp ��ʼ��

BOOL COSVersionApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();
	m_hMutex=OpenMutex(MUTEX_ALL_ACCESS,FALSE,TEXT("OSVersionTool"));
	if(m_hMutex)
	{
		return FALSE;
	}
	else
	{
		m_hMutex=CreateMutex(NULL,FALSE,TEXT("OSVersionTool"));
	}

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	COSVersionDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

int COSVersionApp::ExitInstance()
{
	// TODO: Add your specialized code here and/or call the base class
	if(m_hMutex)
		CloseHandle(m_hMutex);
	m_hMutex=NULL;

	return CWinApp::ExitInstance();
}
