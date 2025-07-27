
// SDI_MFCView.cpp: реализация класса CSDIMFCView
//
#include "pch.h"
#include "framework.h" // added #define _CRT_SECURE_NO_WARNINGS 
#include "CFormatDlg.h"


// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "SDI_MFC.h"
#endif

#include "SDI_MFCDoc.h"
#include "SDI_MFCView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSDIMFCView

IMPLEMENT_DYNCREATE(CSDIMFCView, CView)

BEGIN_MESSAGE_MAP(CSDIMFCView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_CHANGECOLOR_RED, &CSDIMFCView::OnChangecolorRed)
	ON_COMMAND(ID_CHANGECOLOR_GREEN, &CSDIMFCView::OnChangecolorGreen)
	ON_COMMAND(ID_CHANGECOLOR_BLUE, &CSDIMFCView::OnChangecolorBlue)
	ON_COMMAND(ID_DIALOGCLASS_TEST, &CSDIMFCView::OnDialogclassMainTest)
	ON_COMMAND(ID_DIALOGCLASS_DIAL2, &CSDIMFCView::OnDialogclassDialOpen)
	ON_COMMAND(ID_DIALOGCLASS_DIALCOLOR, &CSDIMFCView::OnDialogclassDialSave)
	ON_COMMAND(ID_DIALOGCLASS_COLOR, &CSDIMFCView::OnDialogclassColor)
END_MESSAGE_MAP()

// Создание или уничтожение CSDIMFCView

CSDIMFCView::CSDIMFCView() noexcept
{
	colorRef = 255;
	// TODO: добавьте код создания

}

CSDIMFCView::~CSDIMFCView()
{
}

BOOL CSDIMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: изменить класс Window или стили посредством изменения
	//  CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Рисование CSDIMFCView

