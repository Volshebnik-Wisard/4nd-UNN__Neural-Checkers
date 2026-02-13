#include"pch.h"
#include"Game.h"

vector<vector<int>> Game::MakeStartBoard()
{
	vector<vector<int>> res(8, vector<int>(8, EMPTY));
	bool black = false;
	for (int i = 0; i < 3; i++)
	{
		black = !black;
		for (int j = 0; j < 8; j++)
		{
			if (black)res[i][j] = WHITE;
			black = !black;
		}
	}
	black = true;
	for (int i = 5; i < 8; i++)
	{
		black = !black;
		for (int j = 0; j < 8; j++)
		{
			if (black)res[i][j] = BLACK;
			black = !black;
		}
	}
	return res;
}

Game::Game()
{
	Restart();
}

void Game::Restart()
{
	turn = true;
	board = MakeStartBoard();
	sequence = false;
	wcount = 12;
	bcount = 12;
	end = false;

	counter = 0;
}

vector<vector<int>> Game::GetBoard()
{
	return board;
}

bool Game::GetTurn()
{
	return turn;
}

vector<int> Game::GetBoardN(bool bInversed)
{
	vector<int>res;
	res.resize(32, EMPTY);
	int t = 1;
	bool black = false;
	if (bInversed)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int val = board[i][j];
				board[i][j] = board[7 - i][7 - j];
				board[7 - i][7 - j] = val;
			}
		}
	}
	for (int i = 0; i < 8; i++)
	{
		black = !black;
		for (int j = 0; j < 8; j++)
		{
			if (black)
			{
				int id = i * 4 + (j - (j % 2)) / 2;
				res[id] = board[i][j];
			}
			black = !black;
		}
	}
	if (bInversed)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				int val = board[i][j];
				board[i][j] = board[7 - i][7 - j];
				board[7 - i][7 - j] = val;
			}
		}
		for (int i = 0; i < 32; i++)res[i] = -res[i];
	}
	return res;
}

int Game::GetPossibleTurns(int i, int j, vector<pair<int, int>>& out)
{
	if (board[i][j] == EMPTY)return -1;
	if (turn && ((board[i][j] == BLACK) || (board[i][j] == BLACKQ)))return -1;
	if ((!turn) && ((board[i][j] == WHITE) || (board[i][j] == WHITEQ)))return -1;


	if (board[i][j] == WHITE) return GetPossibleTurnsWHITE(i, j, out);
	if (board[i][j] == WHITEQ) return GetPossibleTurnsWHITEQ(i, j, out);
	if (board[i][j] == BLACK) return GetPossibleTurnsBLACK(i, j, out);
	if (board[i][j] == BLACKQ) return GetPossibleTurnsBLACKQ(i, j, out);
}

inline bool Game::IsPossibleTurn(int i, int j)
{
	for (auto& item : sturns)
	{
		if ((item.first == i) && (item.second == j))return true;
	}
	return false;
}

bool Game::IsEnemyBetween(ip p1, ip p2, ip& out)
{
	int x = 1, y = 1;
	if ((p2.first - p1.first) < 0)y = -1;
	if ((p2.second - p1.second) < 0)x = -1;

	int i = p1.first;
	int j = p1.second;
	while ((i != p2.first) && (j != p2.second))
	{
		if (board[i + y][j + x] != EMPTY)
		{
			out.first = i + y;
			out.second = j + x;
			return true;
		}
		i += y;
		j += x;
	}
	return false;
}

int Game::GetPossibleTurnsWHITE(int i, int j, vector<pair<int, int>>& out)
{
	//проверить на "бить обязательно"
	//сначала слева
	if ((j > 1) && (i < 6))
	{
		if ((board[i + 1][j - 1] == BLACK) || (board[i + 1][j - 1] == BLACKQ))
		{
			if (board[i + 2][j - 2] == EMPTY)out.push_back(ip(i + 2, j - 2));
		}
	}
	//теперь справа
	if ((j < 6) && (i < 6))
	{
		if ((board[i + 1][j + 1] == BLACK) || (board[i + 1][j + 1] == BLACKQ))
		{
			if (board[i + 2][j + 2] == EMPTY)out.push_back(ip(i + 2, j + 2));
		}
	}

	if (!out.empty())return true;

	//теперь просто ходим 
	//сначала влево
	if (j > 0)
	{
		if (board[i + 1][j - 1] == EMPTY)out.push_back(ip(i + 1, j - 1));
	}
	//теперь вправо
	if (j < 7)
	{
		if (board[i + 1][j + 1] == EMPTY)out.push_back(ip(i + 1, j + 1));
	}
	if (out.empty())return -1;
	return false;
}

