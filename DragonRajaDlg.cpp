#include "stdafx.h"
#include "DragonRaja.h"
#include "DragonRajaDlg.h"
#include <direct.h>
#include <Process.h>
#include <windows.h>
#include <wininet.h>
#pragma comment(lib, "wininet.lib")

#include <Process.h>

#include "DebugLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define LENGTH	20000
#define MAX_FILES__			60000

int FirstRun = 1;
int count2 = 0;
int totalcount=0;
FTPSERVER ftpserver[LENGTH];
FILELIST filelist[LENGTH];
CString g_CurrGetFileName;		// 현재 ftp server에서 받아 오고 있는 파일
int		g_CurrFileSize;			// 현재 ftp server에서 받아 오고 있는 파일의 사이즈

extern void DeleteComma( char *text );
void ReconnectForDownload();


extern void SaveGetFileName( FILELIST *filelist, int nMaxCount );



//시간측정 매크로
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CHECK_TIME_START __int64 freq, start, end; if (QueryPerformanceFrequency((_LARGE_INTEGER*)&freq)) {QueryPerformanceCounter((_LARGE_INTEGER*)&start); 
#define CHECK_TIME_END(a,b) QueryPerformanceCounter((_LARGE_INTEGER*)&end); a=(float)((double)(end - start)/freq*1000); b=TRUE; } else b=false;
float Time; 
BOOL err;
int dirsize;//시간측정을 위한 사이즈 


CDragonRajaDlg::CDragonRajaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDragonRajaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDragonRajaDlg)
	m_sCurrFileSize = _T("");
	m_bpStart = 1;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CDragonRajaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDragonRajaDlg)
	DDX_Control(pDX, IDC_GOHOMEPAGE, m_ctrlGohomepage);
	DDX_Control(pDX, IDCANCEL, m_ctrlCancel);
	DDX_Control(pDX, IDOK, m_ctrlOK);
	DDX_Control(pDX, IDC_PROGRESS2, m_ctrlProgress2);
	DDX_Control(pDX, IDC_LIST4, m_totalsize);
	DDX_Control(pDX, IDC_LIST3, m_files);
	DDX_Control(pDX, IDC_LIST1, m_filename);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
	DDX_Control(pDX, IDC_README, m_Readme);
	DDX_Text(pDX, IDC_EDIT1, m_sCurrFileSize);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDragonRajaDlg, CDialog)
	//{{AFX_MSG_MAP(CDragonRajaDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_SYSCOMMAND()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_GOHOMEPAGE, OnGohomepage)
	ON_WM_DRAWITEM()
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

int temp_flag = 0;


BOOL CDragonRajaDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	g_CrashLog.Init(OUTPUT_JUST_FILE,"ClientCrash");//모드 셋팅 기록 될 파일의 고유 이름입니다.

	m_dlg.Create(IDD_SMALLWINDOW, this);
	m_dlg.CenterWindow();
	m_dlg.ShowWindow(SW_SHOW);
	m_dlg.UpdateWindow(); 

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	m_BitmapBG.LoadBitmap(IDB_DN_BG);	

	m_ctrlGohomepage.LoadBitmaps(IDB_SS_HP_NORMAL,IDB_SS_HP_DOWN,IDB_SS_HP_NORMAL,IDB_SS_HP_NORMAL);
	m_ctrlGohomepage.SizeToContent();
	
	m_ctrlCancel.LoadBitmaps(IDB_DN_CANCEL_NORMAL,IDB_DN_CANCEL_DOWN,IDB_DN_CANCEL_NORMAL,IDB_DN_CANCEL_NORMAL);
	m_ctrlCancel.SizeToContent();

	UpdateOkBtn(true);

	VerChk();

	m_dlg.DestroyWindow();	

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CDragonRajaDlg::MakeRealDir( char *dir, int c )
{
	strcpy( text2, dir + strlen( RootDir )  );
	strcat( text2, "/" );
}

char ftp1[ MAX_PATH] = {0,};
char ftp2[ MAX_PATH] = {0,};
char g_ftp_id[ MAX_PATH]= {0,};

extern void ConvertSpecialWord(char *txt,const char *delTarget,const char AfterConvert);
extern char* EatRearWhiteChar( char* pStr );

