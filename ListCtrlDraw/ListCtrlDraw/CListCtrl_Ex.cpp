#include "stdafx.h"

#define ID_LISTEDIT                     9999

CListCtrl_Ex::CListCtrl_Ex()
{
	m_Edit = NULL;
}


CListCtrl_Ex::~CListCtrl_Ex()
{
}
BEGIN_MESSAGE_MAP(CListCtrl_Ex, CListCtrl)
	ON_NOTIFY_REFLECT(NM_CUSTOMDRAW, &CListCtrl_Ex::OnNMCustomdraw)
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CListCtrl_Ex::OnNMDblclk)
	ON_NOTIFY_REFLECT(NM_SETFOCUS, &CListCtrl_Ex::OnNMSetfocus)
END_MESSAGE_MAP()


//处理绘制代码
void CListCtrl_Ex::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	//参照MSDN
	LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;
	switch (lplvcd->nmcd.dwDrawStage)
	{
		//设置控件的内容的背景色 以及字体的颜色
		case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
		{
			//if (1 == lplvcd->iSubItem)	//这里可以设置指定的区域 哪一列颜色覆盖
			{
				lplvcd->clrText = RGB(0, 0, 0); //设置字体的颜色
				lplvcd->clrTextBk = RGB(243, 202, 249);	//设置字体的背景色
			}
		}
		break;
		default:
			break;
	}

	*pResult = 0;
	*pResult |= CDRF_NOTIFYPOSTPAINT;
	*pResult |= CDRF_NOTIFYITEMDRAW;
	*pResult |= CDRF_NOTIFYSUBITEMDRAW;
}

//自动调整列表控件的宽度
void CListCtrl_Ex::AdjustListWidth()
{
	CHeaderCtrl *pHead = GetHeaderCtrl();
	int nColumnCount = pHead->GetItemCount();

	for (int i = 0; i < nColumnCount; i++)
	{
		SetColumnWidth(i, LVSCW_AUTOSIZE);
		int nColumnWidth = GetColumnWidth(i);
		SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
		int nHeaderWidth = GetColumnWidth(i);
		SetColumnWidth(i, max(nColumnWidth, nHeaderWidth));
	}
}


void CListCtrl_Ex::OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	/*
	Step 1 获取编辑框的行列 确定位置；
	Step 2 计算所在区域的Rect 然后建立控件Edit 来存放数据
	*/
	m_Row = pNMItemActivate->iItem;
	m_Col = pNMItemActivate->iSubItem;
	CRect DataRect;
	GetSubItemRect(m_Row, m_Col, LVIR_LABEL, DataRect);
	CRect rect(DataRect);

	m_Edit = new CEdit();
	m_Edit->Create(WS_CHILD | WS_VISIBLE | WS_BORDER, rect, this, ID_LISTEDIT);
	CString str = GetItemText(pNMItemActivate->iItem, pNMItemActivate->iSubItem);
	m_Edit->UpdateData(FALSE);
	m_Edit->SetWindowText(str);
	//编辑框出来后 将焦点设置到文本的右侧
	m_Edit->SetSel(HIWORD(m_Edit->GetSel()), -1);
	m_Edit->SetFocus();
	
	*pResult = 0;
}


void CListCtrl_Ex::OnNMSetfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	if (NULL != m_Edit)
	{
		CString str;
		m_Edit->GetWindowText(str);
		SetItemText(m_Row, m_Col, str);
		delete m_Edit;
		m_Edit = NULL;
	}

	*pResult = 0;
}
