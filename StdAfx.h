// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__BAAD36A9_EB19_11D3_945D_004F4C04C094__INCLUDED_)
#define AFX_STDAFX_H__BAAD36A9_EB19_11D3_945D_004F4C04C094__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxinet.h>
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include "FTPMgr.h"

//#define KOREAN_LOCALIZING_
//#define JAPAN_LOCALIZING_
//#define CHINA_LOCALIZING_
#define TAIWAN_LOCALIZING_
//#define USA_LOCALIZING_
//#define HONGKONG_LOCALIZING_
//#define THAI_LOCALIZING_

extern const char szConnectionErr[];
extern const char szIniReadErr[];
extern const char szTxtReadErr[];
extern const char szTxtAuthConnectErr[];
extern const char szFileDownErr[];
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__BAAD36A9_EB19_11D3_945D_004F4C04C094__INCLUDED_)
