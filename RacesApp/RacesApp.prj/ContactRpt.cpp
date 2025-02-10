// Contact List sorted by Name and Call Sign


#include "pch.h"
#include "ContactRpt.h"
#include "RNUtility.h"


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



#if 0
void ContactRpt::line1(CurMbrData* item) {

  if (isCSsort()) {
    ar << item->callSign;
    ar << aTab << item->lastName  << Comma << _T(' ') << item->firstName;
    }
  else {
    ar << item->lastName  << Comma << _T(' ') << item->firstName;
    ar << aTab << item->callSign;
    }
  ar << aTab << expandPhone(item->prmPhone);
  ar << aTab << expandPhone(item->celPhone);
  ar << aTab << expandPhone(item->prmText);
  ar << aTab << expandPhone(item->secText);
  ar << aCrlf;
  }


void ContactRpt::line2(CurMbrData* item)
                                 {ar << aTab << item->prmEmail << aTab << item->secEmail << aCrlf;}


// !item->employer.isEmpty() && (!item->wrkEmail.isEmpty() || !item->wrkPhone.isEmpty())

void ContactRpt::line3(CurMbrData* item) {

  if (item->isThirdLine()) {
    ar << aTab << item->employer << aTab << expandPhone(item->wrkPhone);
    ar << aTab << item->wrkEmail << aCrlf;
    }
  }


void ContactRpt::setTabs(CurMbrList& list) {
CurMbrSort sort = list.sort();
bool       csSort = sort == CallSignSort;
int        tab1 = csSort ? FCCtab : list.maxName() * 8 /10;
int        tab2 = tab1 + (csSort ? list.maxName() * 8 / 10 : FCCtab);
int        tab3 = tab2 + PhoneTab;
int        tab4 = tab3 + PhoneTab;
int        tab5 = tab4 + PhoneTab;

  ar << aClrTabs;
  ar << aSetTab(tab1) << aSetTab(tab2) << aSetTab(tab3) << aSetTab(tab4) << aSetTab(tab5);
  }


void ContactRpt::setTabs2(CurMbrList& list) {
int tab1 = FCCtab;
int tab2 = tab1 + list.maxEmail() * 8 / 10;

  ar << aClrTabs << aSetTab(tab1) << aSetTab(tab2);
  }


void ContactRpt::setTabs3(CurMbrList& list) {
int tab1 = FCCtab;
int tab2 = tab1 + list.maxEmpl() * 8 / 10;
int tab3 = tab2 + PhoneTab;

  ar << aClrTabs << aSetTab(tab1) << aSetTab(tab2) << aSetTab(tab3);
  }
#endif

