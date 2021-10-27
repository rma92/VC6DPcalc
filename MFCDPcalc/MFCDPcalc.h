// MFCDPcalc.h : main header file for the MFCDPCALC application
//

#if !defined(AFX_MFCDPCALC_H__7CA06533_DA2D_4C0E_A219_B262B40BAD7A__INCLUDED_)
#define AFX_MFCDPCALC_H__7CA06533_DA2D_4C0E_A219_B262B40BAD7A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMFCDPcalcApp:
// See MFCDPcalc.cpp for the implementation of this class
//

class CMFCDPcalcApp : public CWinApp
{
public:
	CMFCDPcalcApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDPcalcApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMFCDPcalcApp)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDPCALC_H__7CA06533_DA2D_4C0E_A219_B262B40BAD7A__INCLUDED_)
