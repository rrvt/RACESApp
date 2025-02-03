// Zip code list, sorted


#include "pch.h"
#include "ZipList.h"
#include "CityStateDlg.h"
#include "CurMbr.h"
#include "RNUtility.h"


ZipList zipList;                        // The one zip list


void ZipList::load() {
CtyIter iter(ctyTbl);
CtyRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) add(rcd);
  }



int ZipList::add(CEdit& cityCtl, CEdit& stateCtl, CEdit& zipCtl) {
Cstring cs;
CtyRcd  cty;

   cityCtl.GetWindowText(cs);  cty.city  = cs;
  stateCtl.GetWindowText(cs);  cty.state = cs;
    zipCtl.GetWindowText(cs);  cty.zip   = compressZip(cs);

    if (!cty.city.isEmpty() || !cty.state.isEmpty() || !cty.zip.isEmpty()) {

      CtyRcd* rcd = ctyTbl.find(cty.zip);

      if (!rcd) rcd = add(curMbr.addCtyTbl(cty));      return rcd->getId();
      }

  return 0;
  }


CtyRcd* ZipList::add(CtyRcd* ctyRcd) {
ZipDtm  dtm;
ZipDtm* zipDtm;

  dtm.add(ctyRcd);   zipDtm = data.bSearch(dtm.zip);

  if (!zipDtm) zipDtm = data = dtm;   return (*zipDtm)();
  }



CtyRcd* ZipList::find(TCchar* tc) {
String        tgt = compressZip(tc);
ZipIter       iter(*this);
ZipDtm*       dtm;
CityStateDlg  dlg;

  for (dtm = iter(); dtm; dtm = iter++) if (dtm->zip == tgt) return (*dtm)();

  dlg.tgt = tgt;

  if (dlg.DoModal() == IDOK && dlg.ctyRcd) return dlg.ctyRcd;

  return 0;
  }



////------------

#if 1
#else
    set(emplCityCtl,  dlg.ctyRcd->city);
    set(emplStateCtl, dlg.ctyRcd->state);
    set(emplZipCtl,   expandZip(dlg.ctyRcd->zip));
#endif

