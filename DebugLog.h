// Debug.h: interface for the CDebugLog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEBUG_H__78933F14_CBDC_417D_B700_95257702E393__INCLUDED_)
#define AFX_DEBUG_H__78933F14_CBDC_417D_B700_95257702E393__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
/*--------------------------------------------------------------------
					SynCzone open source project 
						Debug-Tracer v0.1.0

					Prototype By NetSerenity.
	Modify By HwoarangSangwoo(E-Mail: hwoarang_sangwoo@hotmail.com)
----------------------------------------------------------------------*/
#define SAFE_DELETE(p)			{ if(p) { delete (p);     (p)=NULL; } }
#define SAFE_DELETE_ARRAY(p)	{ if(p) { delete[] (p);   (p)=NULL; } }
#define SAFE_RELEASE(p)			{ if(p) { (p)->Release(); (p)=NULL; } }
#define SAFE_FCLOSE(p)			{ if(p) { ::fclose(p); (p)=NULL; } }

namespace DebugLog
{
	enum eSZDTOT//SyncZone Debug Tracer Ouptput Types
	{
		OUTPUT_NOT_SET			=	0x00000000,
		OUTPUT_JUST_FILE		=	0x00000001,
		OUTPUT_JUST_TRACE		=	0x00000002,
		OUTPUT_JUST_CONSOLE		=	0x00000004,
		OUTPUT_FILE_AND_TRACE	=	OUTPUT_JUST_FILE|OUTPUT_JUST_TRACE,
		OUTPUT_FILE_AND_CONSOLE	=	OUTPUT_JUST_FILE|OUTPUT_JUST_CONSOLE,
		OUTPUT_ALL				=	OUTPUT_JUST_FILE|OUTPUT_JUST_TRACE|OUTPUT_JUST_CONSOLE,	
	};

	enum eSZDTLT//SyncZone Debug Tracer Log Types
	{
		LOG_NORMAL	= 0,
		LOG_LV1		= 1,
		LOG_LV2		= 2,
		LOG_LV3		= 3,
		LOG_LV4		= 4,
		LOG_LV5		= 5,
		LOG_LV6		= 6,
		LOG_LV7		= 7,
		LOG_LV8		= 8,
		LOG_LV9		= 9,
		LOG_LV10	= 10,
	};

	const int  MAX_ERROR_MSG_SIZE	= 1024;//로그기록 최대 길이
	const char szLogFolder[] = "./CustomerService";//SyncZone Debug Tracer Log

	class CDebugLog
	{
	public:
		CDebugLog();
		virtual ~CDebugLog();
		
	public:
		bool Init(const eSZDTOT OutputMode, const char* strIdentifyName);//모드 셋팅 기록 될 파일의 고유 이름입니다.
		void Log(const eSZDTLT LogLv, const char *szLogMsg, ...);//기록부

	private:
		void Start(){::InitializeCriticalSection(&m_ThreadCS);}//시작시 반드시 호출 해야함 Example 참조
		void End(){::DeleteCriticalSection(&m_ThreadCS);}//종료시 반드시 호출 해야함 Example 참조
		void Clear();//변수 초기화
		void SetTime();//시간 관리부
		void SetWriteFile();//기록될 파일 설정// 반드시 호출 전에 SetTime을 호출 하세요 SetTime 뒤에 오게 하세요
		
		void OutFile(const char *szLogMsg);
		void OutTrace(const char *szLogMsg);	
		void OutConsole(const char *szLogMsg);
		
		bool OpenConsole();
		void CloseConsole();

	private:
		__int32	m_iMode;//모드저장소.
		char 	m_szIdentify[MAX_PATH];
		FILE*	m_fp;//파일 핸들
		
		HANDLE	m_hConsole;//콘솔의 핸들.
		CRITICAL_SECTION	m_ThreadCS;//스레드의 핸들.

		__int32 m_iYear,m_iMon,m_iDay;
		__int32 m_iHour,m_iMin,m_iSec;

	private:
		CDebugLog operator=(const CDebugLog &old);//대입연산자 사용 불가.
		CDebugLog(const CDebugLog &old);//복사생성자 사용 불가.
	};

	/*-------------------------------------------------------------------
	Example>
	void Garbage()
	{
		CDebugLog Dbg;
		Dbg.Init(OUTPUT_JUST_FILE,"Func1");
		
		Dbg.Log(LOG_LV1,"여기서 무었을 %d를 호출 했지", 100);
		.
		.
		.
		Dbg.Log(LOG_LV1,"들어오면 안되는곳");
		.
		.
		.
	}
	//------------------------------------------------------------------*/
}
using namespace DebugLog;

extern CDebugLog g_CrashLog;
extern CDebugLog g_DBGLog;
#endif // !defined(AFX_DEBUG_H__78933F14_CBDC_417D_B700_95257702E393__INCLUDED_)
