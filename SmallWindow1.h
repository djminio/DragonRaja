#if !defined(AFX_SMALLWINDOW1_H__BA121DCC_7E3C_459A_8B4A_7588BD27A23F__INCLUDED_)
#define AFX_SMALLWINDOW1_H__BA121DCC_7E3C_459A_8B4A_7588BD27A23F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SmallWindow1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSmallWindow dialog

class CSmallWindow : public CDialog
{
// Construction
public:
	CSmallWindow(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CSmallWindow)
	enum { IDD = IDD_SMALLWINDOW };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSmallWindow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSmallWindow)
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CBitmap m_BitmapBG;
	CBitmap m_BitmapBG2;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SMALLWINDOW1_H__BA121DCC_7E3C_459A_8B4A_7588BD27A23F__INCLUDED_)
