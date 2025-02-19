// Specify the period for Former Member csv output file


#pragma once
#include "MmYyCtl.h"


// FmrPeriodDlg dialog

class FmrPeriodDlg : public CDialogEx {

  DECLARE_DYNAMIC(FmrPeriodDlg)

Cstring beginPeriod;
MmYyCtl beginPeriodCtl;
Cstring endPeriod;
MmYyCtl endPeriodCtl;

public:
Cstring begP;
Cstring endP;

               FmrPeriodDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual     ~FmrPeriodDlg();
  virtual BOOL OnInitDialog();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Period };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

public:

  afx_msg void onChangeBeginPeriod();
  afx_msg void onChangeEndperiod();
  };
