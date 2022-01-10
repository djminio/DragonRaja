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
//< soto-031014 �븸 ��û���� ��Ʈ��ȣ �߰��Ҽ� �ְ� ����.
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
	int	nPortNumber = INTERNET_DEFAULT_FTP_PORT;//����Ʈ�� 21�� ��Ʈ �̴�.
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
		m_Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);		//10�ʰ� ������ �õ�...
//		m_pFtp = m_Session.GetFtpConnection( szServerAddr, szID, szPW, INTERNET_DEFAULT_FTP_PORT,false );	//��Ƽ��� �õ�
		m_pFtp = m_Session.GetFtpConnection( szOnlyIP, szID, szPW, nPortNumber,false );	//��Ƽ��� �õ�
	}
	catch(CInternetException *lpEx)
	{
		lpEx->Delete();
		try	
		{
			m_Session.SetOption(INTERNET_OPTION_CONNECT_TIMEOUT, 10000);		//10�ʰ� ������ �õ�...
//			m_pFtp = m_Session.GetFtpConnection( szServerAddr, szID, szPW, INTERNET_DEFAULT_FTP_PORT,true );	
			m_pFtp = m_Session.GetFtpConnection( szOnlyIP, szID, szPW, nPortNumber,true );	
		}//�нú�� �õ�
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
//> soto-031014 �븸 ��û���� ��Ʈ��ȣ �߰��Ҽ� �ְ� ����.
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
	/////////////////////   FTP�� �ش� ������ �����ϴ��� �������� �ʴ��� ã�´�    /////////////
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
					FALSE,//�̹� ������ ������ ������ �̾߱�
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
	/////////////////////////////// Ŭ���̾�Ʈ�ʿ� ���� ���� ////////////////////////////////////
	CFile	DirFile;									//�ٿ�ε� �޾� ������ CFile ��ü ����...
	if (DirFile.Open(szWriteTarget, CFile::modeCreate | CFile::modeWrite, NULL)==FALSE)		//���� ���� 
	{
		buffer += " FILE CREATE FAIL";
		AfxMessageBox( buffer );
		return FALSE;
	}
	/////////////////////////////////////////////////////////////////////////////////////////////

	/////////////////////////////   ���� �ٿ�ε� �۾�  /////////////////////////////////////////
	CInternetFile*  pFtpFile = m_pFtp->OpenFile(szDNFileName);	//FTP���� �ٿ���� ������ ���� �� ������ �����͸� �޾ƿ´�.	
	
	if(!pFtpFile)
	{
		Sleep(500);
		pFtpFile = m_pFtp->OpenFile(szDNFileName);	//FTP���� �ٿ���� ������ ���� �� ������ �����͸� �޾ƿ´�.	
		if(!pFtpFile){return FALSE;}
	}
	
	const int DOWNLOAD_BUFFER_SIZE = 4096;
	//���� �ٿ�ε� ���� 
	char Buffer[DOWNLOAD_BUFFER_SIZE]= {0,};	
	unsigned int AmountRead = DOWNLOAD_BUFFER_SIZE;
	unsigned int TotalRead = 0;		

	while (AmountRead = pFtpFile->Read(Buffer,DOWNLOAD_BUFFER_SIZE))
	{
		DirFile.Write(Buffer, AmountRead);				//Ŭ���̾�Ʈ ���Ͽ� Write		
		TotalRead += AmountRead;
	}
	////////////////////////////////////////////////////////////////////////////////////////////
	
	DirFile.Close();
	pFtpFile->Close();				//FTP���� Open�� ���� �ݰ�..
	delete pFtpFile;
	return TRUE;
*/
}
