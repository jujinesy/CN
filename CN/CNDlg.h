
// CNDlg.h : ��� ����
//

#pragma once
#include "afxcmn.h"


// CCNDlg ��ȭ ����
class CCNDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CCNDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_CN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	// ��Ʈ�Ѻ��� E_IPv
	CIPAddressCtrl E_IPv;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	CIPAddressCtrl E_IPv2;
};
