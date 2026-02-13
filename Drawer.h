#pragma once


// Drawer
#include"MyDef.h"
#include<gdiplus.h>
#include<vector>
#include<algorithm>
using namespace std;
using namespace Gdiplus;


class Drawer : public CStatic
{
	DECLARE_DYNAMIC(Drawer)
private:
	vector<vector<int>>data;
	vector<ip> selected;
	double lPadding = 0;
	double rPadding = 0;
	double tPadding = 0;
	double bPadding = 0;

	double left = 0;
	double right = 8;
	double bot = 0;
	double top = 8;

	int width = 0;
	int height = 0;

	ULONG_PTR token;

	CString title;

public:
	Drawer();
	virtual ~Drawer();

protected:
	double CalcStringLen(HDC hDC, CString string);
	void MakeStar(PointF* arr, int i, int j);
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
	void SetData(vector<vector<int>>& y);
	void SetSelected(vector<ip>& s);
	//Отступ задается в процентах (диапазон значений от 0 до 100)
	void SetPadding(double lPadding, double rPadding, double tPadding, double bPadding);
	void SetTitle(CString str);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	CWnd* parent;
	ip LastClick;
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};