void CDragonRajaDlg::VerChk()
{
	int my_ver=0;
	flag = false;
	bIsWorkThreadFin = false;
	char tempd[ MAX_PATH];
	memset(ftpserver,0, sizeof(FTPSERVER)*LENGTH);
	DeleteFile( "./$$dir.txt" );
	DeleteFile( "./$$readme.txt" );
	DeleteFile( "./$$dragon.ini" );
	DeleteFile( CREATE_FOLDER_FILE_NAME );

	::_getcwd( tempd , MAX_PATH );
	sprintf( fullpathname, "%s/dragon.ini", tempd );
	my_ver = GetPrivateProfileInt( "network", "ver", 0, fullpathname );
	GetPrivateProfileString( "network", "ftp1", "", ftp1, MAX_PATH, fullpathname );	
	GetPrivateProfileString( "network", "ftp2", "", ftp2, MAX_PATH, fullpathname );	
	if( my_ver == 0 || ftp1[0] == 0 || ftp2[0] == 0) 
	{
		::AfxMessageBox("Re-Install Please.");
		::PostQuitMessage(0);
	}
#ifdef USA_LOCALIZING_
	m_Ftp.Connect(ftp1,"dragon2", "raja"); // USA define use this password " raja" ===> dragon2 mean user for FTP server  /// password is "raja" in dragon.ini client same password of FTP server change it if you want
#else
	m_Ftp.Connect(ftp1,g_ftp_id, "raja"); 
#endif

	if(!m_Ftp.GetFile("./dir.txt","./$$dir.txt"))
	{
		::PostQuitMessage(0);
	}

	if(m_Ftp.GetFile(CREATE_FOLDER_FILE_NAME, CREATE_FOLDER_FILE_NAME,false))
	{
		MakeFolder();
	}

	CFile file;
	CFileStatus file_status1;
	file.GetStatus( "./$$dir.txt", file_status1 );
	dirsize = 0;
	dirsize = file_status1.m_size;
	::printf("%8.6f",Time);

	fp = ::fopen( "./$$dir.txt", "rt" );

	while( !feof( fp ) )
	{
		char temp2[FILENAME_MAX] = {0,};
		::fgets( temp2, FILENAME_MAX, fp );
		::EatRearWhiteChar( temp2 );

		char *token = NULL;
		bool firstdir = false;

		while( 1 )
		{
			char text[512] = {0,};
			char *t = fgets( text, 512, fp );
			EatRearWhiteChar( text );

			if( t == NULL ) break;

#if defined (TAIWAN_LOCALIZING_) || defined (HONGKONG_LOCALIZING_)
			if( text[0] == ' ' && text[8] > 'A' && text[9] == ':' )  // 디렉토리..//for taiwan
#else
	#ifdef ENGLISH_WINDOW
			if( text[0] == ' ' && text[14] > 'A' && text[15] == ':' )  // 디렉토리..
	#else	
			if( text[0] == ' ' && text[1] > 'A' && text[2] == ':' )  // 디렉토리..
	#endif	// ENGLISH_WINDOW
#endif
			{
				token = ::strtok( text, " " );
#if defined (TAIWAN_LOCALIZING_) || defined (HONGKONG_LOCALIZING_)
				token = ::strtok( NULL, " " );//for taiwan
#else
	#ifdef ENGLISH_WINDOW
				token = ::strtok( NULL, " " );//for english
				token = ::strtok( NULL, " " );//for english
	#endif
#endif
				text2[0] = 0 ;

				if( firstdir == false ) 
				{
					strcpy( RootDir, token );
					
					firstdir = true;
				}

				MakeRealDir( token, count2 );
			}
#ifdef ENGLISH_WINDOW
			else if( text[0] == '0' || text[0] == '1' ) // 화일 or 디렉토리..
#else
			else if( text[0] == '1' || text[0] == '2' ) // 화일 or 디렉토리..
#endif
			{
				::memcpy(ftpserver[count2].filedir, text2, strlen(text2)+1 );
				::ConvertSpecialWord(ftpserver[count2].filedir,"\\",'/');

//				char *min_s;
				int min = 0;
#ifdef TAIWAN_LOCALIZING_
				int year	= ::atoi(::strtok( text, " /" ));//for taiwan
				int mon		= ::atoi(::strtok( NULL, " /" ));//for taiwan
				int day		= ::atoi(::strtok( NULL, " /" ));//for taiwan
				int hour	= ::atoi(::strtok( NULL, " /:" ));//for taiwan
				char* min_s	= ::strtok( NULL, " -:" ); //for taiwan
#else
	#ifdef ENGLISH_WINDOW		// MM/DD/YY
				int mon		= ::atoi(::strtok( text, " /" ));
				int day		= ::atoi(::strtok( NULL, " /" ));
				int year	= ::atoi(::strtok( NULL, " " ));
				int hour	= ::atoi(::strtok( NULL, " :" ));
				char* min_s	= ::strtok( NULL, " " ); 
	#else	
				int year	= ::atoi(::strtok( text, " -" ));
				int mon		= ::atoi(::strtok( NULL, " -" ));
				int day		= ::atoi(::strtok( NULL, " -" ));
				int hour	= ::atoi(::strtok( NULL, " -:" ));
				char* min_s	= ::strtok( NULL, " -:" ); 
	#endif	// ENGLISH_WINDOW
#endif

#if defined ( CHINA_LOCALIZING_ ) //|| defined (HONGKONG_LOCALIZING_ )
				min = atoi( min_s );
#else
				if(min_s[2] =='a')
				{
					if( hour == 12 )//오전 12시일 경우
					{
						min_s[2] = 0;
						min = atoi( min_s);
						hour -= 12;
					}
					else
					{
						min_s[2] = 0;
						min = atoi( min_s);
					}
				}
				else
				{
					if( hour == 12 )//오후 12시일 경우
					{
						min_s[2] = 0;
						min = atoi( min_s);
					}
					else
					{
						min_s[2] = 0;
						min = atoi( min_s);
						hour += 12;
					}
				}
#endif
				token = ::strtok( NULL, " " );
				if( token[0] == '<' ) 
				{

					continue;
				}
				else	// 화일 Size..
				{
					DeleteComma( token );
					ftpserver[count2].filesize = atoi( token );
				}

				token = ::strtok( NULL, " " ); // 드디어, 화일을 읽었다.
				memcpy(ftpserver[count2].filename, token, strlen(token));
				::ConvertSpecialWord(ftpserver[count2].filename,"\\",'/');

				CTime temp_time( year, mon, day, hour, min, 0 );
				ftpserver[count2].filetime = temp_time;

				count2++;
			}

		}
		fclose ( fp );

		DeleteFile( "$$dir.txt" );
		UpdateOkBtn(true);
		
		// 010904 YGI
		m_filename.ResetContent();
		m_filename.AddString( "searching files...   ." );
		UINT dwThreadId = 0;
		HANDLE hThread = (HANDLE)::_beginthreadex(NULL,0,SearchFile,this,0,&dwThreadId);
		return;
	}
}

