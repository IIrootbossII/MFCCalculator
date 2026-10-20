
// CalculatorDlg.h : header file
//

#pragma once


// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	// 프로그램이 상시 기억해야 하는 변수
	double	m_firstNumber;	// 첫 번째로 입력된 숫자 보관
	int		m_operator;		// 어떤 연산자가 눌렀는지 보관
	bool	m_isNewInput;	// 연산자를 누른 직후인지 확인

	// 연산값을 표기할 변수 (CEdit)
	CEdit m_calcResult;
	// 사용자의 실시간 입력을 표기할 변수 (CString)
	CString m_currentInput;

	// Clear 버튼에 대한 함수 생성
	afx_msg void OnBnClickedClear();

	// BackSpace 버튼에 대한 함수 생성
	afx_msg void OnBnClickedBackspace();

	// 0부터 9까지의 버튼을 개별 함수로 설정했지만 코드 길어지는 게 
	// 거슬려서 묶어주는 매크로 같은 것을 설정
	// Resource.h 에서 IDC_NUM0 ~ IDC_NUM9 까지의 번호 순차적으로 되도록 수정
	afx_msg void OnBnClickedNumRange(UINT nID);

	// 사칙 연산 기호 (+, -, *, /) 를 묶어주는 매크로 생성
	afx_msg void OnBnClickedOperatorRange(UINT nID);
	
	// Enter를 클릭헀을 때 연산값 출력
	afx_msg void OnBnClickedEnter();

	// Log 버튼 클릭했을 때
	afx_msg void OnBnClickedLog();
};
