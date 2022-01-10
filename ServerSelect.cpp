// ServerSelect.cpp : implementation file
//

#include "stdafx.h"
#include <windows.h>
#include <direct.h>
#include "DragonRaja.h"
#include "ServerSelect.h"
#include "DragonRajaDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

void GetDragonini();
/////////////////////////////////////////////////////////////////////////////
// CServerSelect dialog
CServerSelect::CServerSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CServerSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CServerSelect)
	//}}AFX_DATA_INIT

	m_lpServerSet = NULL;
}


void CServerSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServerSelect)
	DDX_Control(pDX, IDC_SERVERSELECT, m_selectserver);	
	DDX_Control(pDX, ID_OK,	m_btnOk);	
	DDX_Control(pDX, ID_CANCEL, m_btnCancel);	
	DDX_Control(pDX, ID_HOMEPAGE, m_btnHomePage);	
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServerSelect, CDialog)
	//{{AFX_MSG_MAP(CServerSelect)
	ON_BN_CLICKED(ID_OK, OnOk)
	ON_LBN_DBLCLK(IDC_SERVERSELECT, OnDblclkServerselect)
	ON_WM_ERASEBKGND()
	ON_BN_CLICKED(ID_HOMEPAGE, OnHomepage)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(ID_CANCEL, OnCancel)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServerSelect message handlers
void CServerSelect::OnCancel() 
{
	CDialog::OnCancel();	
}

void CServerSelect::OnOk() 
{
	OnDblclkServerselect();
	//CDialog::OnOK();
}

char* EatRearWhiteChar( char* pStr )
{	
	char*	szWhite = " \t\n\r";
	char*	pRear;
	
	pRear = pStr + strlen( pStr ) - 1;
	if ( pRear )
	{
		while ( pStr <= pRear )
		{
			if ( strchr( szWhite, *pRear ) )
			{
				*pRear-- = 0;
			}
			else
			{
				break;
			}
		}
	}
	
	return	pStr;
}	

void ConveString( char *str, const char *conv )
{
	char *temp;
	while( temp = strstr( str, conv ) )
	{
		*temp = '\r';
		temp++;
		*temp = '\n';
	}
}

void GetTitleString( CString &string )
{
	FILE *fp = fopen( "./title.txt", "rt" );
	if( !fp ) return;

	string.Empty();
	char temp[512];
	while( fgets( temp, 512, fp ) )
	{
		EatRearWhiteChar( temp );
		if( temp[0] ) 
		{
			ConveString( temp, "\\n");
			string += temp;
		}		
	}
	fclose( fp );
}


char *ini_name = "./dragon.ini";
BOOL CServerSelect::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_dlg.Create(IDD_SMALLWINDOW, this);
	m_dlg.CenterWindow();
	m_dlg.ShowWindow(SW_SHOW);
	m_dlg.UpdateWindow(); 

	m_BitmapBG.LoadBitmap(IDB_SS_BG);	

	m_btnCancel.LoadBitmaps(IDB_SS_CANCEL_NORMAL,IDB_SS_CANCEL_DOWN,IDB_SS_CANCEL_NORMAL,IDB_SS_CANCEL_NORMAL);
	m_btnCancel.SizeToContent();
	m_btnOk.LoadBitmaps(IDB_SS_OK_NORMAL,IDB_SS_OK_DOWN,IDB_SS_OK_NORMAL,IDB_SS_CANCEL_NORMAL);
	m_btnOk.SizeToContent();
	m_btnHomePage.LoadBitmaps(IDB_SS_HP_NORMAL,IDB_SS_HP_DOWN,IDB_SS_HP_NORMAL,IDB_SS_CANCEL_NORMAL);
	m_btnHomePage.SizeToContent();

	ReadServerSetInfo();

	m_selectserver.SetCurSel( 0 );	

	m_dlg.DestroyWindow();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

extern char g_ftp_id[MAX_PATH];
int g_IsBeta;		// 선택한게 베타인가..

