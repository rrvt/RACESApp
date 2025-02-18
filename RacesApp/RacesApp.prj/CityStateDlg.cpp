// find City State based on zip code


#include "pch.h"
#include "CityStateDlg.h"
#include "CtyTbl.h"
#include "Resource.h"
#include "Utility.h"
#include "ZipList.h"


static TCchar* CityLbl  = _T("City");
static TCchar* StateLbl = _T("State");
static TCchar* ZipLbl   = _T("Zip");


// CityState dialog

IMPLEMENT_DYNAMIC(CityStateDlg, CDialogEx)


BEGIN_MESSAGE_MAP(CityStateDlg, CDialogEx)
  ON_EN_SETFOCUS(IDC_City,    &onFocusCity)
  ON_EN_SETFOCUS(IDC_State,   &onFocusState)
  ON_EN_SETFOCUS(IDC_Zip,     &onFocusZip)
  ON_BN_CLICKED( IDC_FindZip, &onFindZip)
  ON_BN_CLICKED( IDC_NextZip, &onNextZip)
END_MESSAGE_MAP()


CityStateDlg::CityStateDlg(CWnd* pParent) : CDialogEx(IDD_CityState, pParent),
                                                            iter(zipList), zipDtm(0), ctyRcd(0) { }

CityStateDlg::~CityStateDlg() { }



BOOL CityStateDlg::OnInitDialog() {
  CDialogEx::OnInitDialog();   setCtls(CityLbl, StateLbl, ZipLbl);

  if (!tgt.isEmpty()) {set(zipCtl, tgt);   zipCtl.SetFocus();   onFindZip();}

  return TRUE;
  }


void CityStateDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_City,  cityCtl);
  DDX_Control(pDX, IDC_State, stateCtl);
  DDX_Control(pDX, IDC_Zip,   zipCtl);
  }


// CityState message handlers


void CityStateDlg::onFocusCity() {clrLbl(cityCtl, CityLbl);}


void CityStateDlg::onFocusState() {clrLbl(stateCtl, StateLbl);}


void CityStateDlg::onFocusZip()   {clrLbl(zipCtl, ZipLbl);}


void CityStateDlg::onFindZip() {

  tgt = compressZip(get(zipCtl));

  for (zipDtm = iter(); zipDtm; zipDtm = iter++) if (zipDtm->zip.find(tgt) >= 0)
               {ctyRcd = (*zipDtm)(); setCtls(ctyRcd->city, ctyRcd->state, ctyRcd->zip);   return;}
  clrCtls();   ctyRcd = 0;
  }


void CityStateDlg::onNextZip() {

  for (zipDtm = iter++; zipDtm; zipDtm = iter++) if (zipDtm->zip.find(tgt) >= 0)
               {ctyRcd = (*zipDtm)(); setCtls(ctyRcd->city, ctyRcd->state, ctyRcd->zip);   return;}
  clrCtls();   ctyRcd = 0;
  }


void CityStateDlg::OnOK() {CDialogEx::OnOK();}


void CityStateDlg::clrCtls() {clear(cityCtl); clear(stateCtl); clear(zipCtl);}


void CityStateDlg::setCtls(TCchar* cty, TCchar* st, TCchar* zp)
                       {set(cityCtl, cty);   set(stateCtl, st);   set(zipCtl, expandZip(zp));}

