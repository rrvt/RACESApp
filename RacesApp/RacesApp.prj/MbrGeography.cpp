// Member Geography List


#include "pch.h"
#include "MbrGeography.h"
#include "LocTbl.h"
#include "MbrTbl.h"


static const int DefaultGeo = 0;


static TCchar* Geography[5][2] = {{_T("A"), _T("Any Where")},
                                  {_T("5"), _T("Five Miles")},
                                  {_T("1"), _T("One Mile")},
                                  {_T("n"), _T("Neighborhood")},
                                  {_T("O"), _T("Other")},
                                  };


void MbrGeography::load() {
int i;
int index;

  listCtl.ResetContent();

  for (i = 0; i < noElements(Geography); i++)
   {index = listCtl.AddString(Geography[i][1]);   listCtl.SetItemData(index, i);}
  }


void MbrGeography::set(MbrRcd* rcd) {
int     id     = rcd->locationPrefID;
LocRcd* locRcd = locTbl.find(id);     if (!locRcd) {listCtl.Clear();   return;}
String  abbr   = locRcd->key;
int     i;

  for (i = 0; i < noElements(Geography); i++)
        if (Geography[i][0] == abbr) {listCtl.SelectString(0, Geography[i][1]);   return;}
  }


void MbrGeography::setDefault() {listCtl.SelectString(-1, Geography[DefaultGeo][1]);}


// is Default setting

int  MbrGeography::isDefault() {
int k;
int i;

  k = listCtl.GetCurSel();

  i = 0 <= k && k < noElements(Geography) ? listCtl.GetItemData(k) : -1;

  return i == DefaultGeo;
  }


int MbrGeography::getID() {
Cstring cs;
int     k;
int     i;
String  abbr;
LocIter iter(locTbl);
LocRcd* rcd;

  k = listCtl.GetCurSel();

  i = 0 <= k && k < noElements(Geography) ? listCtl.GetItemData(k) : 0;

  abbr = Geography[i][0];

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->key == abbr) return rcd->getId();

  return 0;
  }

