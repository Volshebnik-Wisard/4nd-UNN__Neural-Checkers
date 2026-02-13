// Drawer.cpp: файл реализации
//

#include "pch.h"
#include "Drawer.h"


// Drawer

IMPLEMENT_DYNAMIC(Drawer, CStatic)

Drawer::Drawer()
{
	GdiplusStartupInput si;
	GdiplusStartup(&token, &si, NULL);
}

Drawer::~Drawer()
{
	GdiplusShutdown(token);
}


BEGIN_MESSAGE_MAP(Drawer, CStatic)
	ON_WM_LBUTTONUP()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()



// Обработчики сообщений Drawer




void Drawer::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	Graphics ToWindow(lpDrawItemStruct->hDC);
	width = lpDrawItemStruct->rcItem.right - lpDrawItemStruct->rcItem.left;
	height = lpDrawItemStruct->rcItem.bottom - lpDrawItemStruct->rcItem.top;
	Bitmap bmp(width, height);
	Graphics gr(&bmp);
	gr.Clear(Color::White);

	if (data.empty())
	{
		ToWindow.DrawImage(&bmp, 0, 0);
		return;
	}

	gr.SetSmoothingMode(SmoothingModeAntiAlias);
	double actWidth(right - left);
	double actHeight(top - bot);
	double actLP = actWidth * lPadding / 100.;
	double actRP = actWidth * rPadding / 100.;
	double actTP = actHeight * tPadding / 100.;
	double actBP = actHeight * bPadding / 100.;

	double actTop = top + actTP;
	double actBot = bot - actBP;
	double actLeft = left - actLP;
	double actRight = right + actRP;

	actWidth = actRight - actLeft;
	actHeight = actTop - actBot;


	double xScale = width / actWidth;
	double yScale = -height / actHeight;


	Matrix matr;
	matr.Scale(xScale, yScale);
	matr.Translate(actLP - left, -actTop);


	float steplenY = (top - bot) / 7.;
	float steplenX = (right - left) / 7.;

	FontFamily FF(L"Arial");
	Gdiplus::Font font(&FF, 12, FontStyle::FontStyleRegular, UnitPixel);
	SolidBrush brush(Color::Black);
	for (int i = 0; i < 8; i++)
	{
		PointF p1, p2;
		CString str;
		str.Format(L"%d", 8 - i);

		PointF strPoint;
		strPoint.X = left - actWidth / 100 - CalcStringLen(lpDrawItemStruct->hDC, str) / xScale;
		strPoint.Y = 7.5 - i;
		matr.TransformPoints(&strPoint);
		gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);

		str.Format(L"%c", L'h' - i);

		strPoint.X = 7.5 - i - CalcStringLen(lpDrawItemStruct->hDC, str) / xScale / 2.;
		strPoint.Y = bot + 6 / yScale;
		matr.TransformPoints(&strPoint);
		gr.DrawString(str, str.GetLength() + 1, &font, strPoint, &brush);
	}

	PointF p1, p2;

	if (!title.IsEmpty())
	{

		p1.X = actLeft + actWidth / 2 - CalcStringLen(lpDrawItemStruct->hDC, title) / 2 / xScale;
		p1.Y = (actTop + top) / 2 - 6 / yScale;
		matr.TransformPoints(&p1);
		gr.DrawString(title, title.GetLength() + 1, &font, p1, &brush);
	}

	SolidBrush black(Color::MakeARGB(255, 240, 240, 250));
	SolidBrush white(Color::MakeARGB(255, 88, 53, 38));
	SolidBrush brown(Color::Black);
	SolidBrush lbrown(Color::White);
	SolidBrush golden(Color(255, 255, 255, 0));
	SolidBrush light_blue(Color(255, 102, 255, 255));
	SolidBrush selectedbrush(Color(255, 255, 255, 0));

	bool iscellblack = false;
	for (int i = 0; i < 8; i++)
	{
		iscellblack = !iscellblack;
		for (int j = 0; j < 8; j++)
		{
			p1.X = j;
			p1.Y = i + 1;
			p2.X = j + 1;
			p2.Y = i;
			matr.TransformPoints(&p1);
			matr.TransformPoints(&p2);

			if (iscellblack)gr.FillRectangle(&brown, p1.X, p1.Y, p2.X - p1.X, p2.Y - p1.Y);
			else gr.FillRectangle(&lbrown, p1.X, p1.Y, p2.X - p1.X, p2.Y - p1.Y);
			iscellblack = !iscellblack;
		}
	}
	for (auto& item : selected)
	{
		p1.X = item.second;
		p1.Y = item.first + 1;
		p2.X = item.second + 1;
		p2.Y = item.first;
		matr.TransformPoints(&p1);
		matr.TransformPoints(&p2);
		gr.FillRectangle(&selectedbrush, p1.X, p1.Y, p2.X - p1.X, p2.Y - p1.Y);
	}
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			p1.X = j;
			p1.Y = i + 1;
			p2.X = j + 1;
			p2.Y = i;
			matr.TransformPoints(&p1);
			matr.TransformPoints(&p2);

			if (data[i][j] == WHITE) gr.FillEllipse(&white, p1.X, p1.Y, p2.X - p1.X, p2.Y - p1.Y);
			if (data[i][j] == BLACK) gr.FillEllipse(&black, p1.X, p1.Y, p2.X - p1.X, p2.Y - p1.Y);

			if (data[i][j] == WHITEQ)
			{
				gr.FillEllipse(&white, p1.X, p1.Y, p2.X - p1.X, p2.Y - p1.Y);
				PointF ps[12];
				MakeStar(ps, i, j);
				matr.TransformPoints(ps, 12);
				//gr.FillPolygon(&golden, ps, 12);
				gr.FillEllipse(&golden, p1.X + (p2.X - p1.X) / 4, p1.Y + (p2.Y - p1.Y) / 4, (p2.X - p1.X) / 2, (p2.Y - p1.Y) / 2);
			}
			if (data[i][j] == BLACKQ)
			{
				gr.FillEllipse(&black, p1.X, p1.Y, p2.X - p1.X, p2.Y - p1.Y);
				PointF ps[12];
				MakeStar(ps, i, j);
				matr.TransformPoints(ps, 12);
				//gr.FillPolygon(&golden, ps, 12);
				gr.FillEllipse(&light_blue, p1.X + (p2.X - p1.X) / 4, p1.Y + (p2.Y - p1.Y) / 4, (p2.X - p1.X) / 2, (p2.Y - p1.Y) / 2);
			}
		}
	}
	ToWindow.DrawImage(&bmp, 0, 0);
}