void CSDIMFCView::OnDraw(CDC* pDC)
{
	CSDIMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	// Урок 4
	//CBrush newBrush(colorRef);
	//CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&newBrush);

	//CPen newPen(PS_SOLID, m_width, colorRef);
	//CPen* pOldPen = (CPen*)pDC->SelectObject(&newPen);

	//pDC->Rectangle(100, 100, 500, 500);
	//pDC->MoveTo(500, 500);
	//pDC->LineTo(700, 300);
	//pDC->MoveTo(700, 300);
	//pDC->LineTo(500, 100);

	//pDC->SelectObject(pOldBrush);
	//pDC->SelectObject(pOldPen);
	//newBrush.DeleteObject();
	//newPen.DeleteObject();

	//int i = pDoc->AddI();
	//pDC->TextOut((i+100)%1200, (i+80)%800, L"Hello");
	//pDC->Ellipse(30, 30, 130, 130);
	//// pDoc->UpdateAllViews(0);
	//pDC->TextOut((2*i + 40) % 1200, (2*i + 65) % 800, L"Hello");
	//// TODO: добавьте здесь код отрисовки для собственных данных

	//// Урок 3.
	//CPen penBlack; // Construct it, then initialize
	//// Create Pen возвращает 0, если создать объект не удалось
	//penBlack.CreatePen(PS_SOLID, 2, RGB(255, 0, 0));
	//// Select it into the device context
	//// Save the old pen at the same time
	//CPen* pOldPen = (CPen*)pDC->SelectObject(&penBlack);

	//// Draw with the pen. For example
	//pDC->MoveTo(30, 20);
	//pDC->LineTo(100, 200);

	//// Restore the old pen to the device context
	//pDC->SelectObject(pOldPen);
	//pDC->MoveTo(50, 50);
	//pDC->LineTo(200, 300);
	//pDC->SelectObject(penBlack);
	//pDC->MoveTo(60, 50);
	//pDC->LineTo(300, 300);

	//// Идея в MFC:
	//// создаётся карандаш определённого цвета, стиля и широты (он больше не меняется),
	//// затем он заносится в DC (Device Context). 
	//// Чтобы поменять цвет, стиль, или широту, нужно создать
	//// новый карандаш. Для этого заводим новый карандаш и заносим его в DC взамен старого,
	//// а указатель на старый сохраняем.
	////

	//// Если рисование происходит в другой функции, то
	//// нужно получить контекст следующим образом:
	//// CClientDC dc(this);
	//// либо
	//// CClientDC* pdc = new CClientDC(this);
	//// но тогда надо его удалить


	//// 1. Если нужно один и тот же объект (например, карандаш или кисть) 
	//// создавать несколько раз (меняя цвет, например), 
	//// то последовательность действий такая :
	//CPen pen;
	//for (int i = 0; i < 3; ++i)
	//{
	//	pen.CreatePen(PS_SOLID, i, RGB(i * 100, 0, 0));
	//	pOldPen = pDC->SelectObject(&pen);
	//	// Draw with the pen. For example,
	//	pDC->MoveTo(10 * (i + 1), 20);
	//	pDC->LineTo(100 * (i + 1), 200);
	//	// Restore the old pen to the device context
	//	pDC->SelectObject(pOldPen);
	//	// Delete the graphic object; действует только если перед этим
	//	// выбрать другой графический объект, тем самым освободив предыдущий.
	//	pen.DeleteObject();
	//}

	//// 2. Есть набор стандартных карандашей и кистей. 
	//// Их можно использовать, не создавая своих объектов. Например, так:

	//CBrush* pOldBrush = (CBrush*)pDC->SelectStockObject(BLACK_BRUSH);
	//pDC->SelectObject(pOldBrush);
	//pDC->MoveTo(100, 50);
	//pDC->ArcTo(100, 50, 400, 80, 150, 75, 125, 30);
	//pDC->Pie(100, 50, 400, 80, 800, 200, 125, 30);

	//// 3. Есть возможность создать не саму кисть (или перо), 
	//// а ее содержание (логическую структуру). Потом на основе
	//// этого содержания можно создавать уже настоящие кисти / перья.
	//// Логическая структура удобна тем, что с ней можно работать, 
	//// как с настоящей структурой, менять ее свойства через изменение полей.

	//LOGBRUSH logBrush;
	//logBrush.lbStyle = BS_HATCHED;
	//logBrush.lbColor = RGB(192, 192, 0);
	//logBrush.lbHatch = HS_CROSS;
	//// Declare an uninitialized CBrush ...
	//CBrush brush;
	//// ... and initialize it with the LOGBRUSH.
	//brush.CreateBrushIndirect(&logBrush);

	//// 4. Чтобы рисовать в относительных координатах, 
	//// можно узнать размер всего окна (его клиентской (внутренней части).

	//CRect rc; //Стандартный класс прямоугольника
	//GetClientRect(&rc); //Получаем прямоугольник, имеющий размеры области для
	//// рисования в координатах устройства
	//pDC->Rectangle(100, 100, rc.Width() / 2, rc.Height() / 2); //Прямоугольник размером
	////в четверть окна в логических координатах; в данном случае логические и
	////координаты устройства совпадают, иначе надо пользоваться функциями DPtoLP и LPtoDI
	//// pDC->FillRect(rc, &brush);

	//// 5. Со шрифтами работают так же, как и с перьями и кистями.
	//// Ниже приведен пример работы с использованием логической структуры.

	//CFont font;
	//LOGFONT lf;
	//memset(&lf, 0, sizeof(LOGFONT)); // zero out structure
	//lf.lfHeight = 14; // request a 12-pixel-height font
	//wcscpy(lf.lfFaceName, L"Arial"); // request a face name "Arial"
	//font.CreateFontIndirect(&lf); // create the font
	//CFont* def_font = pDC->SelectObject(&font);
	//pDC->TextOut(300, 400, L"Hello"); //по умолчанию указанные координаты – это координаты
	//// верхнего левого угла прямоугольника, в который идет вывод текста. Это можно //
	//// изменить с помощью вызова pDC->SetTextAlign(…)
	//pDC->SelectObject(def_font);
	//font.DeleteObject();// Done with the font. Delete the font object.
	//lf.lfHeight = 20; // request a 20-pixel-height font
	//wcscpy(lf.lfFaceName, L"Courier New"); // request a face name "Arial"
	//font.CreateFontIndirect(&lf); // create the font
	//def_font = pDC->SelectObject(&font);
	//pDC->TextOut(400, 400, L"Hello");
	//pDC->SelectObject(def_font);

	//// Сделать приложение, рисующее линию и закрашенный прямоугольник на экране.
	//// Добавить пункты меню, которые меняют цвет на синий, красный или зеленый.
	//
	//// При изменении размеров окна цвет должен оставаться тем, который был выбран.
	//// Для этого цвет (или весь карандаш целиком) должен храниться в классе CNameView.
}

void CSDIMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CSDIMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}

void CSDIMFCView::OnChangecolorRed()
{
	CSDIMFCDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(0);
	colorRef = RGB(255, 0, 0);
}

void CSDIMFCView::OnChangecolorGreen()
{
	CSDIMFCDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(0);
	colorRef = RGB(0, 255, 0);
}

void CSDIMFCView::OnChangecolorBlue()
{
	CSDIMFCDoc* pDoc = GetDocument();
	pDoc->UpdateAllViews(0);
	colorRef = RGB(0, 0, 255);
}


// Диагностика CSDIMFCView

