// FTPMgr.cpp: implementation of the CFTPMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DragonRaja.h"
#include "FTPMgr.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFTPMgr::CFTPMgr()
{
	m_pFtp = NULL;
}

CFTPMgr::~CFTPMgr()
{
	Close();
}

bool CFTPMgr::Connect(const char* szServerAddr, const char* szID,const char* szPW)
{
//< soto-031014 대만 요청으로 포트번호 추가할수 있게 수정.
	char szOnlyIP[MAX_PATH] = {0,};
	char szPort[MAX_PATH] = {0,};
	int	nLen = strlen(szServerAddr);
	int i = 0;
	if(nLen)
	{		
		for(;i < nLen;++i)
		{
			if(szServerAddr[i] == ':')
			{
				++i;
				break;
			}
			szOnlyIP[i] = szServerAddr[i];
		}		
	}
	else
	{
		return false;
	}
	
	int	nPortLen = 0;
	int	nPortNumber = INTERNET_DEFAULT_FTP_PORT;//디폴트는 21번 포트 이다.
	if(i < nLen - 1)
	{
		nPortLen = strlen(&(szServerAddr[i]));
		if(0 < nPortLen)
		{
			nPortNumber = atoi(&(szServerAddr[i]));
		}
	}

	try
	{ 
		m_Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);		//10초간 접속을 시도...
//		m_pFtp = m_Session.GetFtpConnection( szServerAddr, szID, szPW, INTERNET_DEFAULT_FTP_PORT,false );	//액티브로 시도
		m_pFtp = m_Session.GetFtpConnection( szOnlyIP, szID, szPW, nPortNumber,false );	//액티브로 시도
	}
	catch(CInternetException *lpEx)
	{
		lpEx->Delete();
		try	
		{
			m_Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);		//10초간 접속을 시도...
//			m_pFtp = m_Session.GetFtpConnection( szServerAddr, szID, szPW, INTERNET_DEFAULT_FTP_PORT,true );	
			m_pFtp = m_Session.GetFtpConnection( szOnlyIP, szID, szPW, nPortNumber,true );	
		}//패시브로 시도
		catch(CInternetException *lpEx)
		{
			lpEx->Delete();
		}
	}
	
	if(!m_pFtp)
	{
		::AfxMessageBox(szConnectionErr);
		::exit(0);
		return false;
	}
	return true;
//> soto-031014 대만 요청으로 포트번호 추가할수 있게 수정.
}

void CFTPMgr::Close()
{
	if(m_pFtp)
	{
		m_pFtp->Close();
		delete m_pFtp;
		m_pFtp = NULL;
		m_Session.Close();
	}
}

bool CFTPMgr::GetFile(const char *szDNFileName,const char *szWriteTarget,const bool bIsASCII, const bool bIsFailIfExit)
{
	/////////////////////   FTP에 해당 파일이 존재하는지 존재하지 않는지 찾는다    /////////////
	CFtpFileFind FtpFinder(m_pFtp,INTERNET_FLAG_DONT_CACHE);
	const BOOL bIsExist = FtpFinder.FindFile(szDNFileName,INTERNET_FLAG_DONT_CACHE);
	
	FtpFinder.Close();
	DWORD dwRet = ::GetLastError();

	if(bIsExist== FALSE)
	{
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////
//	FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_BINARY, 1;
	m_pFtp->GetFile(szDNFileName,szWriteTarget,
					FALSE,//이미 파일이 있으면 지우라는 이야기
					FILE_ATTRIBUTE_NORMAL,
					(bIsASCII)?FTP_TRANSFER_TYPE_ASCII:FTP_TRANSFER_TYPE_BINARY );
	
	if(bIsFailIfExit)
	{
		AfxMessageBox( szFileDownErr );
		Close();
		::PostQuitMessage(0);
		return false;
	}
	return true;
/*
	CString buffer(szDNFileName);	
	/////////////////////////////// 클라이언트쪽에 파일 생성 ////////////////////////////////////
	CFile	DirFile;									//다운로드 받아 저장할 CFile 객체 선언...
	if (DirFile.Open(szWriteTarget, CFile::modeCreate | CFile::modeWrite, NULL)==FALSE)		//파일 생성 
	{
		buffer += " FILE CREATE FAIL";
		AfxMessageBox( buffer );
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////   파일 다운로드 작업  /////////////////////////////////////////
	CInternetFile*  pFtpFile = m_pFtp->OpenFile(szDNFileName);	//FTP상의 다운받을 파일을 연후 그 파일의 포인터를 받아온다.	
	
	if(!pFtpFile)
	{
		Sleep(500);
		pFtpFile = m_pFtp->OpenFile(szDNFileName);	//FTP상의 다운받을 파일을 연후 그 파일의 포인터를 받아온다.	
		if(!pFtpFile){return FALSE;}
	}
	
	const int DOWNLOAD_BUFFER_SIZE = 4096;
	//파일 다운로드 시작 
	char Buffer[DOWNLOAD_BUFFER_SIZE]= {0,};	
	unsigned int AmountRead = DOWNLOAD_BUFFER_SIZE;
	unsigned int TotalRead = 0;		

	while (AmountRead = pFtpFile->Read(Buffer,DOWNLOAD_BUFFER_SIZE))
	{
		DirFile.Write(Buffer, AmountRead);				//클라이언트 파일에 Write		
		TotalRead += AmountRead;
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	
	DirFile.Close();
	pFtpFile->Close();				//FTP상의 Open된 파일 닫고..
	delete pFtpFile;
	return TRUE;
*/
}
