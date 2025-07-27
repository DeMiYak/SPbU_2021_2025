
// SDI_MFCDoc.cpp: реализация класса CSDIMFCDoc 
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDI_MFC.h"
#endif

#include "SDI_MFCDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSDIMFCDoc

IMPLEMENT_DYNCREATE(CSDIMFCDoc, CDocument)

BEGIN_MESSAGE_MAP(CSDIMFCDoc, CDocument)
	ON_COMMAND(ID_HI, &CSDIMFCDoc::OnHi)
	ON_COMMAND(ID_DRAW_CHANGE, &CSDIMFCDoc::OnDrawChange)
//	ON_COMMAND(ID_CHANGECOLOR_RED, &CSDIMFCDoc::OnChangecolorRed)
END_MESSAGE_MAP()


// Создание или уничтожение CSDIMFCDoc

CSDIMFCDoc::CSDIMFCDoc() noexcept
{
	// TODO: добавьте код для одноразового вызова конструктора
}

CSDIMFCDoc::~CSDIMFCDoc()
{
}

BOOL CSDIMFCDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)
	i = 200;
	return TRUE;
}




// Сериализация CSDIMFCDoc

void CSDIMFCDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CSDIMFCDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CSDIMFCDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задание содержимого поиска из данных документа.
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CSDIMFCDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// Диагностика CSDIMFCDoc

#ifdef _DEBUG
void CSDIMFCDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSDIMFCDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Команды CSDIMFCDoc


int CSDIMFCDoc::GetI()
{
	return i;
}

int CSDIMFCDoc::AddI()
{
	return i++;
}


void CSDIMFCDoc::OnHi()
{
	// TODO: добавьте свой код обработчика команд
	AfxMessageBox(L"Hello!");
}


void CSDIMFCDoc::OnDrawChange()
{
	// TODO: добавьте свой код обработчика команд
	i = AddI();
	UpdateAllViews(0);
}


//void CSDIMFCDoc::OnChangecolorRed()
//{
//	UpdateAllViews(0);
//	CClientDC DC(this);
//}
