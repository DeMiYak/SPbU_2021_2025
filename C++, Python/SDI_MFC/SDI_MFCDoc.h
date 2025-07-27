
// SDI_MFCDoc.h: интерфейс класса CSDIMFCDoc 
//


#pragma once


class CSDIMFCDoc : public CDocument
{
protected: // создать только из сериализации
	CSDIMFCDoc() noexcept;
	DECLARE_DYNCREATE(CSDIMFCDoc)

// Атрибуты
public:

// Операции
public:

// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CSDIMFCDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int i;
	LOGPEN logPen;
	LOGBRUSH logBrush;

// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	int GetI();
	int AddI();
	afx_msg void OnHi();
	afx_msg void OnDrawChange();
//	afx_msg void OnChangecolorRed();
};
