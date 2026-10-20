// CLogDlg.cpp : implementation file
//

#include "pch.h"
#include "Calculator.h"
#include "afxdialogex.h"
#include "CLogDlg.h"


// 연산 결과를 저장할 vector 타입 변수 선언
std::vector<double> g_logHistory;


// CLogDlg dialog

IMPLEMENT_DYNAMIC(CLogDlg, CDialogEx)

CLogDlg::CLogDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOG_DIALOG1, pParent)
{

}

CLogDlg::~CLogDlg()
{
}

void CLogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG_LIST1, m_logList);
}


BEGIN_MESSAGE_MAP(CLogDlg, CDialogEx)
END_MESSAGE_MAP()


// CLogDlg message handlers

BOOL CLogDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Add extra initialization here
	for (double val : g_logHistory)
	{
		CString str;
		str.Format(_T("%g"), val);
		m_logList.AddString(str);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