void CServerSelect::OnDblclkServerselect()
{
	CFile::GetStatus( ini_name, m_DragonIniStatus );		// 시간을 읽어오고

	int index = m_selectserver.GetCurSel();
	if( index == LB_ERR ) index = 0;

	if( m_lpServerSet[index].m_szFtp1[0] )
	{
		::WritePrivateProfileString( "network", "ftp1", m_lpServerSet[index].m_szFtp1, ini_name );
		::WritePrivateProfileString( "network", "ftp2", m_lpServerSet[index].m_szFtp2, ini_name );
		::WritePrivateProfileString( "network", "ftp3", m_lpServerSet[index].m_szFtp3, ini_name );
		::WritePrivateProfileString( "network", "ftp4", m_lpServerSet[index].m_szFtp4, ini_name );
		::strcpy( g_ftp_id, m_lpServerSet[index].m_szFtpId );
		//WritePrivateProfileString( "network", "ftpID", m_lpServerSet[index].m_szFtpId, ini_name );
	}

	if( m_lpServerSet[index].m_szIp1[0] )
	{
		::WritePrivateProfileString( "network", "host1", m_lpServerSet[index].m_szIp1, ini_name );
		::WritePrivateProfileString( "network", "host2", m_lpServerSet[index].m_szIp2, ini_name );
	}

	// 선택한 서버셋//010706 lms
	CString server_set;
	server_set.Format( "%d", index );
	::WritePrivateProfileString( "network", "ServerSet", server_set, ini_name );

	FILE *fp = fopen( "./beta.ini", "wt" );
	if( fp ) 
	{
		::fprintf( fp, "%d", m_lpServerSet[index].is_beta );
		::fclose( fp );
	}
	g_IsBeta = m_lpServerSet[index].is_beta;		// 저장해 두고 나중에 게임 실행파일 실행시킬때 이용한다.
//	CFile::SetStatus( ini_name, m_DragonIniStatus );		// ini의 시간을 원래로 돌려놓는다.
	CDialog::OnOK();
}

int CheckBeta()
{
	return g_IsBeta;
}
void GetDragonini()			// 초기에 ini 값을 가져온다.
{
	CFTPMgr FtpMgr;
	char tempd[ MAX_PATH]={0,};
	char fullpathname[ MAX_PATH]={0,};
	char ftp1[ MAX_PATH]={0,};
	char ftp2[ MAX_PATH]={0,};
	::_getcwd( tempd , MAX_PATH );
	::sprintf( fullpathname, "%s/dragon.ini", tempd );
	::GetPrivateProfileString( "network", "ftp1", "", ftp1, MAX_PATH, fullpathname );	
	::GetPrivateProfileString( "network", "ftp2", "", ftp2, MAX_PATH, fullpathname );	
	if( ftp1[0] == 0 || ftp2[0] == 0) 
	{
		AfxMessageBox("Re-Install Please.");
		::PostQuitMessage(0);
	}
	DeleteFile( "./$$dragon.ini" );

#ifdef USA_LOCALIZING_
	FtpMgr.Connect(ftp1, "dragon2", "raja");
#else
	FtpMgr.Connect(ftp1, "dragon1", "raja");
#endif


	if(!FtpMgr.GetFile("./dragon.ini","./$$dragon.ini"))
	{
		::exit(0);
	}

	DeleteFile( "./dragon.ini" );
	MoveFile( "./$$dragon.ini", "./dragon.ini" );


	FtpMgr.Close();
}

int MakeFolder()
{
	FILE *fp;
	char szFolderName[1024];
	if( NULL == (fp = fopen( CREATE_FOLDER_FILE_NAME, "rt" )) )	return -1;	

	while( fgets( szFolderName, 1024, fp ) )
	{
		if( szFolderName[0] == ' '|| szFolderName[0] == NULL || szFolderName[0] == '\n' || szFolderName[0] == ';' || szFolderName[0] == '#' ) continue;
		EatRearWhiteChar( szFolderName );
		if( !CreateDirectory( szFolderName, NULL ) )
		{
#ifdef _DEBUG
			//AfxMessageBox( "Error MakeFolder" );
#endif
		}
 		
	}
	fclose( fp );
	return 1;
}

BOOL CServerSelect::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
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

void CServerSelect::OnHomepage() 
{// TODO: Add your control notification handler code here
	char szCWD[ MAX_PATH] = {0,};
	::_getcwd( szCWD , MAX_PATH );
	
	char szIniAddress[MAX_PATH] = {0,};
	::sprintf( szIniAddress, "%s/dragon.ini", szCWD );

	char szHomePage[MAX_PATH] = {0,};
	::GetPrivateProfileString( "network","HomePage", "http://moonraja.freeforums.org/", szHomePage, MAX_PATH, szIniAddress);

	::ShellExecute(m_hWnd,"open",szHomePage,NULL,NULL,SW_SHOWNORMAL);
}

