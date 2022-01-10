#if !defined(AFX_SERVERSELECT_H__3EE16241_5894_4544_B43B_06081FE79B0A__INCLUDED_)
#define AFX_SERVERSELECT_H__3EE16241_5894_4544_B43B_06081FE79B0A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServerSelect.h : header file
//
#include "SmallWindow1.h"

#define MAX_SERVER_SET	20

struct CServerSet
{
	char m_szServerName[MAX_PATH];
	char m_szIp1[MAX_PATH];
	char m_szIp2[MAX_PATH];
	char m_szFtp1[MAX_PATH];
	char m_szFtp2[MAX_PATH];
	char m_szFtp3[MAX_PATH];
	char m_szFtp4[MAX_PATH];
	char m_szFtpId[MAX_PATH];
	int	 is_beta;
};

/////////////////////////////////////////////////////////////////////////////
// CServerSelect dialog

class CServerSelect : public CDialog
{
public:
	CFileStatus	m_DragonIniStatus;
	CServerSet *m_lpServerSet;
// Construction
public:
	CServerSelect(CWnd* pParent = NULL);   // standard constructor
// Dialog Data
	//{{AFX_DATA(CServerSelect)
	enum { IDD = IDD_SERVERSELECT };
	CListBox	m_selectserver;	
	CString	m_szTitleString;
	CBitmapButton m_btnOk;	
	CBitmapButton m_btnCancel;
	CBitmapButton m_btnHomePage;
	CBitmap m_BitmapBG;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CServerSelect)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CServerSelect)
	afx_msg void OnCancel();
	afx_msg void OnOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkServerselect();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnHomepage();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CSmallWindow m_dlg;
	void ReadServerSetInfo();
};

extern int MakeFolder();
#define CREATE_FOLDER_FILE_NAME		"CreateFolderName.txt"
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVERSELECT_H__3EE16241_5894_4544_B43B_06081FE79B0A__INCLUDED_)
