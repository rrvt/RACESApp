// Member Badge No


#include "pch.h"
#include "MbrBadgeNo.h"
#include "IniFile.h"
#include "MbrTbl.h"
#include "MessageBox.h"


int MbrBadgeNo::findNext() {
MbrIter iter(mbrTbl);
MbrRcd* rcd;
int     n;

  for (lastBadgeNo = 0, rcd = iter(); rcd; rcd = iter++)
               {n = rcd->badgeNumber;   if (n > 0) add(n);   if (n > lastBadgeNo) lastBadgeNo = n;}

  return ++lastBadgeNo;
  }

