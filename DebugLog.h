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

	const int  MAX_ERROR_MSG_SIZE	= 1024;//�αױ�� �ִ� ����
	const char szLogFolder[] = "./CustomerService";//SyncZone Debug Tracer Log

	class CDebugLog
	{
	public:
		CDebugLog();
		virtual ~CDebugLog();
		
	public:
		bool Init(const eSZDTOT OutputMode, const char* strIdentifyName);//��� ���� ��� �� ������ ���� �̸��Դϴ�.
		void Log(const eSZDTLT LogLv, const char *szLogMsg, ...);//��Ϻ�

	private:
		void Start(){::InitializeCriticalSection(&m_ThreadCS);}//���۽� �ݵ�� ȣ�� �ؾ��� Example ����
		void End(){::DeleteCriticalSection(&m_ThreadCS);}//����� �ݵ�� ȣ�� �ؾ��� Example ����
		void Clear();//���� �ʱ�ȭ
		void SetTime();//�ð� ������
		void SetWriteFile();//��ϵ� ���� ����// �ݵ�� ȣ�� ���� SetTime�� ȣ�� �ϼ��� SetTime �ڿ� ���� �ϼ���
		
		void OutFile(const char *szLogMsg);
		void OutTrace(const char *szLogMsg);	
		void OutConsole(const char *szLogMsg);
		
		bool OpenConsole();
		void CloseConsole();

	private:
		__int32	m_iMode;//��������.
		char 	m_szIdentify[MAX_PATH];
		FILE*	m_fp;//���� �ڵ�
		
		HANDLE	m_hConsole;//�ܼ��� �ڵ�.
		CRITICAL_SECTION	m_ThreadCS;//�������� �ڵ�.

		__int32 m_iYear,m_iMon,m_iDay;
		__int32 m_iHour,m_iMin,m_iSec;

	private:
		CDebugLog operator=(const CDebugLog &old);//���Կ����� ��� �Ұ�.
		CDebugLog(const CDebugLog &old);//��������� ��� �Ұ�.
	};

	/*-------------------------------------------------------------------
	Example>
	void Garbage()
	{
		CDebugLog Dbg;
		Dbg.Init(OUTPUT_JUST_FILE,"Func1");
		
		Dbg.Log(LOG_LV1,"���⼭ ������ %d�� ȣ�� ����", 100);
		.
		.
		.
		Dbg.Log(LOG_LV1,"������ �ȵǴ°�");
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
