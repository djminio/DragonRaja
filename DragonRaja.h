// DragonRaja.h : main header file for the DRAGONRAJA application
//

#if !defined(AFX_DRAGONRAJA_H__BAAD36A5_EB19_11D3_945D_004F4C04C094__INCLUDED_)
#define AFX_DRAGONRAJA_H__BAAD36A5_EB19_11D3_945D_004F4C04C094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CDragonRajaApp:
// See DragonRaja.cpp for the implementation of this class
//

class CDragonRajaApp : public CWinApp
{
public:
	CDragonRajaApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDragonRajaApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CDragonRajaApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DRAGONRAJA_H__BAAD36A5_EB19_11D3_945D_004F4C04C094__INCLUDED_)
