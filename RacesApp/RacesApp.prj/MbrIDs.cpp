// Member IDs, i.e. Call Signs alone and Call Signs, Names, etc...


#include "pch.h"
#include "MbrIDs.h"


void MbrIDs::operator() (MbrIDList listType) {
CurMbrList  curMbrList(listType < SuffixList ? CallSignSort : SuffixSort);
CMbrIter    iter(curMbrList);
CurMbrData* item;
int         count;
Tchar       ch;

  for (count = 0, ch = _T('0'), item = iter(); item; item = iter++) {

    if (item->key[0] != ch) {csv << vCrlf;  ch = item->key[0];}

    csv << item->callSign;
    if (listType > CallSignList) {
      csv << Comma << item->firstName;
      csv << Comma << item->lastName;
      csv << Comma << item->badgeNumber;
      }

    csv << vCrlf;   count++;
    }

  msgCount(count);
  }

