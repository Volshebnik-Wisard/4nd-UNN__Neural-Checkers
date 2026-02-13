#pragma once
#include "afxdialogex.h"
#include"Drawer.h"
#include"Neuron.h"

// Диалоговое окно GameDlg


enum GameMode
{
	pvp,
	pvn,
	nvp,
	educ
};
class GameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(GameDlg)

public:
	GameDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~GameDlg();

	// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV
	afx_msg LRESULT OnMsGameClick(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsGameEnd(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMsBotTurn(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT GameDlg::OnMsRestart(WPARAM wParam, LPARAM lParam);

	inline void RefreshPicture();
	DECLARE_MESSAGE_MAP()
public:
	Drawer drw;
	Game game;
	virtual BOOL OnInitDialog();
	int posx, posy;
	GameMode gm;
	bool selected = false;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	NW* bot;


	CString name;

};
