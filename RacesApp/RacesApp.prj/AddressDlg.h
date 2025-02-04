// Find Address Record based on Address


#pragma once
#include "AddrList.h"

class AdrDtm;
class AdrRcd;


class AddressDlg : public CDialogEx {

  DECLARE_DYNAMIC(AddressDlg)

public:

CEdit    addressCtl;
CEdit    unitNoCtl;

AddrIter iter;
AdrDtm*  adrDtm;
AdrRcd*  adrRcd;
String   tgt;
String   strtAddr;
String   unitNo;

               AddressDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual     ~AddressDlg();

  virtual BOOL OnInitDialog();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_Address };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void clrCtls();
  void setCtls(TCchar* strtAddr, TCchar* unitNo);

public:

  afx_msg void onFindaddr();
  afx_msg void onFindNext();
  afx_msg void onFocusStreetaddr();
  afx_msg void onFocusUnitno();
  };
