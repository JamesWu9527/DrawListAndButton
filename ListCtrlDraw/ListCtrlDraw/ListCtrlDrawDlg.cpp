
// ListCtrlDrawDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ListCtrlDraw.h"
#include "ListCtrlDrawDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CListCtrlDrawDlg 对话框

CListCtrlDrawDlg::CListCtrlDrawDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LISTCTRLDRAW_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CListCtrlDrawDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_DrawList);
	DDX_Control(pDX, IDC_BUTTON1, m_MyButton);
	DDX_Control(pDX, IDC_BUTTON2, m_button);
}

BEGIN_MESSAGE_MAP(CListCtrlDrawDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CListCtrlDrawDlg::OnBnClickedButton1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CListCtrlDrawDlg::OnNMDblclkList1)
END_MESSAGE_MAP()


// CListCtrlDrawDlg 消息处理程序

BOOL CListCtrlDrawDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//给列表进行初始化操作
	m_DrawList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT); //LVS_EX_FULLROWSELECT 整行选中
	m_DrawList.SetTextColor(GREEN_SHIFT);
	m_DrawList.InsertColumn(0, L"Author");
	m_DrawList.InsertColumn(1, L"Book");
	m_DrawList.InsertColumn(2, L"Date");
	m_DrawList.InsertColumn(3, L"Salary");

	CString str;
	for (int i = 0; i < 50; i++)
	{
		str.Format(L"%d", i);
		int idx = m_DrawList.InsertItem(i, L"Wang0"+str);
		m_DrawList.SetItemText(idx, 1, L"水浒传00");
		m_DrawList.SetItemText(idx, 2, L"水浒传01");
		m_DrawList.SetItemText(idx, 3, L"水浒传02");
		str = L"";
	}
	

	//设置背景颜色
	//m_DrawList.SetBkColor(COLORREF(RGB(91, 217, 95)));
	m_DrawList.AdjustListWidth();

	


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CListCtrlDrawDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CListCtrlDrawDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CListCtrlDrawDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//AfxMessageBox(L"点击了自定义颜色的按钮");
}


void CListCtrlDrawDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	AfxMessageBox(L"ssssss");
	*pResult = 0;
}
