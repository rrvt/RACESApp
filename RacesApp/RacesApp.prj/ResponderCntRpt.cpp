// Responder Counts by Attribute


#include "pch.h"
#include "ResponderCntRpt.h"
#include "Database.h"
#include "MemberList.h"




static TCchar* keys[5] = {_T("P"),
                          _T("E"),
                          _T("G"),
                          _T("A"),
                          _T("L")
                          };



void ResponderCntRpt::operator() ()  {
MbrListIter iter(memberList);
MbrInfo*    info;
MbrRcd*     mbrRcd;
AsnRcd*     asnRcd;
String      key;
String      dsc;
int         i;
int         counts[6];
int         total;

  for (i = 0; i < noElements(counts); i++) counts[i] = 0;

  for (info = iter(); info; info = iter++) {
    if (!info->curMbr) continue;

    mbrRcd = info->mbrRcd;

    counts[getRspClass(info->asnRcd)]++;
    }

  ar << aClrTabs << aSetRTab(72);

  for (i = 0, total = 0; i < noElements(counts); i++) {
    String k     = i < noElements(keys) ? keys[i] : _T("Nuts");

    asnRcd = asnTbl.find(k);
    dsc    = asnRcd ? asnRcd->txt : String(_T("Other"));

    ar << dsc << aTab << counts[i] << aCrlf;    total += counts[i];
    }

  ar << aTab << _T("------") << aCrlf;
  ar << _T("   Total") << aTab << total << aCrlf;

  msgCount(total);
  }


int ResponderCntRpt::getRspClass(AsnRcd* asnRcd) {
String key;
int    i;

  if (!asnRcd) return 5;

  key = asnRcd->aPKey;

  for (i = 0; i < noElements(keys); i++) if (key == keys[i]) break;

  return i;
  }







