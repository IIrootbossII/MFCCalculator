
# MFC Calculator

C++과 MFC(Microsoft Foundation Classes)를 활용하여 개발한 Windows GUI 기반 계산기 프로그램입니다.

MFC의 메시지 맵과 이벤트 처리 구조를 이해하고, 사칙연산 및 계산 기록 조회 기능을 구현하는 것을 목적으로 개발했습니다.



## 1. 개발 환경 (Development Environment)

| 항목 | 내용 |
|---|---|
| Language | C++ |
| Framework | MFC |
| IDE | Microsoft Visual Studio |
| Platform | Windows |
| 주요 기술 | CString, CEdit, CDialogEx, std::vector |



## 2. 주요 기능 (Features)

- **사칙연산:** 덧셈, 뺄셈, 곱셈, 나눗셈
- **숫자 입력:** 0~9 버튼을 이용한 숫자 입력
- **Backspace:** 마지막 입력 문자 삭제
- **Clear:** 현재 입력값 및 연산 상태 초기화
- **Enter:** 두 피연산자에 대한 계산 결과 출력
- **Log:** 계산 결과를 별도 다이얼로그에서 조회

계산 결과는 `std::vector<double>`에 저장되며, 프로그램 실행 중 메모리에서 유지됩니다.



## 3. 주요 구현 내용 (Implementation)

### 3.1 이벤트 핸들러 통합

초기에는 숫자 버튼마다 개별 이벤트 핸들러를 작성했으나, 중복 코드가 증가하는 문제를 개선하기 위해 `ON_CONTROL_RANGE`를 적용했습니다.

```cpp
ON_CONTROL_RANGE(
    BN_CLICKED,
    IDC_NUM0,
    IDC_NUM9,
    &CCalculatorDlg::OnBnClickedNumRange
)
```

숫자 버튼의 리소스 ID를 연속적으로 배치하고, 전달받은 ID를 이용해 입력 숫자를 구분하도록 구현했습니다.

```cpp
int clickedNumber = nID - IDC_NUM0;
```

사칙연산 버튼에도 동일한 방식을 적용하여 개별 이벤트 핸들러를 공통 함수로 통합했습니다.

### 3.2 입력 및 연산 상태 관리

계산 과정에서 필요한 데이터를 별도의 멤버 변수로 관리했습니다.

| 변수 | 역할 |
|---|---|
| m_firstNumber | 첫 번째 피연산자 저장 |
| m_operator | 선택한 사칙연산 구분 |
| m_currentInput | 현재 입력된 숫자 문자열 |
| m_isNewInput | 새로운 입력 상태 구분 |

`CString`으로 사용자 입력을 관리하고, `_ttof()`를 통해 문자열을 `double` 자료형으로 변환했습니다.

연산자에 따라 `switch` 문으로 계산을 분기하도록 구현했습니다.

### 3.3 계산 결과 기록 및 조회

`std::vector<double>`을 이용하여 계산 결과를 순차적으로 저장하도록 구현했습니다.

```cpp
g_logHistory.push_back(m_finalResult);
```

기록 조회를 위한 별도의 `CLogDlg` 클래스를 구성하고, Log 버튼을 누르면 모달 다이얼로그가 실행되도록 구현했습니다.

```cpp
void CCalculatorDlg::OnBnClickedLog()
{
    CLogDlg dlg;
    dlg.DoModal();
}
```

`OnInitDialog()`에서 저장된 계산 결과를 순회하며 `CString`으로 변환한 뒤, 리스트 박스에 출력하도록 구성했습니다.



## 4. 실행 화면 (Screenshots)

### 계산기 메인 화면

<img width="571" height="634" alt="image" src="https://github.com/user-attachments/assets/e4ea48f9-2162-4db7-ac2c-d98c12262f5f" />

### 계산 기록 화면

실행 화면 첨부 예정



## 5. 개발 과정 및 개선 사항 (Troubleshooting)

### 이벤트 처리 코드 중복 개선

숫자 버튼마다 개별 이벤트 핸들러를 작성하는 초기 구조에서는 유사한 코드가 반복되었습니다.

이를 개선하기 위해 MFC의 `ON_CONTROL_RANGE` 매크로를 활용하여 숫자 및 연산자 입력을 공통 핸들러로 통합했습니다.

이를 통해 중복 코드를 줄이고 이벤트 처리 로직을 간결하게 구성했습니다.

### 향후 개선 사항

- 연속 계산 및 중복 연산자 입력 처리 개선
- 0으로 나누는 경우 사용자에게 오류 메시지 표시
- 계산 로직과 UI 처리 로직 분리
- 전역 변수에 의존하는 기록 관리 구조 개선
- 계산식과 결과를 함께 저장하는 기능
- 계산 기록의 파일 저장 및 불러오기 기능



## 6. 빌드 및 실행 방법 (Build & Run)

1. Microsoft Visual Studio에서 솔루션 파일(`.sln`)을 엽니다.
2. MFC 개발 구성 요소가 설치되어 있는지 확인합니다.
3. 프로젝트를 빌드합니다.
4. 프로그램을 실행합니다.

Windows 환경에서 실행할 수 있는 MFC 기반 애플리케이션입니다.
