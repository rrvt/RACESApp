


#include "pch.h"
#include "ProblemEntriesRpt.h"
#include "Database.h"
#include "MemberList.h"
#include "MessageBox.h"
#include "Utility.h"


void ProblemEntriesRpt::operator() () {
MbrListIter iter(memberList);
MbrInfo*    item;
int         count;

  header();

  for (count = 0, item = iter(); item; item = iter++)
                                                  if (isProblem(*item)) {output(*item);   count++;}
  msgCount(count);
  }


bool ProblemEntriesRpt::isProblem(MbrInfo& info) {
MbrRcd& rcd     = *info.mbrRcd;   if (!info.curMbr)                        return false;
AsnRcd* asnRcd  =  info.asnRcd;   //if (!asnRcd || asnRcd->aPKey == _T("O")) return true;
//LocRcd* locRcd  =  info.locRcd;   if (!locRcd || locRcd->key   == _T("O")) return true;

  if (!rcd.badgeOK && asnRcd->aPKey != _T("A")) return true;
  if ( rcd.badgeOK && asnRcd->aPKey == _T("A")) return true;

  return false;
  }




void ProblemEntriesRpt::header() {

  csv << _T("mbrFirstName") << Comma;
  csv << _T("mbrLastName") << Comma;
  csv << _T("BadgeOK") << Comma;
  preferencesHdr();

#if 0
  memberHdr();      callsignHdr();     employerHdr();     iceHdr();     handHeldHdr();
  limitationsHdr();   locationHdr();     commentHdr(); shirtSizeHdr();
  skillsHdr();
#endif

  csv << vCrlf;
  }


void ProblemEntriesRpt::output(MbrInfo& info) {
MbrRcd& rcd     = *info.mbrRcd;
EntRcd* mbrRcd  =  info.mbrEnt;     if (!mbrRcd) return;
AsnRcd* asnRcd  =  info.asnRcd;
//LocRcd* locRcd  =  info.locRcd;
//StsRcd* stsRcd  =  info.stsRcd;

//csv << rcd.badgeNumber << Comma;

  if (rcd.textMsgPh1.isEmpty() && mbrRcd && !mbrRcd->phone2.isEmpty()) {
    rcd.textMsgPh1 = mbrRcd->phone2;
    String s = mbrRcd->firstName + _T(" ") + mbrRcd->lastName + _T("Text Message Dev blank");
    messageBox(s);
    }

  csv << mbrRcd->firstName << Comma;
  csv << mbrRcd->lastName  << Comma;
  csv << rcd.badgeOK       << Comma;

#if 0
  putTxtPh(rcd);

  csv << rcd.callSign << Comma;

  putDates(rcd);

  putEntity(emplRcd);

  putEntity(iceRcd);

  putHandHeld(rcd);

  csv << replaceCrlf(rcd.limitations) << Comma;
#endif
  putAsn(asnRcd);

//  putLoc(locRcd);
#if 0
  csv << replaceCrlf(rcd.comments) << Comma;

  csv << rcd.shirtSize << Comma;
  csv << rcd.isOfficer << Comma;

  putSts(stsRcd);

  putSkills(rcd);
#endif
  csv << vCrlf;
  }
