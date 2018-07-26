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
	// TODO: �ڴ����ר�ô����/����û���


	CButton::PreSubclassWindow();
}
BEGIN_MESSAGE_MAP(CButton_Ex, CButton)
	ON_WM_DRAWITEM()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEHOVER()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()


/*
��Ҫ���ػ溯�� ����˵��
�����٣������˷���WM_DRAWITEM��Ϣ�Ŀؼ��ı�ʶ��������˵������˴���Ϣ����nIDCtl�а���0��
�����ڣ�ָ����ָ��DRAWITEMSTRUCT���ݽṹ�ĳ�ָ�룬���а����й�Ҫ���������Ҫ��Ļ�ͼ���͵���Ϣ��
*/
void CButton_Ex::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	
	CButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CButton_Ex::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CButton::OnMouseHover(nFlags, point);
}


void CButton_Ex::OnMouseLeave()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CButton::OnMouseLeave();
}

//��дDrawItem�麯��
void CButton_Ex::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	//******************************** MSDN ���� + ���ϵ�����  ***********************//

	//��ȡ��ť���ı���Ϣ
	CString btnCaption;
	GetWindowText(btnCaption);

	CDC *pDC = CDC::FromHandle(lpDrawItemStruct->hDC);

	//�����õ��İ�ť�ߴ磬ʹ��ť��������һЩ
	CRect drawRect;
	RECT recttemp = lpDrawItemStruct->rcItem;
	recttemp.left -= -1;
	recttemp.top -= -1;
	recttemp.right -= 1;
	recttemp.bottom -= 1;
	drawRect.CopyRect(&(recttemp));
	
	//������ť�İ��� ������������·��ƶ���Ч�����Լ����µ���������
	UINT uStyle = DFCS_BUTTONPUSH;
	drawRect.top += (drawRect.Height() - pDC->GetTextExtent(btnCaption).cy) / 2; //�����ı�λ�� ����
	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		drawRect.top += 2;
		drawRect.left += 3;
		uStyle |= DFCS_PUSHED;	//���µ�Ч��
	}
	pDC->DrawFrameControl(&lpDrawItemStruct->rcItem, DFC_BUTTON, uStyle);//���ƿ�� ��������

	//���ð�ť�ı���ɫ�Լ��ı���ɫ
	CBrush pBrush;
	pBrush.CreateSolidBrush(RGB(243, 202, 249));
	pDC->FillRect(&recttemp, &pBrush);
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->DrawText(btnCaption, &drawRect, DT_RIGHT | DT_CENTER | DT_BOTTOM);
}
