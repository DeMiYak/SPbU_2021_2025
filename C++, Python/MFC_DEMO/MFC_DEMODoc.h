// MFC_DEMODoc.h : interface of the CMFCDEMODoc class
//

#pragma once

#include"SampleModelling.h"
#include"BernHypGeomSampleGenerator.h"
#include"InvFunHypGeomSampleGenerator.h"
#include"Model.h"
#include"PLevelDlg.h"
#include"CritVolDlg.h"
#include"Method.h"
#include"Distribution.h"
#include"Chi2Histogram.h"

/// <summary>
/// Режим окна: определяет, какой график рисовать.
/// </summary>
enum WindowMode{CLOSED = 0, HIST = 1, PLEVEL = 2, CRITVOL = 3};

/// <summary>
///
/// </summary>
class CMFCDEMODoc : public CDocument
{
protected: // create from serialization only
	CMFCDEMODoc() noexcept;
	// CMFCDEMODoc(int whBalls, int blBalls, int pickNum);
	DECLARE_DYNCREATE(CMFCDEMODoc)

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
	virtual ~CMFCDEMODoc();
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

// BaseSampleGenerator fields
public:
	WindowMode Window = CLOSED;
	// Для гистограммы
	BaseSampleGenerator* samMod;
	Distribution d0;
	ChiSqHistogram chiSqHist;
	Method method;
	afx_msg void OnFrequencyModelling();
	afx_msg void OnFrequencyParameters();

public:
	// Для распределения p-level
	BaseSampleGenerator* pl_samMod;
	Method pl_method;
	Distribution pl_d0, pl_d1;
	int pl_repnum;
	double* p_levels;
	double p_distribution[20];
	void Simulate_P_Distribution();
	afx_msg void OnPlParameters();
	afx_msg void OnPlModelling();

public:
	// Для зависимости критерия мощности от уровня значимости
	BaseSampleGenerator* cv_samMod;
	Method cv_method;
	Distribution cv_d0, cv_d1;
	int cv_repnum;
	int critnum;
	double* powcrits;
	int from_sv;
	// int to_sv;
	int intrv_sv;
	double slvl;
	void Simulate_PowCrits();
	afx_msg void OnCvParameters();
	afx_msg void OnCvModelling();
};
