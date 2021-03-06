
// ListCtrlDrawDlg.h: 头文件
//

#pragma once

// CListCtrlDrawDlg 对话框
class CListCtrlDrawDlg : public CDialogEx
{
// 构造
public:
	CListCtrlDrawDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LISTCTRLDRAW_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl_Ex m_DrawList;	//改变内容背景颜色
	//CListCtrl m_DrawList;	//原始的形态SetBkColor函数可以设置非内容区的颜色
	CButton_Ex m_MyButton;
	afx_msg void OnBnClickedButton1();
	CButton m_button;
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
};
