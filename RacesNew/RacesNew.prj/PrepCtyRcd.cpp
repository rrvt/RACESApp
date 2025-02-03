// Prepare City Record


#include "pch.h"
#include "PrepCtyRcd.h"
#include "CurMbr.h"


// 95132-2630 becomes 951322630

String PrepCtyRcd::compressZip(TCchar* tc) {
String s   = tc;   s.trim();
int    pos = s.find(_T('-'));
String t;

  if (pos < 0) return s;

  t = s.substr(0, pos);   pos++;   t += s.substr(pos);   return t;
  }



bool PrepCtyRcd::isDifferent(CtyRcd* ctyRcd) {

  return !ctyRcd || rcd.city != ctyRcd->city  ||
                                              rcd.state != ctyRcd->state || rcd.zip != ctyRcd->zip;
  }


CtyRcd* PrepCtyRcd::add() {
CtyRcd* r = ctyTbl.find(rcd.zip);

  if (!r) r = curMbr.addCtyTbl(rcd);   return r;
  }


