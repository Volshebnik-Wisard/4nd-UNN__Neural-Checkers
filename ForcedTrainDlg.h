#pragma once
#include "afxdialogex.h"


// Диалоговое окно ForcedTrainDlg

class ForcedTrainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ForcedTrainDlg)

public:
	ForcedTrainDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~ForcedTrainDlg();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	CEdit FTnum;
	int n = 50;
	afx_msg void OnBnClickedOk();
	virtual BOOL OnInitDialog();
};
