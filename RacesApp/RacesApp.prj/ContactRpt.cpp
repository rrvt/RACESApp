// Contact List sorted by Name and Call Sign


#include "pch.h"
#include "ContactRpt.h"
#include "Utility.h"


static const int PhoneTab = 11;
static const int FCCtab   =  8;


void ContactRpt::operator() (CurMbrSort sort) {
CurMbrList  curMbrList(sort);
CMbrIter    iter(curMbrList);
CurMbrData* item;
int         count = 0;

  callSignSort = sort == CallSignSort;

  header();

  for (item = iter(); item; item = iter++) {output(item);   count++;}

  msgCount(count);
  }


void ContactRpt::header() {
Date   dt;   dt.getToday();
String s = dt.getDate() + _T(" ") + dt.getTime();

  csv << _T("Contact List") << nCommas(11) << s << vCrlf;

  if (isCSsort()) csv << _T("Call Sign") << Comma << _T("Last Name") << Comma << _T("First Name");
  else            csv << _T("Last Name") << Comma << _T("First Name") << Comma << _T("Call Sign");
  csv << Comma << _T("Primary Phone");
  csv << Comma << _T("Cell Phone");
  csv << Comma << _T("Primary Text");
  csv << Comma << _T("Secdry Text");
  csv << Comma << _T("Primary eMail");
  csv << Comma << _T("Secondary eMail");
  csv << Comma << _T("Employer");
  csv << Comma << _T("Work Phone");
  csv << Comma << _T("work eMail");
  csv << vCrlf;
  }


void ContactRpt::output(CurMbrData* item) {

  if (isCSsort()) csv << item->callSign << Comma << item->lastName  << Comma << item->firstName;
  else            csv << item->lastName << Comma << item->firstName << Comma << item->callSign;
  csv << Comma << expandPhone(item->prmPhone);
  csv << Comma << expandPhone(item->celPhone);
  csv << Comma << expandPhone(item->prmText);
  csv << Comma << expandPhone(item->secText);
  csv << Comma << item->prmEmail << Comma << item->secEmail;
  if (item->isThirdLine()) {
    csv << Comma << item->employer;
    csv << Comma << expandPhone(item->wrkPhone);
    csv << Comma << item->wrkEmail;
    }
  csv << vCrlf;
  }




