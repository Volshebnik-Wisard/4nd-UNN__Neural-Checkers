
// Shashki.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CShashkiApp:
// Сведения о реализации этого класса: Shashki.cpp
//

class CShashkiApp : public CWinApp
{
public:
	CShashkiApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
	//afx_msg void OnMenuLoad();
	//afx_msg void On32773();
};

extern CShashkiApp theApp;