extern int CheckBeta();
void CDragonRajaDlg::Game()
{
	DeleteFile( "$$readme.txt" );
	DeleteFile( "$$dir.txt" );

	int t = __argc;

	char dis[2];
	sprintf(dis,"%d",__argc);

	char bin_file[20];
	
	if( CheckBeta() == 1 )		// 베타 이면
	{
		strcpy( bin_file, "dragonraja_b.bin" );
	}
	else 
	{
		strcpy( bin_file, "dragonraja.bin" );
	}

	if(  __argc > 1 ) 
	{
		switch( __argc )
		{ 
			
		case 2 :	_execlp( bin_file, bin_file, __argv[1],								NULL );break;
		case 3 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],						NULL );break;
		case 4 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],			NULL );break;
		case 5 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],	NULL );break;
		case 6 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						NULL );break;
		case 7 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],NULL );break;

		case 8 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],__argv[7],NULL );break;

		case 9 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],__argv[7],__argv[8],NULL );break;

		case 10 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],	
						__argv[6],__argv[7],__argv[8],__argv[9],NULL );break;

		case 11 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],__argv[7],__argv[8],__argv[9],__argv[10],NULL );break;

		case 12 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],__argv[7],__argv[8],__argv[9],__argv[10],__argv[11],NULL );break;

		case 13 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],__argv[7],__argv[8],__argv[9],__argv[10],__argv[11],__argv[12],NULL);break;
 
		case 14 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],__argv[7],__argv[8],__argv[9],__argv[10],__argv[11],__argv[12],__argv[13],
						NULL);break; 

		case 15 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],__argv[7],__argv[8],__argv[9],__argv[10],__argv[11],__argv[12],__argv[13],
						__argv[14],NULL);break;

		case 16 :	_execlp( bin_file, bin_file, __argv[1],__argv[2],__argv[3],__argv[4],__argv[5],
						__argv[6],__argv[7],__argv[8],__argv[9],__argv[10],__argv[11],__argv[12],__argv[13],
						__argv[14],__argv[15],NULL);break;
		}
	}
	else
	{ 
		_execlp( bin_file, "0", NULL );
	}
	::PostQuitMessage(0);
}


