
// morzeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "morze.h"
#include "morzeDlg.h"
#include "afxdialogex.h"
#include <string>

#define MAX_MSG_LEN 16384

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CmorzeDlg dialog

CmorzeDlg::CmorzeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmorzeDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmorzeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmorzeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CmorzeDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CmorzeDlg message handlers

BOOL CmorzeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CmorzeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CmorzeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CmorzeDlg::ShowError(LPCWSTR prefix, DWORD status) {
	WCHAR sys_msg[MAX_MSG_LEN] = { 0 };
	if (FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM, 0, status, 0, sys_msg, MAX_MSG_LEN, NULL) == 0) {
		MessageBoxW(L"Failed to format error message, sorry about that.", L"Fatal error", MB_ICONERROR | MB_OK);
		CDialogEx::OnCancel();
		return;
	}

	WCHAR msg[MAX_MSG_LEN] = { 0 };
	wnsprintf(msg, MAX_MSG_LEN, L"Error during %s: %s", prefix, sys_msg);
	MessageBoxW(msg, L"Error", MB_ICONERROR | MB_OK);
	CDialogEx::OnCancel();
}

void CmorzeDlg::AssertStatus(LPCWSTR prefix, LSTATUS status) {
	if (status == ERROR_SUCCESS) {
		return;
	}

	ShowError(prefix, status);
}

void CmorzeDlg::AssertLastError(LPCWSTR prefix, HINSTANCE status) {
	DWORD err = GetLastError();
	if (err == 0) {
		return;
	}

	ShowError(prefix, err);
}

void CmorzeDlg::OnBnClickedOk()
{
	CString name;

	GetDlgItemText(IDC_EDIT1, name);
	name.Append(L"\r\n%DD%.%MM%.%YYYY%");

	LPWSTR msg = name.GetBuffer();
	
	HKEY hkey;
	AssertStatus(L"opening registry key", RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\NCH Software\\Debut\\VideoEffects", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_WRITE, NULL, &hkey, NULL));
	AssertStatus(L"updating text", RegSetValueExW(hkey, L"Text", 0, REG_SZ, (BYTE*) msg, (DWORD) ((wcslen(msg) + 1) * sizeof(WCHAR))));
	AssertStatus(L"closing registry key", RegCloseKey(hkey));

	AssertLastError(L"running app", ShellExecuteW(NULL, L"open", L"C:\\Program Files (x86)\\NCH Software\\Debut\\debut.exe", NULL, NULL, SW_SHOW));
	CDialogEx::OnOK();
}
