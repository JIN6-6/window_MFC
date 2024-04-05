
// 2022111053View.cpp: CMy2022111053View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "2022111053.h"
#endif

#include "2022111053Doc.h"
#include "2022111053View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy2022111053View

IMPLEMENT_DYNCREATE(CMy2022111053View, CView)

BEGIN_MESSAGE_MAP(CMy2022111053View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CMy2022111053View 생성/소멸

CMy2022111053View::CMy2022111053View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	// 초기화
	m_strOut = _T("00: 00. 00");
	m_nCount = 0;
	m_nMin = 0;
	m_nSec = 0;
	m_nCentiSec = 0;
	m_bRunning = false;
}

CMy2022111053View::~CMy2022111053View()
{
}

BOOL CMy2022111053View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMy2022111053View 그리기

void CMy2022111053View::OnDraw(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CClientDC dc(this);
	CFont my_font;

	// 첫 번째 인자인 12가 폰트의 크기이고 마지막 인자가 폰트의 종류임
	my_font.CreateFont(100, 0, 0, 0, FW_NORMAL, FALSE, FALSE, 0,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("굴림체"));

	//새로 만든 폰트로 속성을 전환
	CFont* p_old_font = dc.SelectObject(&my_font);

	// 스톱워치 화면 출력
	dc.DrawText(m_strOut, rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	//이전에 사용하던 폰트로 속성을 복구
	dc.SelectObject(p_old_font);
	//생성된 폰트를 삭제한다. GDI 리소스를 반환하지 않으면 종종 다운되는 경우가 있어서 명시적으로 삭제하는게 좋음
	my_font.DeleteObject();

	// 기록 출력
	int x = 10; // x 좌표값
	int y = 10; // y 좌표값

	for (int i = 0; i < m_nCount; i++) {
		pDC->TextOut(x, y, m_strRec[i]); // 현재 기록을 출력
		y += 20; // y 좌표값을 20씩 증가시켜 다음 줄에 출력
	}

	CMy2022111053Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
}


// CMy2022111053View 인쇄

BOOL CMy2022111053View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMy2022111053View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMy2022111053View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CMy2022111053View 진단

#ifdef _DEBUG
void CMy2022111053View::AssertValid() const
{
	CView::AssertValid();
}

void CMy2022111053View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy2022111053Doc* CMy2022111053View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy2022111053Doc)));
	return (CMy2022111053Doc*)m_pDocument;
}
#endif //_DEBUG


// CMy2022111053View 메시지 처리기

void CMy2022111053View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bRunning) {	// 스톱워치가 작동중인 경우
		if (m_nCount == 20){	// 20개인 경우 문자열과 갯수를 세는 변수를 초기화
			for (int i = 0; i < 20; ++i) {
				m_strRec[i].Empty();	// 각 배열 요소를 비움
			}
			m_nCount = 0;
		}
		if (nChar == VK_SPACE){
			//문자열 저장 변수에 문자열을 생성하고, 갯수를 세는 변수의 값을 증가시킴
			m_strRec[m_nCount].Format(_T("[%02d] %02d: %02d. %02d", \n), m_nCount + 1, m_nMin, m_nSec, m_nCentiSec);
			m_nCount++;
		}
	}

	Invalidate();
	
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CMy2022111053View::OnRButtonDown(UINT nFlags, CPoint point)	//스톱워치가 작동하지 않을 경우
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (m_bRunning == false)	//스톱워치가 작동하지 않을 경우
	{
		if (AfxMessageBox(_T("스톱워치를 초기화 하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			//모든 변수를 초기화
			m_strOut = _T("00: 00. 00");
			for (int i = 0; i < 20; ++i) {
				m_strRec[i].Empty(); // 각 배열 요소를 비움
			}
			m_nCount = 0;
			m_nMin = 0;
			m_nSec = 0;
			m_nCentiSec = 0;
		}
		Invalidate();
	}
	else
	{
		//초기화 시킬 수 없다는 메시지 박스 출력
		AfxMessageBox(_T("작동 중에는 스톱워치를 초기화시킬 수 없습니다."), MB_OK | MB_ICONEXCLAMATION);
	}

	CView::OnRButtonDown(nFlags, point);
}


void CMy2022111053View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (!m_bRunning) {
		SetTimer(0, 10, NULL);
		m_bRunning = true;
	}
	else {
		KillTimer(0);	//스톱워치 정지
		m_bRunning = false;
	}
	CView::OnLButtonDown(nFlags, point);
}


void CMy2022111053View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	if (m_bRunning) {

		// 초 증가시키기
		m_nCentiSec++;

		// 1/100초 100 -> 1초, 다시 0부터 증가
		if (m_nCentiSec >= 100) {
			m_nSec++;
			m_nCentiSec = 0;
		}

		// 1초 60 -> 1분, 다시 0부터 증가

		if (m_nSec >= 60) {
			m_nMin++;
			m_nSec = 0;
		}
			
		// 문자열 생성
		m_strOut.Format(_T("%02d: %02d. %02d"), m_nMin, m_nSec, m_nCentiSec);

		Invalidate();
	}
	
	

	CView::OnTimer(nIDEvent);
}

int CMy2022111053View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.
	SetTimer(0, 10, NULL);	//타이머 설정

	return 0;
}