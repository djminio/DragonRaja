// DragonRaja.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "DragonRaja.h"
#include "DragonRajaDlg.h"
#include "direct.h"
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDragonRajaApp

BEGIN_MESSAGE_MAP(CDragonRajaApp, CWinApp)
	//{{AFX_MSG_MAP(CDragonRajaApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDragonRajaApp construction

CDragonRajaApp::CDragonRajaApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CDragonRajaApp object

CDragonRajaApp theApp;

extern void RegistProgram();	// 0612 YGI
extern void DeleteComma( char *text );

HRESULT CreateShortCut(LPCSTR pszShortcutFile, LPSTR pszLink, LPSTR pszDesc);

/////////////////////////////////////////////////////////////////////////////
// CDragonRajaApp initialization
BOOL CDragonRajaApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	///////////////////////////////////////////		Working directory changed by this routine
	char temp[MAX_PATH] = {0,};							// 0612 YGI
	::strcpy( temp, __argv[0] );

	int len = ::strlen( temp );

	for( ; len > 0; len-- )
	{
		if( *(temp+len) == '/' || *(temp+len) == '\\' ) 
		{	break; }
	}

	*(temp+len) = NULL;
	_chdir( temp );

	RegistProgram();			// 레지스트리에 등록한다.

	CDragonRajaDlg dlg;

	int nResponse = dlg.s_dlg.DoModal();

	if (nResponse == IDCANCEL)
	{
		if( dlg.s_dlg.m_lpServerSet ) delete dlg.s_dlg.m_lpServerSet;
		return false;
	}

	m_pMainWnd = &dlg;
	nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	if( dlg.s_dlg.m_lpServerSet ) delete dlg.s_dlg.m_lpServerSet;

	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}


//#include <  shlobj.h  >
HRESULT CreateShortCut(LPCSTR pszShortcutFile, LPSTR pszLink, LPSTR pszDesc)
{
  HRESULT hres;
  IShellLink *psl;
  

	CoInitialize(NULL);

  // Create an IShellLink object and get a pointer to the IShellLink
  // interface (returned from CoCreateInstance).
  hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void **)&psl);
  if (SUCCEEDED(hres))
  {
    IPersistFile *ppf;
    
    // Query IShellLink for the IPersistFile interface for
    // saving the shortcut in persistent storage.
    hres = psl->QueryInterface(IID_IPersistFile, (void **)&ppf);
    if (SUCCEEDED(hres))
    {   
      WORD wsz[MAX_PATH];   // buffer for Unicode string
      
      // Set the path to the shortcut target.
      hres = psl->SetPath(pszShortcutFile);
      // Set the description of the shortcut.
      hres = psl->SetDescription(pszDesc);
      
      // Ensure that the string consists of ANSI characters.
      MultiByteToWideChar(CP_ACP, 0, pszLink, -1, (LPWSTR)wsz, MAX_PATH);
      
      // Save the shortcut via the IPersistFile::Save member function.
      hres = ppf->Save((LPCOLESTR)wsz, TRUE);
      
      // Release the pointer to IPersistFile.
      ppf->Release();
    }
    // Release the pointer to IShellLink.
    psl->Release();

	
  }
  CoUninitialize();
  return hres;
}








//////////////////// YGI 0612 ////////////////////////////////////////////////////////////////
#define REGIST_KEY  "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\DragonRaja.exe" 
void RegistProgram( )
{
	char full_directory[ FILENAME_MAX];		// 경로
	char default_value[ FILENAME_MAX];		// 경로에 화일명까지

	GetCurrentDirectory( FILENAME_MAX, full_directory );
	strcpy( default_value, full_directory );
	strcat( default_value, "\\Dragonraja.exe" );

	HKEY hKeyResult;
	DWORD dwDisposition;
	LONG lResult = RegCreateKeyEx(	HKEY_LOCAL_MACHINE, 
									REGIST_KEY, 
									NULL,	
									"", 
									REG_OPTION_NON_VOLATILE, 
									KEY_ALL_ACCESS, 
									NULL, 
									&hKeyResult, 
									&dwDisposition );
	if( lResult != ERROR_SUCCESS )
	{
		RegCloseKey(hKeyResult );
		return;
	}
	lResult = RegSetValueEx( hKeyResult, "", 0, REG_SZ, (unsigned char *)default_value, strlen( default_value ) );
	
	if( lResult != ERROR_SUCCESS )
	{
		RegCloseKey(hKeyResult );
		return;
	}

	lResult = RegSetValueEx( hKeyResult, "Path", 0, REG_SZ, (unsigned char *)full_directory, strlen( full_directory ) );
	RegCloseKey(hKeyResult );

	return;
}

void SaveGetFileName( FILELIST *filelist, int nMaxCount )
{
	FILE *fp;
	fp = fopen( "받아야하는 파일 목록.txt", "wt" );
	if( !fp ) return;

	for( int i=1; i<=nMaxCount; i++ )
	{
		fprintf( fp, "%s	%s	%d	\n", filelist[i].filedir, filelist[i].filename,filelist[i].filesize );
	}
	fclose( fp );
}