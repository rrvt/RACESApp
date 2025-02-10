// Member IDs, i.e. Call Signs alone and Call Signs, Names, etc...


#include "pch.h"
#include "MbrIDs.h"


void MbrIDs::operator() (bool plus) {
CurMbrList  curMbrList(CallSignSort);
CMbrIter    iter(curMbrList);
CurMbrData* item;
int         count;

  for (count = 0, item = iter(); item; item = iter++) {
    csv << item->callSign;
    if (plus) {
      csv << Comma << item->firstName;
      csv << Comma << item->lastName;
      csv << Comma << item->badgeNumber;
      }

    csv << vCrlf;   count++;
    }

  msgCount(count);
  }

