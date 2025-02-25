// Address List, sorted


#include "pch.h"
#include "AddrList.h"
#include "CurMbr.h"
#include "Utility.h"


AddrList addrList;                      // The one Address List sorted by address1


static String get(String& addr1, String& addr2);


void AddrList::load() {
AdrIter iter(adrTbl);
AdrRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) add(rcd);
  }


int AddrList::add(CComboBox& streetCtl, CEdit& unitCtl) {
Cstring cs;
AdrRcd  adr;

  streetCtl.GetWindowText(cs);  adr.address1 = cs;
    unitCtl.GetWindowText(cs);  adr.address2 = cs;

  if (!adr.address1.isEmpty() || !adr.address2.isEmpty()) {

    AdrRcd* rcd = adrTbl.find(adr.address1, adr.address2);

    if (!rcd) rcd = add(curMbr.addAdrTbl(adr));   return rcd->getId();
    }

  return 0;
  }


AdrRcd* AddrList::add(AdrRcd* adrRcd) {
AdrDtm  dtm;
AdrDtm* adrDtm;

  if (!adrRcd) return 0;

  adrDtm = data.bSearch(dtm.add(adrRcd));

  if (!adrDtm) adrDtm = data = dtm;   return (*adrDtm)();
  }



String& AdrDtm::add(AdrRcd* adrRcd) {

  rcd = adrRcd;

  return key = get(adrRcd->address1, adrRcd->address2);
  }


void AddrList::load(CComboBox& ctl, CEdit& unitCtl, String& addr1, String& addr2) {
String   tgt = get(addr1, addr2);

  load(ctl);   index = ctl.FindStringExact(-1, tgt);   set(ctl, unitCtl);
  }


String get(String& addr1, String& addr2)
                   {String s = addr1;   if (!addr2.isEmpty()) s += _T(", ") + addr2;   return s;}


void AddrList::load(CComboBox& ctl) {
AddrIter iter(*this);
AdrDtm*  dtm;
Cstring  cs;

  ctl.GetWindowText(cs);

  ctl.ResetContent();   addCB(ctl, _T(""), &nilRcd);

  for (dtm = iter(); dtm; dtm = iter++) dtm->add(ctl);

  ::set(ctl, cs);                 //  if (!cs.isEmpty()) ctl.SetWindowText(cs);
  }


void AdrDtm::add(CComboBox& ctl) {if (!key.isEmpty()) addCB(ctl, key, rcd);}


void AddrList::getSel(CComboBox& ctl) {index = ctl.GetCurSel();}


void AddrList::set(CComboBox& ctl, CEdit& unitCtl) {
int     x   = index;   if (x < 0) {unitCtl.Clear();   return;}              //ctl.GetCurSel();
AdrRcd& rcd = *(AdrRcd*) ctl.GetItemDataPtr(x);

  ctl.SetWindowText(rcd.address1);   unitCtl.SetWindowText(rcd.address2);   index = -1;
  }




/////////////////----------------------

#if 1
#else
    x = ctl.AddString(s);   if (x < 0) continue;

    ctl.SetItemDataPtr(x, &rcd);
#endif
#if 1
#else
  {
    AdrRcd* rcd = (*dtm)();

    s = dtm->getKey();   if (s.isEmpty()) continue;
    addCB(ctl, s, rcd);
    }
#endif

