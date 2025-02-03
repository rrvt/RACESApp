// Address.cpp : implementation file
//

#include "pch.h"
#include "AddressDlg.h"
#include "AddrList.h"
#include "AdrTbl.h"
#include "Resource.h"
#include "RNUtility.h"


static TCchar* StreetAddrLbl = _T("Street Address");
static TCchar* UnitNoLbl     = _T("Unit No");


// Address dialog

IMPLEMENT_DYNAMIC(AddressDlg, CDialogEx)


BEGIN_MESSAGE_MAP(AddressDlg, CDialogEx)
  ON_EN_SETFOCUS(IDC_StreetAddr, &onFocusStreetaddr)
  ON_EN_SETFOCUS(IDC_UnitNo,     &onFocusUnitno)
  ON_BN_CLICKED( IDC_FindAddr,   &onFindaddr)
  ON_BN_CLICKED( IDC_FindNext,   &onFindNext)
END_MESSAGE_MAP()


AddressDlg::AddressDlg(CWnd* pParent) : CDialogEx(IDD_Address, pParent),
                                                           iter(addrList), adrDtm(0), adrRcd(0) { }

AddressDlg::~AddressDlg() { }


BOOL AddressDlg::OnInitDialog() {

  CDialogEx::OnInitDialog();

  setCtls(StreetAddrLbl, UnitNoLbl);   return TRUE;
  }


void AddressDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_StreetAddr, addressCtl);
  DDX_Control(pDX, IDC_UnitNo,     unitNoCtl);
  }


// AddressDlg message handlers


void AddressDlg::onFocusStreetaddr() {clrLbl(addressCtl, StreetAddrLbl);}


void AddressDlg::onFocusUnitno() {clrLbl(unitNoCtl, UnitNoLbl);}


void AddressDlg::onFindaddr() {
  tgt = get(addressCtl);

  for (adrDtm = iter(); adrDtm; adrDtm = iter++) if (adrDtm->addr.find(tgt) >= 0)
                   {adrRcd = (*adrDtm)();   setCtls(adrRcd->address1, adrRcd->address2);   return;}
  clrCtls();   adrRcd = 0;
  }


void AddressDlg::onFindNext() {

  for (adrDtm = iter++; adrDtm; adrDtm = iter++) if (adrDtm->addr.find(tgt) >= 0)
                   {adrRcd = (*adrDtm)();   setCtls(adrRcd->address1, adrRcd->address2);   return;}
  clrCtls();   adrRcd = 0;
  }


void AddressDlg::OnOK() {CDialogEx::OnOK();}



void AddressDlg::clrCtls() {clear(addressCtl);    clear(unitNoCtl);}


void AddressDlg::setCtls(TCchar* addr, TCchar* unit)
                              {strtAddr = set(addressCtl, addr);   unitNo = set(unitNoCtl, unit);}

