#pragma once
class CListCtrl_Ex : public CListCtrl
{
public:
	CListCtrl_Ex();
	~CListCtrl_Ex();
	DECLARE_MESSAGE_MAP()
	
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);	//�Ի溯��

public:
	void AdjustListWidth();	//�������ݽ�������Ӧ�������
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);	//˫���ɱ༭�б�ʵ��

private:
	CEdit *m_Edit;	//ָ��༭��
	int m_Row;		//��ǰ�༭���кţ���ʼֵΪ-1
	int m_Col;		//��ǰ�༭���кţ���ʼֵΪ-1
public:
	afx_msg void OnNMSetfocus(NMHDR *pNMHDR, LRESULT *pResult);
};