int Game::GetPossibleTurnsWHITEQ(int i, int j, vector<pair<int, int>>& out)
{
	//проверить на "бить обязательно"
	//сначала слева
	if ((j > 1) && (i < 6))
	{
		if ((board[i + 1][j - 1] == BLACK) || (board[i + 1][j - 1] == BLACKQ))
		{
			if (board[i + 2][j - 2] == EMPTY)out.push_back(ip(i + 2, j - 2));
		}
	}

	if ((j > 1) && (i > 1))
	{
		if ((board[i - 1][j - 1] == BLACK) || (board[i - 1][j - 1] == BLACKQ))
		{
			if (board[i - 2][j - 2] == EMPTY)out.push_back(ip(i - 2, j - 2));
		}
	}

	//теперь справа
	if ((j < 6) && (i < 6))
	{
		if ((board[i + 1][j + 1] == BLACK) || (board[i + 1][j + 1] == BLACKQ))
		{
			if (board[i + 2][j + 2] == EMPTY)out.push_back(ip(i + 2, j + 2));
		}
	}

	if ((j < 6) && (i > 1))
	{
		if ((board[i - 1][j + 1] == BLACK) || (board[i - 1][j + 1] == BLACKQ))
		{
			if (board[i - 2][j + 2] == EMPTY)out.push_back(ip(i - 2, j + 2));
		}
	}

	if (!out.empty())return true;

	//теперь просто ходим 
	//сначала влево
	if (j > 0 && i < 7)
	{
		if (board[i + 1][j - 1] == EMPTY)out.push_back(ip(i + 1, j - 1));
	}
	//теперь вправо
	if (j < 7 && i < 7)
	{
		if (board[i + 1][j + 1] == EMPTY)out.push_back(ip(i + 1, j + 1));
	}
	//сначала влево
	if (j > 0 && i > 0)
	{
		if (board[i - 1][j - 1] == EMPTY)out.push_back(ip(i - 1, j - 1));
	}
	//теперь вправо
	if (j < 7 && i > 0)
	{
		if (board[i - 1][j + 1] == EMPTY)out.push_back(ip(i - 1, j + 1));
	}
	if (out.empty())return -1;
	return false;
}


int Game::GetPossibleTurnsBLACK(int i, int j, vector<pair<int, int>>& out)
{
	//проверить на "бить обязательно"
	//сначала слева
	if ((j > 1) && (i > 1))
	{
		if ((board[i - 1][j - 1] == WHITE) || (board[i - 1][j - 1] == WHITEQ))
		{
			if (board[i - 2][j - 2] == EMPTY)out.push_back(ip(i - 2, j - 2));
		}
	}

	//теперь справа
	if ((j < 6) && (i > 1))
	{
		if ((board[i - 1][j + 1] == WHITE) || (board[i - 1][j + 1] == WHITEQ))
		{
			if (board[i - 2][j + 2] == EMPTY)out.push_back(ip(i - 2, j + 2));
		}
	}

	if (!out.empty())return true;

	//теперь просто ходим 
	//сначала влево
	if (j > 0)
	{
		if (board[i - 1][j - 1] == EMPTY)out.push_back(ip(i - 1, j - 1));
	}
	//теперь вправо
	if (j < 7)
	{
		if (board[i - 1][j + 1] == EMPTY)out.push_back(ip(i - 1, j + 1));
	}
	if (out.empty())return -1;
	return false;
}
int Game::GetPossibleTurnsBLACKQ(int i, int j, vector<pair<int, int>>& out)
{
	//проверить на "бить обязательно"
	//сначала слева
	if ((j > 1) && (i < 6))
	{
		if ((board[i + 1][j - 1] == WHITE) || (board[i + 1][j - 1] == WHITEQ))
		{
			if (board[i + 2][j - 2] == EMPTY)out.push_back(ip(i + 2, j - 2));
		}
	}

	if ((j > 1) && (i > 1))
	{
		if ((board[i - 1][j - 1] == WHITE) || (board[i - 1][j - 1] == WHITEQ))
		{
			if (board[i - 2][j - 2] == EMPTY)out.push_back(ip(i - 2, j - 2));
		}
	}

	//теперь справа
	if ((j < 6) && (i < 6))
	{
		if ((board[i + 1][j + 1] == WHITE) || (board[i + 1][j + 1] == WHITEQ))
		{
			if (board[i + 2][j + 2] == EMPTY)out.push_back(ip(i + 2, j + 2));
		}
	}

	if ((j < 6) && (i > 1))
	{
		if ((board[i - 1][j + 1] == WHITE) || (board[i - 1][j + 1] == WHITEQ))
		{
			if (board[i - 2][j + 2] == EMPTY)out.push_back(ip(i - 2, j + 2));
		}
	}

	if (!out.empty())return true;

	//теперь просто ходим 
	//сначала влево
	if (j > 0 && i > 0)
	{
		if (board[i - 1][j - 1] == EMPTY)out.push_back(ip(i - 1, j - 1));
	}
	//теперь вправо
	if (j < 7 && i > 0)
	{
		if (board[i - 1][j + 1] == EMPTY)out.push_back(ip(i - 1, j + 1));
	}
	//сначала влево
	if (j > 0 && i < 7)
	{
		if (board[i + 1][j - 1] == EMPTY)out.push_back(ip(i + 1, j - 1));
	}
	//теперь вправо
	if (j < 7 && i < 7)
	{
		if (board[i + 1][j + 1] == EMPTY)out.push_back(ip(i + 1, j + 1));
	}
	if (out.empty())return -1;
	return false;
}



