// Address List, sorted


#include "pch.h"
#include "AddrList.h"
#include "CurMbr.h"

AddrList addrList;                      // The one Address List sorted by address1


void AddrList::load() {
AdrIter iter(adrTbl);
AdrRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) add(rcd);
  }


int AddrList::add(CEdit& streetCtl, CEdit& unitCtl) {
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

  dtm.add(adrRcd);   adrDtm = data.bSearch(dtm.addr);

  if (!adrDtm) adrDtm = data = dtm;   return (*adrDtm)();
  }

