// Former Member Report


#include "pch.h"
#include "FormerRpt.h"
#include "Database.h"
#include "MemberList.h"
#include "MessageBox.h"
#include "Utility.h"



void FormerRpt::operator() (TCchar* begPrd, TCchar* endPrd) {
MbrListIter iter(memberList);
MbrInfo*    item;
int         count;

  beg = getDate(begPrd);   end = getDate(endPrd);

  header();

  for (count = 0, item = iter(); item; item = iter++) if (!item->curMbr && output(*item)) count++;

  msgCount(count);
  }


void FormerRpt::header() {

  memberHdr();      callsignHdr();     employerHdr();     iceHdr();     handHeldHdr();
  limitationsHdr(); preferencesHdr();  locationHdr();     commentHdr(); shirtSizeHdr();
  skillsHdr();      csv << vCrlf;
  }




bool FormerRpt::output(MbrInfo& info) {
MbrRcd& rcd     = *info.mbrRcd;
EntRcd* mbrRcd  =  info.mbrEnt;
EntRcd* emplRcd =  info.emplEnt;
EntRcd* iceRcd  =  info.iceEnt;
AsnRcd* asnRcd  =  info.asnRcd;
LocRcd* locRcd  =  info.locRcd;
StsRcd* stsRcd  =  info.stsRcd;

  if (!inPeriod(rcd.updateDate)) return false;

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

  csv << vCrlf;   return true;
  }


bool FormerRpt::inPeriod(TCchar* tc) {
String s   = compressDate(tc);
int    lng = s.length();
String yymm;
uint   dt;

  if      (lng == 6) yymm = s.substr(4, 2) + s.substr(0, 2);
  else if (lng == 8) yymm = s.substr(6, 2) + s.substr(0, 2);
  else               yymm = s;

  dt = getDate(yymm);

  return beg <= dt && dt <= end;
  }

