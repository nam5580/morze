
// morzeDlg.h : header file
//

#pragma once

// CmorzeDlg dialog
class CmorzeDlg : public CDialogEx
{
// Construction
public:
	CmorzeDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_MORZE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void CmorzeDlg::ShowError(LPCWSTR prefix, DWORD status);
	afx_msg void CmorzeDlg::AssertStatus(LPCWSTR prefix, LSTATUS status);
	afx_msg void CmorzeDlg::AssertLastError(LPCWSTR prefix, HINSTANCE status);

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