#ifdef _DEBUG
void CSDIMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CSDIMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSDIMFCDoc* CSDIMFCView::GetDocument() const // встроена неотлаженная версия
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSDIMFCDoc)));
	return (CSDIMFCDoc*)m_pDocument;
}
#endif //_DEBUG


// Обработчики сообщений CSDIMFCView


//void CSDIMFCView::OnChangecolorRed()
//{
//	CClientDC DC(this);
//	CPen newPen;
//	CBrush newBrush;
//	logPen.lopnColor = RGB(255, 0, 0);
//	logPen.lopnStyle = PS_SOLID;
//	logPen.lopnWidth = CPoint(1, 105);
//	logBrush.lbColor = RGB(255, 0, 0);
//	logBrush.lbStyle = BS_HATCHED;
//	logBrush.lbHatch = HS_CROSS;
//
//	// Создание новой кисти и карандаша
//	newPen.CreatePenIndirect(&logPen);
//	newBrush.CreateBrushIndirect(&logBrush);
//
//	// Сохранение старых кисти и карандаша
//	CPen* pOldPen = (CPen*)DC.SelectObject(&newPen);
//	CBrush* pOldBrush = (CBrush*)DC.SelectObject(&newBrush);
//
//	// Создание прямоугольника
//	CRect rc; //Стандартный класс прямоугольника
//	GetClientRect(&rc);//Получаем прямоугольник, имеющий размеры области для
//	// рисования в координатах устройства
//	DC.Rectangle(0, 0, rc.Width() / 2, rc.Height() / 2); //Прямоугольник размером
//	//в четверть окна в логических координатах; в данном случае логические и
//	//координаты устройства совпадают, иначе надо пользоваться функциями DPtoLP и LPtoDI
//	// pDC->FillRect(rc, &brush);
//
//	// Плохая закраска
//	DC.FillRect(rc, &newBrush);
//	DC.MoveTo(rc.Width()/2, rc.Height()/2);
//	DC.LineTo(rc.Width() / 2 + 300, rc.Height() / 2 + 300);
//
//	// Возвращение старых кисти и карандаша и удаление новых
//	DC.SelectObject(pOldPen);
//	DC.SelectObject(pOldBrush);
//	newPen.DeleteObject();
//	newBrush.DeleteObject();
//}
//
//
//void CSDIMFCView::OnChangecolorGreen()
//{
//	CClientDC DC(this);
//	CPen newPen;
//	CBrush newBrush;
//	logPen.lopnColor = RGB(0, 255, 0);
//	logPen.lopnStyle = PS_SOLID;
//	logPen.lopnWidth = CPoint(1, 105);
//	logBrush.lbColor = RGB(0, 255, 0);
//	logBrush.lbStyle = BS_HATCHED;
//	logBrush.lbHatch = HS_CROSS;
//
//	// Создание новой кисти и карандаша
//	newPen.CreatePenIndirect(&logPen);
//	newBrush.CreateBrushIndirect(&logBrush);
//
//	// Сохранение старых кисти и карандаша
//	CPen* pOldPen = (CPen*)DC.SelectObject(&newPen);
//	CBrush* pOldBrush = (CBrush*)DC.SelectObject(&newBrush);
//
//	// Создание прямоугольника
//	CRect rc; //Стандартный класс прямоугольника
//	GetClientRect(&rc);//Получаем прямоугольник, имеющий размеры области для
//	// рисования в координатах устройства
//	DC.Rectangle(0, 0, rc.Width() / 2, rc.Height() / 2); //Прямоугольник размером
//	//в четверть окна в логических координатах; в данном случае логические и
//	//координаты устройства совпадают, иначе надо пользоваться функциями DPtoLP и LPtoDI
//	// pDC->FillRect(rc, &brush);
//
//	// Плохая закраска
//	DC.FillRect(rc, &newBrush);
//	DC.MoveTo(rc.Width() / 2, rc.Height() / 2);
//	DC.LineTo(rc.Width() / 2 + 300, rc.Height() / 2 + 300);
//
//	// Возвращение старых кисти и карандаша и удаление новых
//	DC.SelectObject(pOldPen);
//	DC.SelectObject(pOldBrush);
//	newPen.DeleteObject();
//	newBrush.DeleteObject();
//}
//
//
//void CSDIMFCView::OnChangecolorBlue()
//{
//	CClientDC DC(this);
//	CPen newPen;
//	CBrush newBrush;
//	logPen.lopnColor = RGB(0, 0, 255);
//	logPen.lopnStyle = PS_SOLID;
//	logPen.lopnWidth = CPoint(1, 105);
//	logBrush.lbColor = RGB(0, 0, 255);
//	logBrush.lbStyle = BS_HATCHED;
//	logBrush.lbHatch = HS_CROSS;
//
//	// Создание новой кисти и карандаша
//	newPen.CreatePenIndirect(&logPen);
//	newBrush.CreateBrushIndirect(&logBrush);
//
//	// Сохранение старых кисти и карандаша
//	CPen* pOldPen = (CPen*)DC.SelectObject(&newPen);
//	CBrush* pOldBrush = (CBrush*)DC.SelectObject(&newBrush);
//
//	// Создание прямоугольника
//	CRect rc; //Стандартный класс прямоугольника
//	GetClientRect(&rc);//Получаем прямоугольник, имеющий размеры области для
//	// рисования в координатах устройства
//	DC.Rectangle(0, 0, rc.Width() / 2, rc.Height() / 2); //Прямоугольник размером
//	//в четверть окна в логических координатах; в данном случае логические и
//	//координаты устройства совпадают, иначе надо пользоваться функциями DPtoLP и LPtoDI
//	// pDC->FillRect(rc, &brush);
//
//	// Плохая закраска
//	DC.FillRect(rc, &newBrush);
//	DC.MoveTo(rc.Width() / 2, rc.Height() / 2);
//	DC.LineTo(rc.Width() / 2 + 300, rc.Height() / 2 + 300);
//
//	// Возвращение старых кисти и карандаша и удаление новых
//	DC.SelectObject(pOldPen);
//	DC.SelectObject(pOldBrush);
//	newPen.DeleteObject();
//	newBrush.DeleteObject();
//}







