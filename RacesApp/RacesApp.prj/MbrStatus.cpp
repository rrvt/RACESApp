// Member Status Dropdown List


#include "pch.h"
#include "MbrStatus.h"
#include "MbrTbl.h"
#include "StsTbl.h"

//#include "MessageBox.h"

static const int DefaultSts = 0;


static TCchar* StatusList[3][2] = {{_T("Act"), _T("Active")},
                                   {_T("InA"), _T("Inactive")},
                                   {_T("Fmr"), _T("Former")}
                                   };

void MbrStatus::load() {
int i;
int index;

  listCtl.ResetContent();

  for (i = 0; i < noElements(StatusList); i++)
                    {index = listCtl.AddString(StatusList[i][1]);   listCtl.SetItemData(index, i);}
  }


void MbrStatus::setDefault() {listCtl.SelectString(-1, StatusList[DefaultSts][1]);}


// is Default setting

int  MbrStatus::isDefault() {
int k;
int i;

  k = listCtl.GetCurSel();

  i = 0 <= k && k < noElements(StatusList) ? (int) listCtl.GetItemData(k) : -1;

  return i == DefaultSts;
  }



void MbrStatus::set(MbrRcd* rcd) {
int     id     = rcd->statusID;
StsRcd* stsRcd = stsTbl.find(id);       if (!stsRcd) {listCtl.Clear();   return;}
String  abbr   = stsRcd->abbreviation;
int     i;

  for (i = 0; i < noElements(StatusList); i++) if (StatusList[i][0] == abbr)
                                            {listCtl.SelectString(-1, StatusList[i][1]);   return;}
  }


int MbrStatus::getID() {
Cstring cs;
int     k;
int     i;
String  abbr;
StsIter iter(stsTbl);
StsRcd* rcd;

  k = listCtl.GetCurSel();

  i = 0 <= k && k < noElements(StatusList) ? (int) listCtl.GetItemData(k) : 0;

  abbr = StatusList[i][0];

  for (rcd = iter(); rcd; rcd = iter++) if (rcd->abbreviation == abbr) return rcd->getId();

  return 0;
  }