vector<ip> Game::GetMoveable()
{
	if (sequence)return vector<ip>(1, selected);

	vector<ip> res;
	vector<ip> notstrong;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			vector<ip>out;
			int rval = GetPossibleTurns(i, j, out);
			if (rval == -1)continue;

			if (rval == true)res.push_back(ip(i, j));
			else notstrong.push_back(ip(i, j));
		}
	}
	if (res.empty())
	{
		if (notstrong.empty())
		{
			winner = -1;
			end = true;
		}
		return notstrong;
	}
	return res;
}

bool Game::Select(int i, int j, vector<ip>& out)
{
	if (turn && ((board[i][j] == BLACK) || (board[i][j] == BLACKQ)))return false;
	if ((!turn) && ((board[i][j] == WHITE) || (board[i][j] == WHITEQ)))return false;
	int val = GetPossibleTurns(i, j, out);
	if (val == -1)return false;
	selected = ip(i, j);
	sturns = out;
	return true;
}

bool Game::DoTurn(int i, int j)
{
	if (end)return false;
	if (turn && ((board[i][j] == BLACK) || (board[i][j] == BLACKQ)))return false;
	if ((!turn) && ((board[i][j] == WHITE) || (board[i][j] == WHITEQ)))return false;
	kill = false;
	if (IsPossibleTurn(i, j))
	{
		ip pos;

		if (IsEnemyBetween(selected, ip(i, j), pos))
		{
			board[pos.first][pos.second] = EMPTY;
			if (turn)bcount--;
			else wcount--;
			kill = true;
		}
		else sequence = false;

		if (turn && (i == 7))board[i][j] = WHITEQ;
		else if ((!turn) && (i == 0))board[i][j] = BLACKQ;
		else board[i][j] = board[selected.first][selected.second];
		board[selected.first][selected.second] = EMPTY;
		selected.first = i;
		selected.second = j;

		if (kill)
			if (GetPossibleTurns(i, j, vector<ip>()) == 1)sequence = true;
			else sequence = false;

		if (!sequence)turn = !turn;


		if (wcount == 0)
		{
			end = true;
			winner = false;
		}
		if (bcount == 0)
		{
			end = true;
			winner = true;
		}
		counter++;
		if (counter > TURNS_CAP)
		{
			end = true;
			winner = -1;
		}
		return true;
	}
	return false;
}
bool Game::DoTurnUnchecked(int i, int j)
{
	if (end)return false;
	if (turn && ((board[i][j] == BLACK) || (board[i][j] == BLACKQ)))return false;
	if ((!turn) && ((board[i][j] == WHITE) || (board[i][j] == WHITEQ)))return false;
	kill = false;
	ip pos;

	if (IsEnemyBetween(selected, ip(i, j), pos))
	{
		board[pos.first][pos.second] = EMPTY;
		if (turn)bcount--;
		else wcount--;
		kill = true;
	}
	else sequence = false;

	if (turn && (i == 7))board[i][j] = WHITEQ;
	else if ((!turn) && (i == 0))board[i][j] = BLACKQ;
	else board[i][j] = board[selected.first][selected.second];
	board[selected.first][selected.second] = EMPTY;
	selected.first = i;
	selected.second = j;

	if (kill)
		if (GetPossibleTurns(i, j, vector<ip>()) == 1)sequence = true;
		else sequence = false;

	if (!sequence)turn = !turn;


	if (wcount == 0)
	{
		end = true;
		winner = false;
	}
	if (bcount == 0)
	{
		end = true;
		winner = true;
	}
	counter++;
	if (counter > TURNS_CAP)
	{
		end = true;
		winner = -1;
	}
	return true;
}

bool Game::IsGameEnd()
{
	return end;
}

int Game::Winner()
{
	return winner;
}

