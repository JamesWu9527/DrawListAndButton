#include "stdafx.h"
#include "CButton_Ex.h"


CButton_Ex::CButton_Ex()
{
	m_bTracking = false;
}


CButton_Ex::~CButton_Ex()
{
}


void CButton_Ex::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类


	CButton::PreSubclassWindow();
}
BEGIN_MESSAGE_MAP(CButton_Ex, CButton)
	ON_WM_DRAWITEM()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


/*
重要的重绘函数 参数说明
参数①：包含了发送WM_DRAWITEM消息的控件的标识符。如果菜单发送了此消息，则nIDCtl中包含0。
参数②：指定了指向DRAWITEMSTRUCT数据结构的长指针，其中包含有关要画出的项和要求的绘图类型的信息。
*/
void CButton_Ex::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	
	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CButton_Ex::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT t;
		t.cbSize = sizeof(t);
		t.hwndTrack = m_hWnd;
		t.dwFlags = TME_LEAVE | TME_HOVER;
		t.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&t);
	}
	CButton::OnMouseMove(nFlags, point);
}


void CButton_Ex::OnMouseHover(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnMouseHover(nFlags, point);
}


void CButton_Ex::OnMouseLeave()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CButton::OnMouseLeave();
}

//重写DrawItem虚函数
void CButton_Ex::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//******************************** MSDN 例子 + 网上的例子  ***********************//

	//获取按钮的文本信息
	CString btnCaption;
	GetWindowText(btnCaption);

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	//调整得到的按钮尺寸，使按钮有轮廓感一些
	CRect drawRect;
	RECT recttemp = lpDrawItemStruct->rcItem;
	recttemp.left -= -1;
	recttemp.top -= -1;
	recttemp.right -= 1;
	recttemp.bottom -= 1;
	drawRect.CopyRect(&(recttemp));
	
	//调整按钮的按下 字体会有向右下方移动的效果，以及按下的属性设置
	UINT uStyle = DFCS_BUTTONPUSH;
	drawRect.top += (drawRect.Height() - pDC->GetTextExtent(btnCaption).cy) / 2; //调整文本位置 居中
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		drawRect.top += 2;
		drawRect.left += 3;
		uStyle |= DFCS_PUSHED;	//按下的效果
	}
	pDC->DrawFrameControl(&lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle);//绘制框架 设置属性

	//设置按钮的背景色以及文本颜色
	CBrush pBrush;
	pBrush.CreateSolidBrush(RGB(243, 202, 249));
	pDC->FillRect(&recttemp, &pBrush);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->DrawText(btnCaption, &drawRect, DT_RIGHT | DT_CENTER | DT_BOTTOM);
}
