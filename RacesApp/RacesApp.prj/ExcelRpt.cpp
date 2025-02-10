//Excel Report


#include "pch.h"
#include "ExcelRpt.h"
#include "Database.h"
#include "MemberList.h"
#include "MessageBox.h"
#include "RNUtility.h"


void ExcelRpt::operator() () {
MbrListIter iter(memberList);
MbrInfo*    item;
int         count;

  header();

  for (count = 0, item = iter(); item; item = iter++) if (item->curMbr) {output(*item);   count++;}

  msgCount(count);
  }


void ExcelRpt::header() {

  memberHdr();      callsignHdr();     employerHdr();     iceHdr();     handHeldHdr();
  limitationsHdr(); preferencesHdr();  locationHdr();     commentHdr(); shirtSizeHdr();
  skillsHdr();      csv << vCrlf;
  }


void ExcelRpt::output(MbrInfo& info) {
MbrRcd& rcd     = *info.mbrRcd;
EntRcd* mbrRcd  =  info.mbrEnt;
EntRcd* emplRcd =  info.emplEnt;
EntRcd* iceRcd  =  info.iceEnt;
AsnRcd* asnRcd  =  info.asnRcd;
LocRcd* locRcd  =  info.locRcd;
StsRcd* stsRcd  =  info.stsRcd;

  csv << rcd.badgeNumber << Comma;

  if (rcd.textMsgPh1.isEmpty() && mbrRcd && !mbrRcd->phone2.isEmpty()) {
    rcd.textMsgPh1 = mbrRcd->phone2;
    String s = mbrRcd->firstName + _T(" ") + mbrRcd->lastName + _T("Text Message Dev blank");
    messageBox(s);
    }

  putEntity(mbrRcd, &rcd);

  putTxtPh(rcd);

  csv << rcd.callSign << Comma;

  putDates(rcd);

  putEntity(emplRcd);

  putEntity(iceRcd);

  putHandHeld(rcd);

  csv << replaceCrlf(rcd.limitations) << Comma;

  putAsn(asnRcd);

  putLoc(locRcd);

  csv << replaceCrlf(rcd.comments) << Comma;

  csv << rcd.shirtSize << Comma;
  csv << rcd.isOfficer << Comma;

  putSts(stsRcd);

  putSkills(rcd);

  csv << vCrlf;
  }



