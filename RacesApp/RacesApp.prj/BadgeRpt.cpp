// Badge Reports


#include "pch.h"
#include "BadgeRpt.h"
#include "Database.h"
#include "MemberList.h"
//#include "MessageBox.h"
#include "Utility.h"


void BadgeRpt::operator() (CurMbrSort sort) {
CurMbrList  curMbrList(sort);
CMbrIter    iter(curMbrList);
CurMbrData* item;
int         count;

  tab2 = 8    + curMbrList.maxBgFirst() + 2;
  tab3 = tab2 + curMbrList.maxBgLast()  + 2;
  tab4 = tab3 + 4;

  ar << aClrTabs << aSetTab(8) << aSetTab(tab2) << aSetTab(tab3) << aSetTab(tab4);

  for (count = 0, item = iter(); item; item = iter++) if (item->badgeOk) {output(*item);  count++;}

  msgCount(count);
  }


void BadgeRpt::output(CurMbrData& item) {


    String t; t.format(_T("%03s"), item.badgeNumber.str());

    ar << item.callSign << aTab;
    ar << item.firstName<< aTab;
    ar << item.lastName << aTab;
    ar << t             << aTab;
    ar << expandDate(item.badgeExpDate) << aCrlf;
  }


////------------------

#if 0
int        i;
int        n;
int        lng;
int        maxFn = 0;
int        maxLn = 0;


  for (item = iter(); item ; item = iter++) {
    if (!item->curMbr) continue;

    MbrInfo memberInfo;     if (!memberInfo.get(*item->rcd)) continue;


    if (badgeSort == BdgDateSort) memberInfo.sortKey  = getDateKey(memberInfo.badgeExpDate);
    memberInfo.sortKey += memberInfo.callSign;

    lng = memberInfo.firstName.length();  if (lng > maxFn) maxFn = lng;
    lng = memberInfo.lastName.length();   if (lng > maxLn) maxLn = lng;

    data = memberInfo;
    }

  int tab2 = 8    + maxFn + 2;
  int tab3 = tab2 + maxLn + 2;
  int tab4 = tab3 + 4;
#endif
#if 0
int         maxFn = 0;
int         maxLn = 0;

  for (item = iter(); item; item = iter++)
             if (item->badgeOk) {setMax(item->firstName, maxFn);   setMax(item->lastName,  maxLn);}
#endif

