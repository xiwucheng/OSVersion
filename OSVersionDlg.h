// OSVersionDlg.h : ͷ�ļ�
//

#pragma once


// COSVersionDlg �Ի���
class COSVersionDlg : public CDialog
{
// ����
public:
	COSVersionDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_OSVERSION_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int GetSMBIOSInfo(SMInfoW* lpInfoW);
};
