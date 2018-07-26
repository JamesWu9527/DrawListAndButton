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


//������ƴ���
void CListCtrl_Ex::OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult)
{
	//����MSDN
	LPNMLVCUSTOMDRAW  lplvcd = (LPNMLVCUSTOMDRAW)pNMHDR;
	switch (lplvcd->nmcd.dwDrawStage)
	{
		//���ÿؼ������ݵı���ɫ �Լ��������ɫ
		case CDDS_SUBITEM | CDDS_ITEMPREPAINT:
		{
			//if (1 == lplvcd->iSubItem)	//�����������ָ�������� ��һ����ɫ����
			{
				lplvcd->clrText = RGB(0, 0, 0); //�����������ɫ
				lplvcd->clrTextBk = RGB(243, 202, 249);	//��������ı���ɫ
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

//�Զ������б�ؼ��Ŀ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*
	Step 1 ��ȡ�༭������� ȷ��λ�ã�
	Step 2 �������������Rect Ȼ�����ؼ�Edit ���������
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
	//�༭������� ���������õ��ı����Ҳ�
	m_Edit->SetSel(HIWORD(m_Edit->GetSel()), -1);
	m_Edit->SetFocus();
	
	*pResult = 0;
}


void CListCtrl_Ex::OnNMSetfocus(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
