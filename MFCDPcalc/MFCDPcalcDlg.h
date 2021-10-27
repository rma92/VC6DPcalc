// MFCDPcalcDlg.h : header file
//

#if !defined(AFX_MFCDPCALCDLG_H__FD22DB9C_2C91_4820_BAB7_19BECE1E4664__INCLUDED_)
#define AFX_MFCDPCALCDLG_H__FD22DB9C_2C91_4820_BAB7_19BECE1E4664__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMFCDPcalcDlg dialog

class CMFCDPcalcDlg : public CDialog
{
// Construction
public:
	CMFCDPcalcDlg(CWnd* pParent = NULL);	// standard constructor
	void doCalcFromF(float fTempF, float fRH); //function to do the calculation
	float calcHI(float fTempF, float fRH);
	float fToC(float fTempF);
	float cToF(float fTempC);
	float calcDP(float fTempC, float fRH);
// Dialog Data
	//{{AFX_DATA(CMFCDPcalcDlg)
	enum { IDD = IDD_MFCDPCALC_DIALOG };
	CEdit	m_tempc;
	CEdit	m_tempf;
	CEdit	m_rh;
	CStatic	m_output;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFCDPcalcDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	BOOL updateOnChange;

	// Generated message map functions
	//{{AFX_MSG(CMFCDPcalcDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeTempf();
	afx_msg void OnChangeRh();
	afx_msg void OnChangeTempc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFCDPCALCDLG_H__FD22DB9C_2C91_4820_BAB7_19BECE1E4664__INCLUDED_)
