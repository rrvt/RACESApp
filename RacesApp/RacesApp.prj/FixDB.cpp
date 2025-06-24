


#include "pch.h"
#include "FixDB.h"
#include "AdrTbl.h"
#include "EntTbl.h"
#include "MessageBox.h"


int FixDB::addr() {
AdrIter iter(adrTbl);
AdrRcd* rcd;
String  s;
int     cnt = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    if (rcd->address2.find(_T("<")) >= 0) {
//    s.format(_T("Rcd: %s, %s"), rcd->address1.str(), rcd->address2.str());   messageBox(s);
      if (!findEnt(rcd->getId())) {iter.remove(); cnt++;}
      }
    }
  return cnt;
  }


bool FixDB::findEnt(uint adrId) {
EntIter iter(entTbl);
EntRcd* rcd;
String  s;

  for (rcd = iter(); rcd; rcd = iter++) {
    if (rcd->addrID == adrId) {
//    s.format(_T("Ent: %s %s"), rcd->firstName, rcd->lastName);   messageBox(s);
      return true;
      }
    }

  return false;
  }