extern BOOL DumpException(LPEXCEPTION_POINTERS lpExcep,char* szOutMsg);

void CDragonRajaDlg::OnOK() 
{
	EXCEPTION_POINTERS* pException = NULL;//020508 lsw	
	__try	//020514 lsw
	{
	if(flag) 
	{
		if(bIsWorkThreadFin) 
		{
			Game();
		}
	}
	else 
	{
		// 010904 YGI
		if(bIsWorkThreadFin)
		{
			bIsWorkThreadFin = false;

			m_Ftp.Close();

			char buffer[MAX_PATH] = {0,};
			char fullpathname[MAX_PATH] = {0,};
			char ftp4[ MAX_PATH] = {0,};
			::_getcwd(buffer, MAX_PATH);
			::sprintf(fullpathname,	"%s/dragon.ini", buffer);

			int down_load_size = ::GetPrivateProfileInt( "option", "DownLoadSize", 0, fullpathname );

			if( !down_load_size ) down_load_size = 1024*1024*50;		// 50M 만 받는다.

//			if( down_load_size == 9999 || totalsize <= down_load_size )		// 무한대로 받는다.
			{
				::GetPrivateProfileString("network", "ftp3", "", ftp3, MAX_PATH, fullpathname);
				::GetPrivateProfileString("network", "ftp4", "", ftp4, MAX_PATH, fullpathname);
				if(ftp3[0]==0 || ftp4[0] ==0)	
				{
					::AfxMessageBox("Reinstall Please");
					::PostQuitMessage(0);
				}
				UINT dwThreadId = 0;
				flag = true;//버튼을 다시 눌러도 실행되지 않게
				HANDLE hThread = (HANDLE)::_beginthreadex(NULL,0,ThreadFunc,this,0,&dwThreadId);
			}
		}
	}

	DeleteFile( "$$dir.txt" );
	DeleteFile( "$$readme.txt" );
	DeleteFile( "*.tmp");
//	CDialog::OnOK();
	}
	__except(pException = GetExceptionInformation())//020508 lsw
	{
		::DumpException( pException, "Exception Raised on WinMain()");		
	}
}



void CDragonRajaDlg::OnCancel() 
{
	DeleteFile( "$$dir.txt" );
	DeleteFile( "$$readme.txt" );
	DeleteFile("*.tmp");

	
	CDialog::OnCancel();
}

void CDragonRajaDlg::OnGohomepage() 
{
	char szCWD[ MAX_PATH] = {0,};
	::_getcwd( szCWD , MAX_PATH );
	
	char szIniAddress[MAX_PATH] = {0,};
	::sprintf( szIniAddress, "%s/dragon.ini", szCWD );

	char szHomePage[MAX_PATH] = {0,};
	::GetPrivateProfileString( "network","HomePage", "http://www.moonraja.freeforums.org", szHomePage, MAX_PATH, szIniAddress);

	::ShellExecute(m_hWnd,"open",szHomePage,NULL,NULL,SW_SHOWNORMAL);
}

void DeleteComma( char *text )
{
	char *temp_ch = strchr( text, ',' );
	if( !temp_ch ) return;

	int len = strlen( temp_ch );

	memmove( temp_ch, temp_ch+1, len );
	DeleteComma( text );
}

ULONGLONG ConvCTimeToInt( CTime *olg_time )
{
	ULONGLONG tt, tt1;
	int year, month, day, hour, min;
	int month_tbl[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };	

	year = olg_time->GetYear()- 1601;
	month = olg_time->GetMonth()- 1;
	day = olg_time->GetDay()- 1;
	hour = olg_time->GetHour();
	min = olg_time->GetMinute();

	CString imsi_time = olg_time->Format( "%Y-%m-%d %H:%M" );

	tt = (ULONGLONG) year * 365 *  24 * 60 * 60 * 10000 +
		(ULONGLONG) month_tbl[month]  *  24 * 60 * 60 * 10000 +     
		(ULONGLONG) day  *  24 * 60 * 60 * 10000 +     
		(ULONGLONG) hour * 60 * 60 * 10000 +     
		(ULONGLONG) min * 60 * 10000;

	tt1 = olg_time->GetTime();
	return tt;
}

void CDragonRajaDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDialog::OnLButtonDown(nFlags, point);
	PostMessage(WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(point.x,point.y));
}

void ConvertSpecialWord(char *txt,const char *delTarget,const char AfterConvert)
{
	char *pdest = txt;
	while( pdest = strstr(pdest,delTarget) )
	{
		*pdest = AfterConvert;
		pdest++;
	} 
}

UINT WINAPI SearchFile( LPVOID pParam )
//void CDragonRajaDlg::SearchFile(FTPSERVER ftpserver[], LPCTSTR pstr, int count2)
{
	CDragonRajaDlg *dlg = (CDragonRajaDlg*) pParam;

	int i;
	int j = 1;
	CFileFind finder;
	CString strName;
	DWORD length;
	CTime time;
	CString strTime, strPath;
	CString str;
	CString string;	
	dlg->totalsize = 0;
	dlg->totaltime = 0;
	dlg->totalcount=0;
	char pstr[ MAX_PATH];
	::_getcwd( pstr , MAX_PATH );
	::ConvertSpecialWord(pstr,"\\",'/');
////////////////////////////////////////////////////////////////////////////////////////////////////////
	char sentence[200];

	if(!dlg->m_Ftp.GetFile("./readme.txt","./$$readme.txt"))
	{
		return 0;
	}
	
	FILE *fp1 = fopen( "./$$readme.txt", "rt" );

	while( !feof(fp1))
	{
		if( fgets ( sentence, 200, fp1) == NULL ) break;
		for ( int i=0; sentence[i]; i++)
		{
			if ( sentence[i] == '\n' )
			{
				sentence[i] = 0;
				break;
			}
		}
		dlg->m_Readme.AddString( sentence );

	}
	fclose ( fp1 );
	DeleteFile("$$readme.txt");
	DeleteFile("$$dir.txt");


////////////////////////////////////////////////////////////////////////////////////////////////////
	// 010904 YGI
	CString view_ing;
	int para;
	static int view_flag = 0;

	for(i = 0; i<count2; i++)
	{
		para = (i/300)%15;
		if( view_flag != para )
		{
			view_flag = para;
			view_ing = "Searching files";
			for( int j=0; j< para; j++ ) 
			{
				view_ing+='.';
			}

			dlg->m_filename.ResetContent();
			dlg->m_filename.AddString( view_ing );
		}	

		str.Format("%s%s%s", pstr, ftpserver[i].filedir, ftpserver[i].filename);
		BOOL bWorking = finder.FindFile(str);

		if(bWorking)
		{
			bWorking = finder.FindNextFile();
			filelist[j].filename = finder.GetFileName();
			length = finder.GetLength();
			filelist[j].filesize = length;
			finder.GetLastWriteTime(time);

			int sec = (ftpserver[i].filetime.GetTime() - time.GetTime());
			sec /= 60;

			if(	!sec &&	(ftpserver[i].filesize == filelist[j].filesize) )//크기가 같다면
			{
				continue;
			}
		}

		if ( !::stricmp(ftpserver[i].filename,  "dir.txt" ) ) continue;
		if ( !::stricmp(ftpserver[i].filename,  "dir.bat" ) ) continue;
		if ( !::stricmp(ftpserver[i].filename,  "readme.txt" ) ) continue;
		if ( !::stricmp(ftpserver[i].filename,  "dragon.ini" ) ) continue;
		if ( !::stricmp(ftpserver[i].filename,  CREATE_FOLDER_FILE_NAME ) ) continue;

		if ( !::stricmp(ftpserver[i].filename,  "DragonRaja.b" ) )
		{
			DeleteFile( "./DragonRaja.b" );
			finder.FindFile("./DragonRaja.exe");
			finder.FindNextFile();
			filelist[j].filename = finder.GetFileName();
			length = finder.GetLength();
			filelist[j].filesize = length;
			finder.GetLastWriteTime(time);

			int sec = (ftpserver[i].filetime.GetTime() - time.GetTime());
			sec /= 60;
			if(	!sec &&	(ftpserver[i].filesize == filelist[j].filesize) )//크기가 같다면
			{
				continue;
			}
		}

		filelist[j].filename = ftpserver[i].filename;
		filelist[j].filesize = ftpserver[i].filesize;
		filelist[j].filedir = ftpserver[i].filedir;
		filelist[j].ftp_time = &ftpserver[i].filetime;

		dlg->totalcount = j ;
		dlg->totalsize += ftpserver[i].filesize; 
		j++;
	}
	finder.Close();
	/////////////////////////////////////////////////////////////////
#ifdef _DEBUG
	SaveGetFileName( filelist, dlg->totalcount );
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////
	dlg->totaltime = (Time/100)*(dlg->totalsize)/dirsize;

	// 010904 YGI
	dlg->m_filename.ResetContent();
	if(dlg->totaltime<60)
	{
		string.Format("Forcast Time : About %d Sec", (int)dlg->totaltime);
		dlg->m_filename.AddString(string);
	}		
	else
	{
		string.Format("Forcast Time : About %d Min", (int)dlg->totaltime/60);
		dlg->m_filename.AddString(string);
	}
	string.Format( ("File Count : %d "), dlg->totalcount);
	dlg->m_files.AddString(string);
	string.Format("Total Size : %d Kb", dlg->totalsize/1024);
	dlg->m_totalsize.AddString(string);

	if(dlg->totalcount > 0) 
	{
		dlg->flag = false; 
		dlg->bIsWorkThreadFin = true;
	}
	else
	{
		dlg->flag = true; 
		dlg->bIsWorkThreadFin = true;

		dlg->m_filename.ResetContent();
		dlg->m_filename.AddString( "Download Finished... " );
		dlg->m_sCurrFileSize.Empty();
		dlg->m_files.ResetContent();
		dlg->m_totalsize.ResetContent();

		dlg->UpdateOkBtn(false);
	}

	return 0;
}



