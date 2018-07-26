#pragma once
class CListCtrl_Ex : public CListCtrl
{
public:
	CListCtrl_Ex();
	~CListCtrl_Ex();
	DECLARE_MESSAGE_MAP()
	
	afx_msg void OnNMCustomdraw(NMHDR *pNMHDR, LRESULT *pResult);	//自绘函数

public:
	void AdjustListWidth();	//根据内容进行自适应宽度设置
	afx_msg void OnNMDblclk(NMHDR *pNMHDR, LRESULT *pResult);	//双击可编辑列表实现

private:
	CEdit *m_Edit;	//指向编辑框
	int m_Row;		//当前编辑的行号，初始值为-1
	int m_Col;		//当前编辑的列号，初始值为-1
public:
	afx_msg void OnNMSetfocus(NMHDR *pNMHDR, LRESULT *pResult);
};