// 8. Задание: Сделать так, чтобы при вызове пункта меню Format вызывался диалог, 
// в котором можно установить ширину линии и выбрать один из трех цветов:
// синий, зеленый или красный. После чего в окне рисовалась бы 
// линия выбранной толщины и цвета.По пункту меню Color должен 
// вызываться стандартный диалог выбора цвета, после чего 
// рисоваться прямоугольник выбранного цвета.

// 14. Задание: Сделать так, чтобы был контроль за значение ширины линии 
// в границах от 1 до 3. Сделать так, чтобы при выборе синего цвета 
// изменение ширины линии стало недоступным. При выборе другого цвета – снова доступным.

void CSDIMFCView::OnDialogclassMainTest()
{
	CFormatDlg d;
	d.m_width = m_width;
	d.m_colorIndex = m_colorIndex;
	d.m_lineColor = colorRef;
	if (d.DoModal() == IDOK) {
		/*действия*/
		m_width = d.m_width;
		m_colorIndex = d.m_colorIndex;
		colorRef = d.m_lineColor;
		
		// Если перерисовываем, то обновляем окно
		/*CSDIMFCDoc* update = GetDocument();
		update->UpdateAllViews(0);*/

		CClientDC* pDC = new CClientDC(this);
		CPen newPen(PS_SOLID, m_width, colorRef);
		CPen* pOldPen = (CPen*)pDC->SelectObject(&newPen);
		
		// Аналог UpdateAllViews():
		Invalidate();
		UpdateWindow();

		pDC->MoveTo(500, 500);
		pDC->LineTo(700, 300);
		pDC->MoveTo(700, 300);
		pDC->LineTo(500, 100);

		pDC->SelectObject(pOldPen);
		newPen.DeleteObject();
		pDC->DeleteDC();
	}
	// TODO: добавьте свой код обработчика команд
}


void CSDIMFCView::OnDialogclassDialOpen()
{
	CFileDialog FileO(TRUE);
	FileO.DoModal();
	FileO.GetFileName();
	// TODO: добавьте свой код обработчика команд
}


void CSDIMFCView::OnDialogclassDialSave()
{
	CFileDialog FileS(FALSE);
	FileS.DoModal();
	// TODO: добавьте свой код обработчика команд
}


void CSDIMFCView::OnDialogclassColor()
{
	CColorDialog dlg(RGB(255, 0, 0));

	if (dlg.DoModal() == IDOK) {
		COLORREF m_penColor = dlg.GetColor();

		// Если перерисовываем, то обновляем окно
		/*CSDIMFCDoc* update = GetDocument();
		update->UpdateAllViews(0);*/

		CClientDC* pDC = new CClientDC(this);
		CBrush newBrush(m_penColor);
		CBrush* pOldBrush = (CBrush*)pDC->SelectObject(&newBrush);
		CPen newPen(PS_SOLID, m_width, m_penColor);
		CPen* pOldPen = (CPen*)pDC->SelectObject(&newPen);
		
		Invalidate();
		UpdateWindow();		
		
		pDC->Rectangle(100, 100, 500, 500);

		pDC->SelectObject(pOldPen);
		newPen.DeleteObject();
		pDC->SelectObject(pOldBrush);
		newBrush.DeleteObject();
		pDC->DeleteDC();
	}

	
	// TODO: Add your command handler code here
}
