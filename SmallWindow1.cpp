// SmallWindow1.cpp : implementation file
//

#include "stdafx.h"
#include "DragonRaja.h"
#include "SmallWindow1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSmallWindow dialog


CSmallWindow::CSmallWindow(CWnd* pParent /*=NULL*/)
	: CDialog(CSmallWindow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSmallWindow)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CSmallWindow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSmallWindow)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSmallWindow, CDialog)
	//{{AFX_MSG_MAP(CSmallWindow)
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// CSmallWindow message handlers
BOOL CSmallWindow::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	m_BitmapBG.LoadBitmap(IDB_NC_BG);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CSmallWindow::OnEraseBkgnd(CDC* pDC) 
{
	CDC cdc;
	cdc.CreateCompatibleDC(pDC);
	cdc.SelectObject(m_BitmapBG);
	BITMAP bm;
	m_BitmapBG.GetObject(sizeof(BITMAP), &bm);
	
	const int iWidth = bm.bmWidth; 
	const int iHeight = bm.bmHeight;

	pDC->BitBlt(0, 0, iWidth, iHeight, &cdc, 0, 0, SRCCOPY);
	return 0;
}