int CurrSize=0;

UINT WINAPI ThreadFunc( LPVOID pParam )
{
	CDragonRajaDlg *dlg = (CDragonRajaDlg*) pParam;

#ifdef USA_LOCALIZING_
	dlg->m_FtpDown.Connect(dlg->ftp3, "dragon2", "raja");
#else
	dlg->m_FtpDown.Connect(dlg->ftp3, g_ftp_id, "raja");
#endif

	char jpercount[35] = {0,};
	CString strPathName = "";
	CString str = "";

	dlg->SetTimer(1, 10, NULL);
	dlg->m_ctrlProgress.SetRange( 0, dlg->totalcount);//파일 전체에 대한 프로그래시브바

	int i = 1;
	while( i<=dlg->totalcount )
	{	
		char tempname[FILENAME_MAX]	=	{0,};
		char DataPath[FILENAME_MAX]	=	{0,};
		char DataName[FILENAME_MAX]	=	{0,};
		char FullPathName[FILENAME_MAX]	=	{0,};

		strPathName = filelist[i].filedir + filelist[i].filename;

		::sprintf ( tempname, "%d.tmp" , i );

		dlg->m_filename.ResetContent();
		dlg->m_filename.AddString(filelist[i].filedir+filelist[i].filename);

		::sprintf ( jpercount, "Received Files : %d/%d", i, dlg->totalcount );	
		dlg->m_files.ResetContent();
		dlg->m_files.AddString( jpercount );

		::DeleteFile( tempname );

		dlg->m_bpStart = FALSE;
		g_CurrGetFileName = tempname;
		g_CurrFileSize = filelist[i].filesize;
		dlg->m_ctrlProgress2.SetRange( 0, 100);//현재받는 파일의 프로그래시브바 설정

		dlg->m_totalsize.ResetContent();
		CString kkk;
		CurrSize += g_CurrFileSize;
		kkk.Format(" %d/%d kbytes", CurrSize/1024, (dlg->totalsize)/1024 );//전체파일용량에대한 현재 받은 양 표시
		dlg->m_totalsize.AddString(kkk);
			
#if defined (TAIWAN_LOCALIZING_) || defined (CHINA_LOCALIZING_) || defined (HONGKONG_LOCALIZING_)
		if(dlg->m_FtpDown.GetFile( strPathName, tempname) )
#else 
		CString strDir;
		strDir.Format(".%s%s",filelist[i].filedir, filelist[i].filename);
		if(dlg->m_FtpDown.GetFile( strDir, tempname) )
#endif
		{	
			sprintf ( FullPathName, ".%s%s", filelist[i].filedir, filelist[i].filename );
			SetFileAttributes(FullPathName, FILE_ATTRIBUTE_NORMAL );
			DeleteFile( FullPathName );
			MoveFile( tempname, FullPathName);
			dlg->changefile( FullPathName, *filelist[i].ftp_time );
			dlg->m_ctrlProgress2.SetPos( 100 ); 
			i++;
		}	
		else
		{	
			AfxMessageBox( szFileDownErr );
			DeleteFile( "$$dir.txt" );
			DeleteFile( "$$readme.txt" );
			DeleteFile("*.tmp");
			dlg->EndDialog(0);
			return 0;
		}	
					
		dlg->m_bpStart =TRUE;
		dlg->m_ctrlProgress.SetPos( i );

	}	
	dlg->KillTimer(1);
	
	dlg->UpdateOkBtn(false);

	dlg->bIsWorkThreadFin = true;

	return (0);
}