void Drawer::SetData(vector<vector<int>>& y)
{
	data = y;
	if (data.empty())return;
}

void Drawer::SetSelected(vector<ip>& s)
{
	selected = s;
}

void Drawer::SetPadding(double lP, double rP, double tP, double bP)
{
	lPadding = lP;
	rPadding = rP;
	tPadding = tP;
	bPadding = bP;
}
void Drawer::SetTitle(CString str)
{
	title = str;
}


double Drawer::CalcStringLen(HDC hDC, CString str)
{
	double numlen = 0;
	int size = str.GetLength() + 1;
	for (int i = 0; i < size; i++)
	{
		ABCFLOAT abc;
		GetCharABCWidthsFloatW(hDC, str[i], str[i], &abc);
		numlen += abc.abcfA + abc.abcfB + abc.abcfC;
	}
	return numlen;
}

void Drawer::MakeStar(PointF* arr, int i, int j)
{
	arr[0] = PointF(j, i + 0.26);
	arr[1] = PointF(j + 0.33, i + 0.26);
	arr[2] = PointF(j + 0.5, i);
	arr[3] = PointF(j + 0.66, i + 0.26);
	arr[4] = PointF(j + 1, i + 0.26);
	arr[5] = PointF(j + 0.85, i + 0.5);
	arr[6] = PointF(j + 1, i + 0.73);
	arr[7] = PointF(j + 0.66, i + 0.73);
	arr[8] = PointF(j + 0.5, i + 1);
	arr[9] = PointF(j + 0.33, i + 0.73);
	arr[10] = PointF(j, i + 0.73);
	arr[11] = PointF(j + 0.15, i + 0.5);

}

void Drawer::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	double actWidth(right - left);
	double actHeight(top - bot);
	double actLP = actWidth * lPadding / 100.;
	double actRP = actWidth * rPadding / 100.;
	double actTP = actHeight * tPadding / 100.;
	double actBP = actHeight * bPadding / 100.;

	double actTop = top + actTP;
	double actBot = bot - actBP;
	double actLeft = left - actLP;
	double actRight = right + actRP;

	actWidth = actRight - actLeft;
	actHeight = actTop - actBot;


	double xScale = width / actWidth;
	double yScale = -height / actHeight;


	Matrix matr;
	matr.Scale(xScale, yScale);
	matr.Translate(actLP - left, -actTop);
	matr.Invert();

	PointF p;
	p.X = point.x;
	p.Y = point.y;

	matr.TransformPoints(&p);
	parent->PostMessageW(MS_GAMECLICK);
	LastClick.first = p.Y;
	LastClick.second = p.X;
	CStatic::OnLButtonUp(nFlags, point);
}


void Drawer::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: добавьте свой код обработчика сообщений или вызов стандартного
	if (nChar == 0x52)parent->PostMessageW(MS_RESTART);
	CStatic::OnKeyDown(nChar, nRepCnt, nFlags);
}
