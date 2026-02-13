#pragma once
#include"MyDef.h"
#include<vector>
#include<math.h>
using namespace std;



class Game
{
private:
	bool turn;
	vector<vector<int>>board;
	ip selected;
	vector<ip>sturns;
	bool sequence;

	int wcount = 0;
	int bcount = 0;
	bool kill = false;
	bool end = false;
	int winner = false;

	int counter = 0;
protected:
	inline int GetPossibleTurns(int i, int j, vector<pair<int, int>>& out);
	inline int GetPossibleTurnsWHITE(int i, int j, vector<pair<int, int>>& out);
	inline int GetPossibleTurnsWHITEQ(int i, int j, vector<pair<int, int>>& out);
	inline int GetPossibleTurnsBLACK(int i, int j, vector<pair<int, int>>& out);
	inline int GetPossibleTurnsBLACKQ(int i, int j, vector<pair<int, int>>& out);
	vector<vector<int>>MakeStartBoard();
	inline bool IsPossibleTurn(int i, int j);
	bool IsEnemyBetween(ip p1, ip p2, ip& out);

public:
	Game();
	inline void Restart();
	vector<vector<int>>GetBoard();
	bool GetTurn();
	vector<int>GetBoardN(bool bInversed);
	vector<ip>GetMoveable();

	//выбор клетки, возвращает true, если клетка выбрана успешно
	bool Select(int i, int j, vector<ip>& out);
	//на вход номер клетки, в которую ходят из клетки selected
	bool DoTurn(int i, int j);
	bool DoTurnUnchecked(int i, int j);

	bool IsGameEnd();
	// 1 - белые, 0 - черные, -1 ничья
	int Winner();
};