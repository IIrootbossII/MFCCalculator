
# MFC Calculator

C++과 MFC(Microsoft Foundation Classes)를 활용하여 개발한 Windows GUI 기반 계산기 프로그램입니다.

MFC의 메시지 맵과 이벤트 처리 구조를 학습하고, 사칙연산과 계산 기록 관리 기능을 직접 구현했습니다.

특히 개별 버튼에 작성했던 이벤트 핸들러를 공통 핸들러로 통합하여 코드 중복을 줄이고 유지보수성을 개선하는 데 중점을 두었습니다.



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
- **숫자 입력:** 0~9 버튼을 통한 숫자 입력
- **Backspace:** 마지막 입력 문자 삭제
- **Clear:** 입력값 및 연산 상태 초기화
- **Enter:** 계산 결과 출력
- **Log:** 별도 다이얼로그를 통한 계산 기록 조회

계산 결과는 `std::vector<double>`에 순차적으로 저장되며, 프로그램 실행 중 메모리에서 유지됩니다.



## 3. 주요 구현 내용 (Implementation)

### 3.1 공통 이벤트 핸들러 구현

초기에는 숫자 버튼(0~9)에 각각 별도의 이벤트 핸들러를 작성했습니다.

그러나 기능이 동일한 코드가 반복되는 문제를 개선하기 위해 MFC의 `ON_CONTROL_RANGE` 매크로를 적용했습니다.

```cpp
ON_CONTROL_RANGE(
    BN_CLICKED,
    IDC_NUM0,
    IDC_NUM9,
    &CCalculatorDlg::OnBnClickedNumRange
)
```

숫자 버튼의 리소스 ID를 연속적으로 배치하고, 이벤트 발생 시 전달되는 ID를 이용하여 입력된 숫자를 구분하도록 구현했습니다.

```cpp
int clickedNumber = nID - IDC_NUM0;
```

사칙연산 버튼에도 동일한 구조를 적용하여 개별 이벤트 핸들러를 통합했습니다.

이를 통해 중복 코드를 줄이고 입력 처리 로직을 일관된 구조로 관리할 수 있도록 개선했습니다.

### 3.2 입력 및 연산 상태 관리

사용자의 입력과 계산 과정을 관리하기 위해 다음과 같은 멤버 변수를 사용했습니다.

| 변수 | 역할 |
|---|---|
| `m_firstNumber` | 첫 번째 피연산자 저장 |
| `m_operator` | 선택한 사칙연산 구분 |
| `m_currentInput` | 현재 입력 중인 숫자 문자열 |
| `m_isNewInput` | 새로운 숫자 입력 여부 판단 |

`CString`을 이용하여 사용자 입력을 문자열 형태로 관리하고, `_ttof()`를 통해 입력값을 `double` 자료형으로 변환했습니다.

이후 `switch` 문을 이용하여 선택된 연산자에 따라 계산을 수행하도록 구현했습니다.

계산 과정에 필요한 데이터를 별도로 관리하여 사용자 입력과 연산 처리의 흐름을 구분했습니다.

### 3.3 계산 기록 저장 및 조회

STL 컨테이너인 `std::vector<double>`을 활용하여 계산 결과를 메모리에 누적 저장하도록 구현했습니다.

```cpp
g_logHistory.push_back(m_finalResult);
```

별도의 `CLogDlg` 클래스를 구성하고, Log 버튼 클릭 시 모달 다이얼로그를 실행하도록 구현했습니다.

```cpp
void CCalculatorDlg::OnBnClickedLog()
{
    CLogDlg dlg;
    dlg.DoModal();
}
```

`CLogDlg::OnInitDialog()`에서는 저장된 데이터를 범위 기반 `for` 문으로 순회하며 `CString`으로 변환한 후 리스트 박스에 출력합니다.

이를 통해 계산 기능과 계산 기록 조회 화면을 별도의 다이얼로그로 구성했습니다.



## 4. 실행 화면 (Screenshots)

### 4.1 계산기 메인 화면

<img width="571" height="634" alt="계산기 메인 화면" src="https://github.com/user-attachments/assets/e4ea48f9-2162-4db7-ac2c-d98c12262f5f" />

### 4.2 계산 기록 화면

<img width="573" height="634" alt="계산 기록 조회 화면" src="https://github.com/user-attachments/assets/d87e92fc-8875-4cf2-a531-0e01e690b456" />

---

## 5. 개발 과정 및 개선 사항 (Development & Improvements)

### 5.1 이벤트 처리 구조 개선

**기존 방식**
- 숫자 버튼마다 별도의 이벤트 핸들러 작성
- 동일한 입력 처리 코드의 반복
- 기능 수정 시 여러 함수의 변경 필요

**개선 방식**
- `ON_CONTROL_RANGE`를 활용한 공통 이벤트 핸들러 구현
- 리소스 ID를 이용하여 입력된 숫자와 연산자 구분
- 중복 코드 감소 및 유지보수성 개선

### 5.2 현재 구현의 제약 사항

현재 계산기는 두 피연산자에 대한 기본 사칙연산을 중심으로 구현되어 있습니다.

- 연속 계산 및 중복 연산자 입력 처리 보완 필요
- 0으로 나누는 경우 사용자 오류 안내 기능 미구현
- 계산 결과와 입력 상태 간 전환 처리 개선 필요
- 계산 기록은 프로그램 실행 중 메모리에만 유지

### 5.3 향후 개선 방향

- 계산 로직과 MFC UI 처리 로직 분리
- 연속 계산 및 예외 입력 처리 개선
- 전역 변수에 의존하는 계산 기록 관리 구조 개선
- 계산식과 결과를 함께 저장하는 기록 기능
- 계산 기록의 파일 저장 및 불러오기 기능



## 6. 빌드 및 실행 방법 (Build & Run)

### 개발 요구사항

- Windows 운영체제
- Microsoft Visual Studio
- MFC 개발 구성 요소

### 실행 방법

1. 프로젝트의 솔루션 파일(`.sln`)을 Visual Studio에서 엽니다.
2. MFC 개발 구성 요소가 설치되어 있는지 확인합니다.
3. 프로젝트를 빌드합니다.
4. 생성된 프로그램을 실행합니다.



## 7. 프로젝트 회고 (Retrospective)

이번 프로젝트를 통해 MFC의 메시지 맵과 이벤트 기반 프로그래밍 구조를 학습하고, Windows GUI 애플리케이션의 기본적인 개발 과정을 경험했습니다.

특히 숫자 버튼별로 작성했던 중복 이벤트 처리 코드를 공통 핸들러로 통합하면서, 단순한 기능 구현뿐 아니라 코드의 가독성과 유지보수성을 고려하는 과정의 중요성을 이해할 수 있었습니다.

또한 `CString`을 이용한 입력값 처리, 멤버 변수를 활용한 연산 상태 관리, `std::vector`를 이용한 계산 기록 저장 등 C++의 다양한 기능을 실제 애플리케이션에 적용하는 경험을 쌓았습니다.
