// FTPMgr.h: interface for the CFTPMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FTPMGR_H__C853DC5B_F0F4_44C3_825D_749D5DB23064__INCLUDED_)
#define AFX_FTPMGR_H__C853DC5B_F0F4_44C3_825D_749D5DB23064__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <wininet.h>
#pragma comment(lib, "wininet.lib")

class CFTPMgr
{
public:
	CFTPMgr();
	virtual ~CFTPMgr();

	bool Connect(const char* szServerAddr, const char* szID,const char* szPW);
	void Close();
	bool GetFile(const char *szDNFileName,const char *szWriteTarget,const bool bIsASCII=false, const bool bIsFailIfExit = false);

private:
	CFtpConnection *m_pFtp;
	CInternetSession m_Session;
};

#endif // !defined(AFX_FTPMGR_H__C853DC5B_F0F4_44C3_825D_749D5DB23064__INCLUDED_)
