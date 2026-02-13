// ForcedTrainDlg.cpp: файл реализации
//

#include "pch.h"
#include "Shashki.h"
#include "afxdialogex.h"
#include "ForcedTrainDlg.h"


// Диалоговое окно ForcedTrainDlg

IMPLEMENT_DYNAMIC(ForcedTrainDlg, CDialogEx)

ForcedTrainDlg::ForcedTrainDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

ForcedTrainDlg::~ForcedTrainDlg()
{
}

void ForcedTrainDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, FTnum);
}


BEGIN_MESSAGE_MAP(ForcedTrainDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &ForcedTrainDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// Обработчики сообщений ForcedTrainDlg


void ForcedTrainDlg::OnBnClickedOk()
{
	// TODO: добавьте свой код обработчика уведомлений
	CString str;
	FTnum.GetWindowTextW(str);
	n = _wtoi(str);
	CDialogEx::OnOK();
}


BOOL ForcedTrainDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  Добавить дополнительную инициализацию
	CString str;
	str.Format(L"%d", n);
	FTnum.SetWindowTextW(str);
	return TRUE;  // return TRUE unless you set the focus to a control
	// Исключение: страница свойств OCX должна возвращать значение FALSE
}
