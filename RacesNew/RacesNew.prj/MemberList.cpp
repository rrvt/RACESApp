// List of Members suitable for sorting


#include "pch.h"
#include "MemberList.h"
#include "CurMbr.h"
#include "Database.h"
#include "MbrTbl.h"


MemberList memberList;


void MemberList::create() {
MbrIter  iter(mbrTbl);
MbrRcd*  rcd;

  for (rcd = iter(); rcd; rcd = iter++) add(rcd);
  }


MbrInfo* MemberList::add(MbrRcd* rcd) {
MbrInfo* info;
MbrRcd*  r;

  if (!rcd) return 0;

  r = mbrTbl.find(rcd->callSign);

  rcd = r ? r : curMbr.addMbrTbl(*rcd);

  info = data.allocate();   if (!info->get(rcd)) {data.deallocate(info); return 0;}

  return data = info;
  }



////-------------

#if 1
#else
    info = data.allocate();   if (!info->get(rcd)) {data.deallocate(info); continue;}

    data = info;
#endif

