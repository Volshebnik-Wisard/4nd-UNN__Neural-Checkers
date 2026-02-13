#pragma once

#include<afxwin.h>
#include<vector>
#include<algorithm>
#include<fstream>
#include"Game.h"
using namespace std;

struct neuron
{
	double out = 0;

	vector<double> w;
	double fi = 0;

	neuron() {}
	neuron(int size);
};


class NW
{
private:
	struct PossibleTurn
	{
		double est = 0;
		ip from = ip(0, 0);
		ip to = ip(0, 0);
	};


	vector<vector<neuron>>Layer;
	vector<int>LayerSize;

	vector<int>ls;
	const double MutationVal = 0.1;
protected:
	inline void ProcessNeuron(neuron& n, vector<double>& in, int len);
	inline double f(double x);
	inline PossibleTurn Max(vector<PossibleTurn>& p);
	inline PossibleTurn Min(vector<PossibleTurn>& p);
public:
	NW::NW(vector<int>& LS, int Enters);
	NW& NW::operator =(const NW& nw);
	template<typename T>
	inline double Calc(vector<T>& in);
	inline void NW::MakeChild(NW& left, NW& right);
	inline void NW::Mutate();
	inline pair<ip, ip> MakePredictions(Game& in);
	inline PossibleTurn NeuronMinmax1(Game in, ip& from, ip& to, bool turn);
	inline PossibleTurn NeuronMinmax2(Game in, ip& from, ip& to, bool turn);
	inline NW::PossibleTurn NW::NeuronMinmax3(Game in, ip& from, ip& to, bool turn);
	inline NW::PossibleTurn NW::NeuronMinmax4(Game in, ip& from, ip& to, bool turn);

	inline PossibleTurn Estimate(Game in, ip& from, ip& to, bool turn);
	int score = 0;
	bool turn = true;

	void Save();
	void Load();

	void Save(ofstream& ofstr);
	void Load(ifstream& ifstr);
};



typedef  NW* link;
class Trainer
{
private:
	vector<NW>P;
	static const int _size = 30;
	static const int _games = 5;
	const double MutVer = 0.5;

	vector<int>LS = { 40,10, 1 };

	bool ForcedToTrain = false;
protected:
	inline void score(NW& target, NW& opponent, bool turn);
	inline void ResetScore();
	inline void ScoreAll();
	inline void Replace();
	inline void MutateAll();
public:
	int TrainLimit = 1;

	Trainer();
	void train();
	bool stop = false;
	NW* OutNW = nullptr;
	CWnd* parent;

	void SaveBest();
	void SaveAll();

	void ForceToTrain(int val);
	void Load();
	void LoadALL();
	void FillOut();
	int BestScore = 0;
	unsigned int GamesCount = 0;
	int GenerationCount = 0;
	int scores[30];
	int hod = 0;
	int StartTime = 0;
	int EndTime = 0;
};

