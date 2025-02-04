// find City State based on zip code


#pragma once
#include "ZipList.h"

class CtyRcd;
class ZipDtm;


// CityState dialog

class CityStateDlg : public CDialogEx {

  DECLARE_DYNAMIC(CityStateDlg)

public:
CEdit   cityCtl;
CEdit   stateCtl;
CEdit   zipCtl;

ZipIter iter;
ZipDtm* zipDtm;
CtyRcd* ctyRcd;
String  tgt;

               CityStateDlg(CWnd* pParent = nullptr);   // standard constructor
  virtual     ~CityStateDlg();

  virtual BOOL OnInitDialog();
  virtual void OnOK();

// Dialog Data
#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_CityState };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

  DECLARE_MESSAGE_MAP()

private:

  void clrCtls();
  void setCtls(TCchar* cty, TCchar* st, TCchar* zp);

public:

  afx_msg void onFocusCity();
  afx_msg void onFocusState();
  afx_msg void onFocusZip();
  afx_msg void onFindZip();
  afx_msg void onNextZip();
};
