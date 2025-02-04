// New Member Check List


#pragma once
#include "afxdialogex.h"


// ChkListDlg dialog

class ChkListDlg : public CDialogEx {

  DECLARE_DYNAMIC(ChkListDlg)

public:
CString nameCallSign;
BOOL    applicationProc;
BOOL    picture;
BOOL    groupsIO;
BOOL    trainingIntro;

           ChkListDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~ChkListDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_CheckList };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