void CDragonRajaDlg::OnTimer(UINT nIDEvent) 
{
	if( FALSE == m_bpStart )
	{
		if( g_CurrGetFileName ) 
		{
			CFile file;
			CFileStatus file_status;
			if( TRUE == file.GetStatus( g_CurrGetFileName, file_status ) )
			{
				int size = file_status.m_size;
				int pos = (int) ( (float)(size/g_CurrFileSize) *100 );
				
				m_ctrlProgress2.SetPos(pos);

				m_sCurrFileSize.Format( "%d/%d Kb", size/1000 + 1, g_CurrFileSize/1000 + 1);
				UpdateData(FALSE);
			}
		}
	}
	CDialog::OnTimer(nIDEvent);
}


void CDragonRajaDlg::changefile( CString filename, CTime time )
{
	CFile file;
	CFileStatus file_status;
	file_status.m_size = 0;
	int ret = file.GetStatus( filename, file_status );
	if( ret )
	{
		if( file_status.m_size > 0 )
		{
			file_status.m_mtime = time;
			file_status.m_ctime = time;
			file_status.m_atime = time;
			file.SetStatus( filename, file_status ); 
		}
	}
}

BOOL CDragonRajaDlg::OnEraseBkgnd(CDC* pDC) 
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
//	return CDialog::OnEraseBkgnd(pDC);
}

void CDragonRajaDlg::UpdateOkBtn(const bool bIsNeedUpdate)
{
	if(bIsNeedUpdate)
	{
		m_ctrlOK.LoadBitmaps(IDB_DN_UPDATE_NORMAL,IDB_DN_UPDATE_DOWN,IDB_DN_UPDATE_NORMAL,IDB_DN_UPDATE_NORMAL);	
	}
	else
	{
		m_ctrlOK.LoadBitmaps(IDB_DN_START_NORMAL,IDB_DN_START_DOWN,IDB_DN_START_NORMAL,IDB_DN_START_NORMAL);	
	}
	m_ctrlOK.SizeToContent();
	Invalidate(FALSE);
}

BOOL CDragonRajaDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
			{
				OnOK();
				return 0;
			}break;
		}
	}
	return CDialog::PreTranslateMessage(pMsg);
}

HBRUSH CDragonRajaDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
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

