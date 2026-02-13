
// MyDlg.h: файл заголовка
//

#pragma once
#include"GameDlg.h"
#include"ForcedTrainDlg.h"
// Диалоговое окно MyDlg
class MyDlg : public CDialogEx
{
	// Создание
public:
	MyDlg(CWnd* pParent = nullptr);	// стандартный конструктор

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHASHKI_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


	// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//afx_msg HCURSOR OnQueryDragIcon();
	//afx_msg LRESULT OnMsFillBot(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
public:
	CComboBox CBGameMode;
	afx_msg void OnBnClickedOk();
	//afx_msg void On32771();
	//afx_msg void On32773();
	//afx_msg void OnMenuLoad();

	Trainer trainer;
	//afx_msg void OnSaveAll();
	//afx_msg void OnLoadAll();
	CButton OkCtr;

	HANDLE TrainingThread;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	UINT_PTR timerid;
	//	CStatic BSctr;

	//	CStatic ScoresList;
		//afx_msg void OnForcedTrain();

	ForcedTrainDlg ftd;
	void MyDlg::FillInfo();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnCbnSelchangeComboGameMode();
	//	CButton but_save;
	CButton but_load;
	CButton but_save;
	CEdit info_educate;
	CEdit num_max_generation;
	CStatic str_50;
};
