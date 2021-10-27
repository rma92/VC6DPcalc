// MFCDPcalcDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCDPcalc.h"
#include "MFCDPcalcDlg.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCDPcalcDlg dialog

CMFCDPcalcDlg::CMFCDPcalcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFCDPcalcDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMFCDPcalcDlg)
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCDPcalcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMFCDPcalcDlg)
	DDX_Control(pDX, IDC_TEMPC, m_tempc);
	DDX_Control(pDX, IDC_TEMPF, m_tempf);
	DDX_Control(pDX, IDC_RH, m_rh);
	DDX_Control(pDX, IDC_OUT, m_output);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMFCDPcalcDlg, CDialog)
	//{{AFX_MSG_MAP(CMFCDPcalcDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_TEMPF, OnChangeTempf)
	ON_EN_CHANGE(IDC_RH, OnChangeRh)
	ON_EN_CHANGE(IDC_TEMPC, OnChangeTempc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCDPcalcDlg message handlers

BOOL CMFCDPcalcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	updateOnChange = true;
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	m_tempf.SetWindowText("68");
	m_tempc.SetWindowText("20.00");
	m_rh.SetWindowText("50");
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCDPcalcDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

HCURSOR CMFCDPcalcDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMFCDPcalcDlg::doCalcFromF(float fTempF, float fRH)
{
	LPTSTR szOutStr = new char[255];
	float fHI, fDPc;
	fHI = calcHI( fTempF, fRH );
	fDPc = calcDP( fToC( fTempF ), fRH );
	sprintf(szOutStr, "Heat Index: %.2f F %.2f C \r\nDew Point: %.2f degF %.2f degC", fHI, fToC( fHI), cToF( fDPc ), fDPc );
	m_output.SetWindowText(szOutStr);
}

float CMFCDPcalcDlg::calcHI(float fTempF, float fRH)
{
	float fHI = 0;
	if( fTempF < 80 )
	{
		fHI = 0.5 * (fTempF + 61.0 + (( fTempF-68.0)*1.2) + (fRH*0.094));
	}
	else
	{
		fHI = -42.379 + 2.04901523 * fTempF + 10.14333127 * fRH - .22475541 * fTempF * fRH - .00683783* fTempF * fTempF - .05481717 * fRH * fRH + .00122874 * fTempF * fTempF * fRH + .00085282* fTempF * fRH * fRH - .00000199 * fTempF * fTempF * fRH * fRH;
		if( fRH < 13 && fTempF > 80 && fTempF < 112 )
		{
			OutputDebugString("80-112");
			fHI -= ( (13.0f - fRH) / 4.0f ) * sqrt( (17.0 - abs(fTempF - 95.0f) ) / 17.0f );
		}
		else if( fRH > 85 && fTempF > 80 && fTempF < 87 )
		{
			OutputDebugString("80-87 and humid");
			fHI += (( fRH - 85.0f) / 10.0f) * ( (87.0f - fTempF) / 5.0f );
		}
	}
	return fHI;
}

float CMFCDPcalcDlg::cToF(float fTempC)
{
  return ((fTempC * 9.0 / 5.0 ) + 32);
}
float CMFCDPcalcDlg::fToC(float fTempF)
{
  return (( fTempF - 32.0 ) * 5.0 / 9.0);
}
float CMFCDPcalcDlg::calcDP(float fTempC, float fRH)
{
  return 243.04 * ( log( fRH /100 ) + ((17.625 * fTempC )/(243.04+ fTempC )))/(17.625 - log( fRH / 100.0 )-((17.625 * fTempC)/(243.04 + fTempC )));
}
void CMFCDPcalcDlg::OnChangeTempf() 
{
	if( updateOnChange && m_tempf.GetFocus() == &m_tempf )
	{
		
		LPTSTR szRhStr = new char[15];
		LPTSTR szTempFStr = new char[15];
		m_rh.GetWindowText(szRhStr, 15);
		m_tempf.GetWindowText(szTempFStr, 15);
		float fTempF, fRH;
		fTempF = atof(szTempFStr);
		fRH = atof(szRhStr);

		LPTSTR szOutDegC = new char[255];
		sprintf(szOutDegC, "%.2f", fToC(fTempF) );
		m_tempc.SetWindowText(szOutDegC);
		
		doCalcFromF(fTempF, fRH);
	}
}

void CMFCDPcalcDlg::OnChangeRh() 
{
	if( updateOnChange && m_rh.GetFocus() == &m_rh)
	{
		LPTSTR szRhStr = new char[15];
		LPTSTR szTempFStr = new char[15];
		m_rh.GetWindowText(szRhStr, 15);
		m_tempf.GetWindowText(szTempFStr, 15);
		float fTempF, fRH;
		fTempF = atof(szTempFStr);
		fRH = atof(szRhStr);

		doCalcFromF(fTempF, fRH);
	}
}

void CMFCDPcalcDlg::OnChangeTempc() 
{	
	if( updateOnChange && m_tempc.GetFocus() == &m_tempc )
	{
		LPTSTR szRhStr = new char[15];
		LPTSTR szTempCStr = new char[15];
		m_rh.GetWindowText(szRhStr, 15);
		m_tempc.GetWindowText(szTempCStr, 15);
		float fTempC, fRH;
		fTempC = atof(szTempCStr);
		fRH = atof(szRhStr);

		LPTSTR szOutDegF = new char[255];
		sprintf(szOutDegF, "%.2f", cToF(fTempC) );
		m_tempf.SetWindowText(szOutDegF);

		doCalcFromF(cToF( fTempC) , fRH);
	}
}