BOOL CServerSelect::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			{
				OnDblclkServerselect();
				return 0;
			}break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

void CServerSelect::ReadServerSetInfo() 
{
	GetDragonini();
	
	int server_count = GetPrivateProfileInt( "network", "server_count", 0, ini_name );
	if( !server_count )		// 베타 서버 없을때	
	{
		OnOK();
		return;
	}

	CFile file;
	int ret = file.GetStatus( ini_name, m_DragonIniStatus );
	if( !ret ) 
	{
		OnCancel();
		return;
	}

	m_lpServerSet = new CServerSet[server_count];
	char temp_server_str[20];
	char *get_str;
	for( int i=1; i<=server_count; i++ )		// name1_ftp1을 그냥 ftp1으로 바꿔 세팅하고 제어를 넘겨준다.
	{
		sprintf( temp_server_str, "name%d", i );
		get_str = m_lpServerSet[i-1].m_szServerName;
		GetPrivateProfileString("network", temp_server_str, "", get_str, MAX_PATH, ini_name ); 

		sprintf( temp_server_str, "name%d_ftp1", i );
		get_str = m_lpServerSet[i-1].m_szFtp1;
		GetPrivateProfileString("network", temp_server_str, "", get_str, MAX_PATH, ini_name); 
		
		sprintf( temp_server_str, "name%d_ftp2", i );
		get_str = m_lpServerSet[i-1].m_szFtp2;
		GetPrivateProfileString("network", temp_server_str, "", get_str, MAX_PATH, ini_name); 

		sprintf( temp_server_str, "name%d_ftp3", i );
		get_str = m_lpServerSet[i-1].m_szFtp3;
		GetPrivateProfileString("network", temp_server_str, "", get_str, MAX_PATH, ini_name); 
		
		sprintf( temp_server_str, "name%d_ftp4", i );
		get_str = m_lpServerSet[i-1].m_szFtp4;
		GetPrivateProfileString("network", temp_server_str, "", get_str, MAX_PATH, ini_name); 

		sprintf( temp_server_str, "name%d_ftpID", i );
		get_str = m_lpServerSet[i-1].m_szFtpId;
		GetPrivateProfileString("network", temp_server_str, "", get_str, MAX_PATH, ini_name);

		sprintf( temp_server_str, "name%d_host1", i );
		get_str = m_lpServerSet[i-1].m_szIp1;
		GetPrivateProfileString("network", temp_server_str, "", get_str, MAX_PATH, ini_name); 
		
		sprintf( temp_server_str, "name%d_host2", i );
		get_str = m_lpServerSet[i-1].m_szIp2;
		GetPrivateProfileString("network", temp_server_str, "", get_str, MAX_PATH, ini_name); 


		sprintf( temp_server_str, "name%d_beta", i );
		m_lpServerSet[i-1].is_beta = GetPrivateProfileInt( "network", temp_server_str, 0, ini_name );

		m_selectserver.AddString( m_lpServerSet[i-1].m_szServerName );		
	}
}

HBRUSH CServerSelect::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

    switch(nCtlColor) 
	{
    case CTLCOLOR_STATIC:
		{
			// The Slider Control has CTLCOLOR_STATIC, but doesn't let
			// the background shine through,
//			TCHAR lpszClassName[255];
//			GetClassName(pWnd->m_hWnd, lpszClassName, 255);
//			if(_tcscmp(lpszClassName, TRACKBAR_CLASS) == 0)
//			{
//				return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
//			}
		}break;
//	case CTLCOLOR_STATIC:
	case CTLCOLOR_SCROLLBAR:
	case CTLCOLOR_LISTBOX:
//  case CTLCOLOR_BTN:
		{
//			pDC->SetBkColor(RGB(230, 230, 230)) ;
//			pDC->SetTextColor(RGB(25,25,25));
//			pDC->SetBkMode(TRANSPARENT);
//			CBrush MyBrush;
//			MyBrush.CreateStockObject(NULL_BRUSH);
//			hbr = MyBrush;
			return hbr;
		}break;
    default:
        break;
    }
    
    // if we reach this line, we haven't set a brush so far
    return CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
}

void CServerSelect::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CDialog::OnPaint() for painting messages
}
