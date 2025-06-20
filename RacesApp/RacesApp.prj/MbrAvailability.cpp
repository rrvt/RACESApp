// Availability Drop Down List


#include "pch.h"
#include "MbrAvailability.h"
#include "AsnTbl.h"
#include "MbrTbl.h"


static TCchar* AvailList[6][2] = {{_T("P"), _T("Primary")},
                                  {_T("E"), _T("Secondary")},
                                  {_T("G"), _T("May Respond")},
                                  {_T("L"), _T("Last Resort")},
                                  {_T("O"), _T("Other")},
                                  {_T("A"), _T("ARES Only")}
                                  };


void MbrAvailability::load() {
int i;
int index;

  listCtl.ResetContent();

  for (i = 0; i < noElements(AvailList); i++)
    {index = listCtl.AddString(AvailList[i][1]);   listCtl.SetItemData(index, i);}
  }


void MbrAvailability::set(MbrRcd* rcd) {
int     id     = rcd->assgnPrefID;
AsnRcd* asnRcd = asnTbl.find(id);    if (!asnRcd) {listCtl.Clear();   return;}
String  abbr   = asnRcd->aPKey;
int     i;

  for (i = 0; i < noElements(AvailList); i++)
                 if (AvailList[i][0] == abbr) {listCtl.SelectString(0, AvailList[i][1]);   return;}
  }


void MbrAvailability::setDefault() {listCtl.SelectString(-1, AvailList[4][1]);}


int MbrAvailability::getID() {
Cstring cs;
int     k;
int     i;
String  abbr;
AsnIter iter(asnTbl);
AsnRcd* rcd;

  k = listCtl.GetCurSel();

  i = 0 <= k && k < noElements(AvailList) ? listCtl.GetItemData(k) : 0;

  abbr = AvailList[i][0];

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->aPKey == abbr) return rcd->getId();

  return 0;
  }

