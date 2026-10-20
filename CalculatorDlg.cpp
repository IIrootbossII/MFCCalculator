
// CalculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CLogDlg.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


double m_finalResult;	// Enter를 누른 이후 최종 연산 결과 보관
extern std::vector<double> g_logHistory;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Display, m_calcResult);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CONTROL_RANGE(BN_CLICKED, IDC_NUM0, IDC_NUM9, &CCalculatorDlg::OnBnClickedNumRange)
	ON_CONTROL_RANGE(BN_CLICKED, IDC_PLUS, IDC_DIVIDE, &CCalculatorDlg::OnBnClickedOperatorRange)
	ON_BN_CLICKED(IDC_CLEAR, &CCalculatorDlg::OnBnClickedClear)
	ON_BN_CLICKED(IDC_BACKSPACE, &CCalculatorDlg::OnBnClickedBackspace)
	ON_BN_CLICKED(IDC_ENTER, &CCalculatorDlg::OnBnClickedEnter)
	ON_BN_CLICKED(IDC_LOG, &CCalculatorDlg::OnBnClickedLog)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_firstNumber = 0.0;	// 실수 타입
	m_operator = 0;			// 정수 타입
	m_isNewInput = FALSE;	// 문자열 타입

	m_currentInput = _T("");	// 실시간 입력 받는 변수 초기화
	m_calcResult.SetWindowText(_T(""));	// 연산 결과 띄우는 창 초기화

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
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
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CCalculatorDlg::OnBnClickedClear()
{
	// TODO: Add your control notification handler code here
	m_firstNumber = 0.0;	// 실수 타입 변수 초기화
	m_operator = 0;			// 정수 타입 변수 초기화
	m_isNewInput = FALSE;	// 문자열 타입 변수 초기화

	m_currentInput = _T("");	// 실시간 입력 받는 창 초기화
	m_calcResult.SetWindowText(_T(""));	// 연산 결과 띄우는 창 초기화
}

void CCalculatorDlg::OnBnClickedBackspace()
{
	// TODO: Add your control notification handler code here
	int currentLength = m_currentInput.GetLength();

	if (currentLength > 0)
	{
		m_currentInput = m_currentInput.Left(currentLength - 1);
		int	totalLength = m_calcResult.GetWindowTextLength();

		if (totalLength > 0)
		{
			m_calcResult.SetSel(totalLength - 1, totalLength);
			m_calcResult.ReplaceSel(_T(""));
		}
	}
}

void CCalculatorDlg::OnBnClickedNumRange(UINT nID)
{
	// 누른 숫자 = 클릭된 버튼의 ID - 0번 버튼의 ID
	int clickedNumber = nID - IDC_NUM0;

	// m_strDisplay에 표기할 숫자에 대한 변수 (CString)
	CString strClickedNum;
	strClickedNum.Format(_T("%d"), clickedNumber);

	// 방금 사칙연산 기호 눌렀을 때
	if (m_isNewInput == true)
	{
		// 기존의 숫자에 이어붙이지 않고 내용 날린 후, 누른 숫자 표기
		m_currentInput = strClickedNum;

		// false를 통해 else로 넘어가도록 흐름 생성
		m_isNewInput = false;
	}
	else
	{
		// 복사해 온 숫자에 누른 숫자 뒤에 붙이기
		m_currentInput += strClickedNum;
	}

	m_calcResult.SetSel(-1, -1);
	m_calcResult.ReplaceSel(strClickedNum);
}

void CCalculatorDlg::OnBnClickedOperatorRange(UINT nID)
{
	int clickedOperator = nID - IDC_PLUS;
	CString strOp;

	m_firstNumber = _ttof(m_currentInput);

	switch (clickedOperator)
	{
	case 0:
		strOp = _T(" + ");
		break;

	case 1:
		strOp = _T(" - ");
		break;

	case 2:
		strOp = _T(" x ");
		break;

	case 3:
		strOp = _T(" / ");
		break;
	}

	m_calcResult.SetSel(-1, -1);
	m_calcResult.ReplaceSel(strOp);
	
	m_currentInput = _T("");

	m_operator = clickedOperator;

	m_isNewInput = true;
}

void CCalculatorDlg::OnBnClickedEnter()
{
	// TODO: Add your control notification handler code here
	double secondNumber = _ttof(m_currentInput);
	double result{};
	CString strResult{};

	switch (m_operator)
	{
	case 0:
		result = m_firstNumber + secondNumber;
		break;
		
	case 1:
		result = m_firstNumber - secondNumber;
		break;

	case 2:
		result = m_firstNumber * secondNumber;
		break;

	case 3:
		if (secondNumber == 0)
		{
			return;
		}
		result = m_firstNumber / secondNumber;
		break;
	}
	
	strResult.Format(_T("\r\n= %g\r\n\r\n"), result);

	m_calcResult.SetSel(-1, -1);
	m_calcResult.ReplaceSel(strResult);

	m_currentInput = _T("");
	
	m_finalResult = result;
	g_logHistory.push_back(m_finalResult);

	m_isNewInput = true;
}


void CCalculatorDlg::OnBnClickedLog()
{
	// TODO: Add your control notification handler code here
	CLogDlg dlg;
	dlg.DoModal();
}




























//void CCalculatorDlg::OnBnClickedNum0()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("0");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("0");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum1()
//{
//	// TODO: Add your control notification handler code here
//	// 방금 사칙연산 기호를 눌렀을 때 
//	if (m_isNewInput == true)
//	{
//		// 기존의 글자에 이어붙이지 않고 새로운 숫자 1 띄우기
//		m_strDisplay = _T("1");
//		// 이젠 글자를 이어붙이기 위해 false를 통해 else로 넘어가도록 흐름 생성
//		m_isNewInput = false;
//	}
//	// 그냥 숫자가 이어져 올 때
//	else
//	{
//		// 화면 내부에 떠 있는 숫자 복사해오기
//		UpdateData(TRUE);
//		// 복사해온 숫자 뒤에 1 붙이기
//		m_strDisplay += _T("1");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum2()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("2");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("2");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum3()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("3");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("3");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum4()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("4");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("4");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum5()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("5");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("5");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum6()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("6");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("6");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum7()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("7");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("7");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum8()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("8");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("8");
//	}
//
//	UpdateData(FALSE);
//}
//
//void CCalculatorDlg::OnBnClickedNum9()
//{
//	// TODO: Add your control notification handler code here
//	if (m_isNewInput == true)
//	{
//		m_strDisplay = _T("9");
//		m_isNewInput = false;
//	}
//	else
//	{
//		UpdateData(TRUE);
//		m_strDisplay += _T("9");
//	}
//
//	UpdateData(FALSE);
//}