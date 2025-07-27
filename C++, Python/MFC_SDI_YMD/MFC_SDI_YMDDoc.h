
// MFC_SDI_YMDDoc.h : interface of the CMFCSDIYMDDoc class
//


#pragma once
#include"SampleModelling.h"
#include"ModelDlg.h"

class CMFCSDIYMDDoc : public CDocument
{
protected: // create from serialization only
	CMFCSDIYMDDoc() noexcept;
	// CMFCSDIYMDDoc(int whBalls, int blBalls, int pickNum);
	DECLARE_DYNCREATE(CMFCSDIYMDDoc)

	// Attributes
public:

	// Operations
public:

	// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// Implementation
public:
	virtual ~CMFCSDIYMDDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

	// SampleModelling fields
public:
	SampleModelling* samMod;
	Distribution d1;
	Histogram hist;
	Method method;
	BOOL isOpenWindow = FALSE;
	afx_msg void OnDialogModelling();
	afx_msg void OnDialogParameters();
};