BOOL DumpException(LPEXCEPTION_POINTERS lpExcep,char* szOutMsg)
{
	if (!lpExcep)
		return FALSE;

	BOOL		result = TRUE;
	SYSTEMTIME time;

	const DWORD		dwExceptionAddress = (DWORD)lpExcep->ExceptionRecord->ExceptionAddress;
	const DWORD		dwExceptionCode = lpExcep->ExceptionRecord->ExceptionCode;
	const DWORD		dwExceptionFlags = lpExcep->ExceptionRecord->ExceptionFlags;
	const DWORD		dwNumberParameters = lpExcep->ExceptionRecord->NumberParameters;
	const DWORD		dwDr0 = lpExcep->ContextRecord->Dr0;
	const DWORD		dwDr1 = lpExcep->ContextRecord->Dr1;
	const DWORD		dwDr2 = lpExcep->ContextRecord->Dr2;
	const DWORD		dwDr3 = lpExcep->ContextRecord->Dr3;
	const DWORD		dwDr6 = lpExcep->ContextRecord->Dr6;
	const DWORD		dwDr7 = lpExcep->ContextRecord->Dr7;

	const DWORD		dwSegCs = lpExcep->ContextRecord->SegCs;

	const DWORD		dwSegGs = lpExcep->ContextRecord->SegGs;
	const DWORD		dwSegFs = lpExcep->ContextRecord->SegFs;
	const DWORD		dwSegEs = lpExcep->ContextRecord->SegEs;
	const DWORD		dwEFlags = lpExcep->ContextRecord->EFlags;

	const DWORD		dwEsi = lpExcep->ContextRecord->Esi;
	const DWORD		dwEdi = lpExcep->ContextRecord->Edi;
	const DWORD		dwEbp = lpExcep->ContextRecord->Ebp;
	const DWORD		dwEsp = lpExcep->ContextRecord->Esp;
	const DWORD		dwEip = lpExcep->ContextRecord->Eip;

	const DWORD		dwEax = lpExcep->ContextRecord->Eax;
	const DWORD		dwEbx = lpExcep->ContextRecord->Ebx;
	const DWORD		dwEcx = lpExcep->ContextRecord->Ecx;
	const DWORD		dwEdx = lpExcep->ContextRecord->Edx;
	__try
	{
		GetLocalTime(&time);
	
		g_CrashLog.Log(LOG_LV1,"%04d-%02d-%02d-%02d-%02d-%02d",
			time.wYear,time.wMonth,time.wDay,time.wMinute,time.wSecond);
		
		g_CrashLog.Log(LOG_LV1,szOutMsg);

		g_CrashLog.Log(LOG_LV1,"Crashed address %xh",dwExceptionAddress);

		g_CrashLog.Log(LOG_LV1,"Crashed Map Address %04X:%08X",
			dwSegCs,
			dwExceptionAddress);

		g_CrashLog.Log(LOG_LV1,"Exception Code %u",dwExceptionCode);
		g_CrashLog.Log(LOG_LV1,"Exception Flag %xh",dwExceptionFlags);
		g_CrashLog.Log(LOG_LV1,"NumberParameters %d",dwNumberParameters);
		g_CrashLog.Log(LOG_LV1,"Dr0 %xh",dwDr0);
		g_CrashLog.Log(LOG_LV1,"Dr1 %xh",dwDr1);
		g_CrashLog.Log(LOG_LV1,"Dr2 %xh",dwDr2);
		g_CrashLog.Log(LOG_LV1,"Dr3 %xh",dwDr3);
		g_CrashLog.Log(LOG_LV1,"Dr6 %xh",dwDr6);
		g_CrashLog.Log(LOG_LV1,"Dr7 %xh",dwDr7);
		
		g_CrashLog.Log(LOG_LV1,"SegGs %xh",dwSegGs);
		g_CrashLog.Log(LOG_LV1,"SegFs %xh",dwSegFs);
		g_CrashLog.Log(LOG_LV1,"SegEs %xh",dwSegEs);
		g_CrashLog.Log(LOG_LV1,"EFlags %xh",dwEFlags);
		
		g_CrashLog.Log(LOG_LV1,"Esi %xh",dwEsi);
		g_CrashLog.Log(LOG_LV1,"Edi %xh",dwEdi);
		g_CrashLog.Log(LOG_LV1,"Ebp %xh",dwEbp);
		g_CrashLog.Log(LOG_LV1,"Esp %xh",dwEsp);
		g_CrashLog.Log(LOG_LV1,"Eip %xh",dwEip);
		

		g_CrashLog.Log(LOG_LV1,"Eax %xh",dwEax);
		g_CrashLog.Log(LOG_LV1,"Ebx %xh",dwEbx);
		g_CrashLog.Log(LOG_LV1,"Ecx %xh",dwEcx);
		g_CrashLog.Log(LOG_LV1,"Edx %xh",dwEdx);

		g_CrashLog.Log(LOG_LV1,"Log Complete!");

	}
	__except (GetExceptionCode())
	{
		result = FALSE;
	}

	return result;
}

