// Prepare Address Record


#include "pch.h"
#include "PrepAdrRcd.h"
#include "CurMbr.h"


bool PrepAdrRcd::isDifferent(AdrRcd* adrRcd)
          {return !adrRcd || rcd.address1 != adrRcd->address1 || rcd.address2 != adrRcd->address2;}



AdrRcd* PrepAdrRcd::add() {
AdrRcd* r = adrTbl.find(rcd.address1, rcd.address2);

  if (!r) r = curMbr.addAdrTbl(rcd);   return r;
  }


