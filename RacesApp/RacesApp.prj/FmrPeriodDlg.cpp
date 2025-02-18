// FmrPeriodDlg.cpp : implementation file
//

#include "pch.h"
#include "FmrPeriodDlg.h"
#include "Resource.h"
#include "Utility.h"


// FmrPeriodDlg dialog

IMPLEMENT_DYNAMIC(FmrPeriodDlg, CDialogEx)


FmrPeriodDlg::FmrPeriodDlg(CWnd* pParent) : CDialogEx(IDD_Period, pParent),
                                            beginPeriod(2015, 1, 1, 0, 0, 0),
                                            endPeriod(COleDateTime::GetCurrentTime()) { }

FmrPeriodDlg::~FmrPeriodDlg() { }


BOOL FmrPeriodDlg::OnInitDialog() {
COleDateTimeSpan span(100, 0, 0, 0);

  endPeriod += span;

  CDialogEx::OnInitDialog();

  return TRUE;
  }


void FmrPeriodDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_DateTimeCtrl(pDX, IDC_BeginPeriod, beginPeriod);
  DDX_DateTimeCtrl(pDX, IDC_EndPeriod,   endPeriod);
  }


BEGIN_MESSAGE_MAP(FmrPeriodDlg, CDialogEx)
END_MESSAGE_MAP()


void FmrPeriodDlg::OnOK() {

  CDialogEx::OnOK();

  begP = beginPeriod.Format(_T("%y%m"));
  endP =   endPeriod.Format(_T("%y%m"));
  }
