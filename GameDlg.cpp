// GameDlg.cpp: файл реализации
//

#include "pch.h"
#include "Shashki.h"
#include "afxdialogex.h"
#include "GameDlg.h"


// Диалоговое окно GameDlg

IMPLEMENT_DYNAMIC(GameDlg, CDialogEx)

GameDlg::GameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

GameDlg::~GameDlg()
{
}

void GameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_PICTURE, drw);
}


BEGIN_MESSAGE_MAP(GameDlg, CDialogEx)
	ON_MESSAGE(MS_GAMECLICK, &GameDlg::OnMsGameClick)
	ON_MESSAGE(MS_GAMEEND, &GameDlg::OnMsGameEnd)
	ON_MESSAGE(MS_RESTART, &GameDlg::OnMsRestart)
	ON_MESSAGE(MS_BOTTURN, &GameDlg::OnMsBotTurn)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()


// Обработчики сообщений GameDlg


BOOL GameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	game.Restart();
	drw.parent = this;
	auto board = game.GetBoard();




	drw.SetData(board);
	drw.SetSelected(game.GetMoveable());

	SetFocus();
	SetWindowPos(this, posx, posy, 800, 800, SWP_NOZORDER);
	CRect rect;
	GetClientRect(&rect);
	drw.SetWindowPos(this, 0, 0, rect.Width(), rect.Height(), SWP_NOZORDER);

	if (gm == nvp)SendMessageW(MS_BOTTURN);
	SetWindowTextW(name);
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}

afx_msg LRESULT GameDlg::OnMsGameClick(WPARAM wParam, LPARAM lParam)
{
	bool turn = game.GetTurn();
	bool letbotplay = false;
	if (!selected)
	{

		vector<ip>turns;

		if (!game.Select(drw.LastClick.first, drw.LastClick.second, turns)) return 0;
		drw.SetSelected(turns);
		selected = !selected;
	}
	else
	{
		if (!game.DoTurn(drw.LastClick.first, drw.LastClick.second))return 0;
		drw.SetSelected(vector<ip>());
		selected = !selected;

		RefreshPicture();
		if ((gm == pvn) || (gm == nvp))
			if ((turn != game.GetTurn()) && (!game.IsGameEnd())) letbotplay = true;
	}
	drw.Invalidate();
	SendMessageW(MS_GAMEEND);
	if (letbotplay)SendMessage(MS_BOTTURN);
	return 0;
}

LRESULT GameDlg::OnMsGameEnd(WPARAM wParam, LPARAM lParam)
{
	if (game.IsGameEnd())
	{
		int res = game.Winner();
		if (res == 1)MessageBoxW(L"Победили коричневые", L"Игра окончена", MB_OK);
		if (res == 0)MessageBoxW(L"Победили белые", L"Игра окончена", MB_OK);
		if (res == -1)MessageBoxW(L"Ничья", L"Игра окончена", MB_OK);
	}
	return NULL;
}

LRESULT GameDlg::OnMsBotTurn(WPARAM wParam, LPARAM lParam)
{
	if (game.IsGameEnd())return 0;
	auto pos = bot->MakePredictions(game);
	if (game.IsGameEnd())
	{
		SendMessage(MS_GAMEEND);
		return 0;
	}
	bool turn = game.GetTurn();
	vector<ip>out;
	game.Select(pos.first.first, pos.first.second, out);
	if (!game.DoTurn(pos.second.first, pos.second.second)) abort();
	if (turn == game.GetTurn())SendMessageW(MS_BOTTURN);
	SendMessageW(MS_GAMEEND);

	RefreshPicture();
	return 0;
}

void GameDlg::RefreshPicture()
{
	drw.SetData(game.GetBoard());
	if (!game.IsGameEnd())
	{
		auto m = game.GetMoveable();
		if (m.empty())SendMessageW(MS_GAMEEND);
		else
			drw.SetSelected(m);
	}
	else drw.SetSelected(vector<ip>());
	drw.Invalidate();
}


void GameDlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (nChar == 0x52)
	{
		game.Restart();
		drw.SetData(game.GetBoard());
		drw.SetSelected(game.GetMoveable());
		drw.Invalidate();
		if (gm == nvp)SendMessageW(MS_BOTTURN);
	}
	CDialogEx::OnKeyDown(nChar, nRepCnt, nFlags);
}

afx_msg LRESULT GameDlg::OnMsRestart(WPARAM wParam, LPARAM lParam)
{
	game.Restart();
	drw.SetData(game.GetBoard());
	drw.SetSelected(game.GetMoveable());
	drw.Invalidate();
	return NULL;
}