#pragma once
#include "afxdialogex.h"


// SearchDlg dialog

class SearchDlg : public CDialogEx {

  DECLARE_DYNAMIC(SearchDlg)

public:

Cstring target;
BOOL    wholeWord;
BOOL    curFldOnly;
BOOL    caseSensitive;
int     attributes;

               SearchDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual     ~SearchDlg();
  virtual BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Search };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
public:
    virtual void OnOK();
};
