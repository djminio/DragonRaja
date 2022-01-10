// Debug.cpp: implementation of the CDebugLog class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "Debuglog.h"
#include <assert.h>
#include <direct.h>
#include <Time.h>

CDebugLog g_DBGLog;
CDebugLog g_CrashLog;
#ifdef _DEBUG
	#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
	#define new DEBUG_NEW
#endif

CDebugLog::CDebugLog()
{
	m_fp = NULL;
	m_hConsole	= INVALID_HANDLE_VALUE;
	Start();
	Clear();
}

CDebugLog::~CDebugLog()
{
	Clear();
	CloseConsole();
	End();
}

bool CDebugLog::Init(const eSZDTOT OutputMode, const char* szIdentifyName)
{
	switch(OutputMode)
	{
	case OUTPUT_NOT_SET:
		{
			assert(0);
			break;
		}//OUTPUT_NOT_SET:
	default:
		{	
			m_iMode = OutputMode;
			break;
		}
	}//switch(OutputMode)

	if(m_iMode & OUTPUT_JUST_CONSOLE)
	{
		OpenConsole();
	}

	::strcpy(m_szIdentify,szIdentifyName);
	return true;
}

void CDebugLog::Clear()
{
	m_iMode		= OUTPUT_NOT_SET;
	::strcpy(m_szIdentify,"");
	SAFE_FCLOSE(m_fp);//파일 클리어
}

void CDebugLog::SetTime()//시간 관리부
{
	time_t nowTime;//시간 받기
	::time( &nowTime );
	struct tm *now = ::localtime(&nowTime);

	m_iYear = now->tm_year+1900;
	m_iMon  = now->tm_mon+1;
	m_iDay  = now->tm_mday;
	m_iHour = now->tm_hour;
	m_iMin  = now->tm_min;
	m_iSec  = now->tm_sec;
}

void CDebugLog::SetWriteFile()//파일 관리부
{
	static __int32 siLogYear=0, siLogMon=0, siLogDay=0;
	if( siLogDay != m_iDay 
	||	siLogMon != m_iMon 
	||	siLogYear != m_iYear 
	||	!m_fp)
	{
		siLogDay = m_iDay,	siLogMon = m_iMon,	siLogYear = m_iYear;
		SAFE_FCLOSE(m_fp);//파일 닫고

		::mkdir(szLogFolder);
		char szFileName[MAX_PATH+500] = {0,};
		::sprintf(szFileName,"%s/%d-%d-%d %s.log",szLogFolder, siLogYear, siLogMon, siLogDay, m_szIdentify);
		m_fp = ::fopen(szFileName,"at");//파일 오픈
		if(!m_fp)
		{
			assert(0);//열리지 않았으면 assert
		}
	}
}

void CDebugLog::Log(const eSZDTLT LogLv, const char *szLogMsg, ...)
{
	::EnterCriticalSection(&m_ThreadCS);

	SetTime();
	SetWriteFile();

	char szTemp[MAX_ERROR_MSG_SIZE] = {0,};
	char szResultMsg[MAX_ERROR_MSG_SIZE+20];

	va_list vargs;
	va_start(vargs,szLogMsg);
	::vsprintf(szTemp, szLogMsg, vargs);
	va_end(vargs);

	::sprintf(szResultMsg, "<LogLv%d(%d:%d:%d)> %s",LogLv, m_iHour, m_iMin, m_iSec, szTemp);//시간이 기록 됩니다
	
	if(m_iMode & OUTPUT_JUST_FILE)
	{
		OutFile(szResultMsg);
	}
	if(m_iMode & OUTPUT_JUST_TRACE)
	{
		OutTrace(szResultMsg);
	}
	if(m_iMode & OUTPUT_JUST_CONSOLE)
	{
		OutConsole(szResultMsg);
	}
	::LeaveCriticalSection(&m_ThreadCS);
}

void CDebugLog::OutFile(const char* szLogMsg)
{
	if(m_fp)
	{
		::fprintf(m_fp,"%s\n",szLogMsg);
		::fflush(m_fp);
	}
}

void CDebugLog::OutTrace(const char* szLogMsg)
{
	::OutputDebugString(szLogMsg);
}

void CDebugLog::OutConsole(const char* szLogMsg)
{
	DWORD dwBytes = 0;
	::WriteFile(m_hConsole, szLogMsg, ::strlen(szLogMsg), &dwBytes, NULL);
	::WriteFile(m_hConsole, "\n", ::strlen("\n"), &dwBytes, NULL);
}

bool CDebugLog::OpenConsole()
{
	if(m_iMode & OUTPUT_JUST_CONSOLE)
	{
		if(!::AllocConsole()){return false;}
		m_hConsole = ::GetStdHandle(STD_OUTPUT_HANDLE);
		if(INVALID_HANDLE_VALUE == m_hConsole) 
		{
			::FreeConsole();
			return false;
		}
		return true;
	}
	return false;
}

void CDebugLog::CloseConsole()
{
	if(m_iMode & OUTPUT_JUST_CONSOLE)
	{
		::FreeConsole();
		::CloseHandle(m_hConsole);
		m_hConsole	= INVALID_HANDLE_VALUE;
	}
}