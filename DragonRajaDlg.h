// DragonRajaDlg.h : header file
//
//#define DEBUG_

#include "SmallWindow1.h"
#include "ServerSelect.h"

#if !defined(AFX_DRAGONRAJADLG_H__BAAD36A7_EB19_11D3_945D_004F4C04C094__INCLUDED_)
#define AFX_DRAGONRAJADLG_H__BAAD36A7_EB19_11D3_945D_004F4C04C094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

extern ULONGLONG ConvCTimeToInt( CTime *olg_time );

typedef struct _FILELIST {

	CString		filedir;
	CTime		*ftp_time;
	int			filesize;
	CString		filename;

	_FILELIST()
	{
		ftp_time = NULL;
		filesize = 0;
	}
} FILELIST;

typedef struct _FTPSERVER {

	char		filedir[MAX_PATH];
	CTime		filetime;
	int			filesize;
	char		filename[MAX_PATH];

	_FTPSERVER()
	{
		filesize = 0;
	}

} FTPSERVER;

/////////////////////////////////////////////////////////////////////////////
// CDragonRajaDlg dialog

class CDragonRajaDlg : public CDialog
{
// Construction
public:
	char ftp3[ MAX_PATH];
	CDragonRajaDlg(CWnd* pParent = NULL);	// standard constructor
	BOOL flag;
	bool bIsWorkThreadFin;
	char fullpathname[ MAX_PATH];
	int  ver;
	FILE *fp;
	char RootDir[ FILENAME_MAX];
	char text2[512];
	int totalcount;
	int totalsize ;
	float totaltime ;

	void Game();
	void MakeRealDir( char *dir, int c );
	void VerChk();
	void MyVersion();
	void changefile( CString filename, CTime time);
	BOOL m_bpStart;

	CServerSelect s_dlg;		// 서버 선택 메뉴
	CFTPMgr m_Ftp;
	CFTPMgr m_FtpDown;
// Dialog Data
	//{{AFX_DATA(CDragonRajaDlg)
	enum { IDD = IDD_DRAGONRAJA_DIALOG };
	
	CBitmapButton	m_ctrlGohomepage;
	CBitmapButton	m_ctrlCancel;
	CBitmapButton	m_ctrlOK;

	CProgressCtrl	m_ctrlProgress2;
	CListBox	m_totalsize;
	CListBox	m_files;
	CListBox	m_filename;
	CProgressCtrl	m_ctrlProgress;
	CListBox	m_Readme;
	CString	m_sCurrFileSize;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragonRajaDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CRgn Working,Temp;
	// Generated message map functions
	//{{AFX_MSG(CDragonRajaDlg)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnGohomepage();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	CBitmap m_bmpOK, m_bmpCancel, m_bmpNewID, m_bmpGohomepage, m_bmpUpdatenow, m_bmpStartgame;
	CBitmap m_BitmapBG;
	CSmallWindow m_dlg;
	void UpdateOkBtn(const bool bIsNeedUpdate);
};

UINT WINAPI ThreadFunc( LPVOID pParam );

UINT WINAPI SearchFile( LPVOID pParam );

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGONRAJADLG_H__BAAD36A7_EB19_11D3_945D_004F4C04C094__INCLUDED_)
