// Zip code list, sorted


#include "pch.h"
#include "ZipList.h"
#include "CurMbr.h"
#include "Utility.h"


ZipList zipList;                        // The one zip list


void ZipList::load() {
CtyIter iter(ctyTbl);
CtyRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) add(rcd);
  }



int ZipList::add(CComboBox& zipCtl, CEdit& cityCtl, CEdit& stateCtl) {
Cstring cs;
CtyRcd  cty;

   cityCtl.GetWindowText(cs);  cty.city  = cs;
  stateCtl.GetWindowText(cs);  cty.state = cs;
    zipCtl.GetWindowText(cs);  cty.zip   = compressZip(cs);

    if (!cty.city.isEmpty() || !cty.state.isEmpty() || !cty.zip.isEmpty()) {

      CtyRcd* rcd = ctyTbl.find(cty.zip);

      if (rcd) {
        if (rcd->city  != cty.city  && !cty.city.isEmpty())  rcd->city  = cty.city;
        if (rcd->state != cty.state && !cty.state.isEmpty()) rcd->state = cty.state;
        }
      else rcd = add(curMbr.addCtyTbl(cty));

      return rcd->getId();
      }

  return 0;
  }


CtyRcd* ZipList::add(CtyRcd* ctyRcd) {
ZipDtm  dtm;
ZipDtm* zipDtm;

  zipDtm = data.bSearch(dtm.add(ctyRcd));

  if (!zipDtm) zipDtm = data = dtm;   return (*zipDtm)();
  }



void ZipList::load(CComboBox& ctl, TCchar* tc) {
String  s = expandZip(tc);

  load(ctl);   ctl.SetCurSel(ctl.FindStringExact(-1, s));
  }


void ZipList::load(CComboBox& ctl) {
ZipIter iter(*this);
ZipDtm* dtm;
Cstring  cs;

  ctl.GetWindowText(cs);

  ctl.ResetContent();   addCB(ctl, _T(""), &nilRcd);

  for (dtm = iter(); dtm; dtm = iter++) dtm->add(ctl);

  ::set(ctl, cs);
  }


void ZipDtm::add(CComboBox& ctl) {if (!key.isEmpty()) addCB(ctl, expandZip(key), rcd);}


void ZipList::set(CComboBox& ctl, CEdit& cityCtl, CEdit& stateCtl) {
int     x   = ctl.GetCurSel();   if (x < 0) return;
CtyRcd& rcd = *(CtyRcd*)ctl.GetItemDataPtr(x);

  cityCtl.SetWindowText(rcd.city);   stateCtl.SetWindowText(rcd.state);
  }




////////--------------------

