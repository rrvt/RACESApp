// Save Record Dialog -- Use when readOnly is true


#pragma once


// SaveRcdDlg dialog

class SaveRcdDlg : public CDialogEx {

  DECLARE_DYNAMIC(SaveRcdDlg)

public:
BOOL editable;

           SaveRcdDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual ~SaveRcdDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_SaveChgs };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()
  };
