// List of Members suitable for sorting


#include "pch.h"
#include "MemberList.h"
#include "CurMbr.h"
#include "Database.h"
#include "MbrTbl.h"


bool MemberList::isPresent(TCchar* callSign) {return mbrTbl.find(callSign) != 0;}


void MemberList::create() {
MbrIter  iter(mbrTbl);
MbrRcd*  rcd;

  data.clear();   maxNonResp = 0;

  for (rcd = iter(); rcd; rcd = iter++) {updateNonResp(rcd); add(rcd);}
  }


String MemberList::nextNonResp() {String s;   s.format(_T("~%04i*"), ++maxNonResp);   return s;}


void MemberList::updateNonResp(MbrRcd* rcd) {
String s;
int    x;
uint   pos;

  if (!asnTbl.isNonResp(rcd->assgnPrefID)) return;

  s = rcd->callSign;   s.trim();

  if (s[0] == _T('~')) {x = s.substr(1, 4).stoi(pos);   if (x > maxNonResp) maxNonResp = x;}
  }



MbrInfo* MemberList::add(MbrRcd* rcd) {
MbrInfo* info;
MbrRcd*  r;

  if (!rcd) return 0;

  r = mbrTbl.find(rcd->callSign);

  rcd = r ? r : curMbr.addMbrTbl(*rcd);

  info = data.allocate();   if (!info->set(rcd)) {data.deallocate(info); return 0;}

  return data = info;
  }
