﻿
// 2022111053Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "2022111053.h"
#include "2022111053Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CMy2022111053Dlg 대화 상자



CMy2022111053Dlg::CMy2022111053Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MY2022111053_DIALOG, pParent)
	, m_strResult(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2022111053Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LEFT, m_listLeft);
	DDX_Control(pDX, IDC_LIST_RIGHT, m_listRight);
	DDX_Control(pDX, IDC_COMBO_MOVE, m_cbMove);
	DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
}

BEGIN_MESSAGE_MAP(CMy2022111053Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PURCHASE, &CMy2022111053Dlg::OnClickedButtonPurchase)
	ON_CBN_SELCHANGE(IDC_COMBO_MOVE, &CMy2022111053Dlg::OnSelchangeComboMove)
END_MESSAGE_MAP()


// CMy2022111053Dlg 메시지 처리기

BOOL CMy2022111053Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	m_listLeft.AddString(_T("복숭아"));
	m_listLeft.AddString(_T("딸기"));
	m_listLeft.AddString(_T("사과"));
	m_listLeft.AddString(_T("바나나"));
	m_listLeft.AddString(_T("수박"));
	m_listLeft.AddString(_T("삼겹살"));
	m_listLeft.AddString(_T("참기름"));
	m_listLeft.AddString(_T("양파"));
	m_listLeft.AddString(_T("계란"));
	m_listLeft.AddString(_T("감자"));

	m_cbMove.AddString(_T("------------->"));
	m_cbMove.AddString(_T("<-------------"));

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMy2022111053Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMy2022111053Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMy2022111053Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//

void CMy2022111053Dlg::OnSelchangeComboMove()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// TODO: 여기에 구현 코드 추가.
	int nIndex = m_cbMove.GetCurSel();		//선택된 아이템의 인덱스를 구함
	int leftIndex = m_listLeft.GetCurSel();
	int rightIndex = m_listRight.GetCurSel();

	CString m_strItemSelect;

	if (nIndex == 0) {
		if (leftIndex == LB_ERR) {
			AfxMessageBox(_T("왼쪽 리스트 박스에서 이동할 아이템을 선택하세요"), MB_OK | MB_ICONEXCLAMATION);
		}
		else {
			m_listLeft.GetText(leftIndex, m_strItemSelect);    // 선택된 아이템의 문자열을 구함
			m_listLeft.DeleteString(leftIndex);    // 선택된 아이템을 삭제함
			m_listLeft.SetCurSel(leftIndex);    // 다음 아이템이 선택되게 함
			m_listRight.AddString(m_strItemSelect);    // 선택된 아이템의 문자열을 다른 리스트 박스에 추가함
		}
	}
	else if (nIndex == 1) {
		if (rightIndex == LB_ERR) {
			AfxMessageBox(_T("오른쪽 리스트 박스에서 이동할 아이템을 선택하세요"), MB_OK | MB_ICONEXCLAMATION);
		}
		else {
			m_listRight.GetText(rightIndex, m_strItemSelect);    // 선택된 아이템의 문자열을 구함
			m_listRight.DeleteString(rightIndex);    // 선택된 아이템을 삭제함
			m_listRight.SetCurSel(rightIndex);    // 다음 아이템이 선택되게 함
			m_listLeft.AddString(m_strItemSelect);    // 선택된 아이템의 문자열을 다른 리스트 박스에 추가함
		}
	}
}


void CMy2022111053Dlg::OnClickedButtonPurchase()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.	
	int nCount = m_listRight.GetCount();
	CString m_strPurchase;

	m_strResult.Empty();	// 에디트 박스를 비움

	for (int i = 0; i < nCount; i++) {
		m_listRight.GetText(i, m_strPurchase);
		m_strResult += m_strPurchase + _T("\r\n");
	}
	UpdateData(FALSE);
}



