// Current Members Prioritized


#include "pch.h"
#include "PriorityList.h"
#include "AsnTbl.h"
#include "EntTbl.h"
#include "MemberList.h"
#include "MbrTbl.h"


PriorityList::PriorityList() {
MbrListIter iter(memberList);
MbrInfo*    info;
MbrRcd*     mbrRcd;
int         mbrID;
EntRcd*     entRcd;
PLDsc*      plDsc;
int         priority;

  for (info = iter(); info; info = iter++) {

    if (!info->curMbr) continue;

    mbrRcd    = info->mbrRcd;         if (!mbrRcd) continue;
    mbrID  = mbrRcd->mbrEntityID;
    entRcd = entTbl.find(mbrID);      if (!entRcd) continue;

    plDsc = data.allocate();

    plDsc->info = info;

    priority = getPriority(asnTbl.find(mbrRcd->assgnPrefID));

    plDsc->key = priority;   plDsc->key += entRcd->lastName + entRcd->firstName;

    data = plDsc;
    }
  }




static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };


int PriorityList::getPriority(AsnRcd* asnRcd) {
int i;
int n = noElements(keys);

  if (!asnRcd) return n;

  for (i = 0; i < n; i++) if (asnRcd->aPKey == keys[i]) break;

  return i;
  }

