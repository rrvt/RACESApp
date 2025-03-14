// FmrPeriodDlg.cpp : implementation file
//

#include "pch.h"
#include "FmrPeriodDlg.h"
#include "Date.h"
#include "Resource.h"
#include "Utility.h"


// FmrPeriodDlg dialog

IMPLEMENT_DYNAMIC(FmrPeriodDlg, CDialogEx)


FmrPeriodDlg::FmrPeriodDlg(CWnd* pParent) :
                                       CDialogEx(IDD_Period, pParent), beginPeriod(_T("01/70")) { }
FmrPeriodDlg::~FmrPeriodDlg() { }


BOOL FmrPeriodDlg::OnInitDialog() {
Date dt;   dt.getToday();
CTimeSpan  oneMonth(30, 0, 0, 0);   dt += oneMonth;

  endPeriod = dt.format(_T("%m/%y"));   CDialogEx::OnInitDialog();   return TRUE;
  }


void FmrPeriodDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(   pDX, IDC_BeginPeriod, beginPeriod);
  DDX_Control(pDX, IDC_BeginPeriod, beginPeriodCtl);
  DDX_Text(   pDX, IDC_EndPeriod,   endPeriod);
  DDX_Control(pDX, IDC_EndPeriod,   endPeriodCtl);
  }


BEGIN_MESSAGE_MAP(FmrPeriodDlg, CDialogEx)
  ON_EN_CHANGE(IDC_BeginPeriod, &onChangeBeginPeriod)
  ON_EN_CHANGE(IDC_EndPeriod,   &onChangeEndperiod)
END_MESSAGE_MAP()


void FmrPeriodDlg::onChangeBeginPeriod()   {beginPeriodCtl.verify();}


void FmrPeriodDlg::onChangeEndperiod() {endPeriodCtl.verify();}


void FmrPeriodDlg::OnOK() {

  CDialogEx::OnOK();

  begP = beginPeriodCtl.format(beginPeriod);
  endP = endPeriodCtl.format(endPeriod);
  }
