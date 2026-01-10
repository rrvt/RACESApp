


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
MbrRcd& rcd     = *info.mbrRcd;   if (!info.curMbr) return false;
AsnRcd* asnRcd  =  info.asnRcd;

  if (!rcd.badgeOK && asnRcd->aPKey != _T("A")) return true;
  if ( rcd.badgeOK && asnRcd->aPKey == _T("A")) return true;

  return false;
  }




void ProblemEntriesRpt::header() {

  csv << _T("mbrFirstName") << Comma;
  csv << _T("mbrLastName") << Comma;
  csv << _T("BadgeOK") << Comma;
  preferencesHdr();

  csv << vCrlf;
  }


void ProblemEntriesRpt::output(MbrInfo& info) {
MbrRcd& rcd     = *info.mbrRcd;
EntRcd* mbrRcd  =  info.mbrEnt;     if (!mbrRcd) return;
AsnRcd* asnRcd  =  info.asnRcd;

  if (rcd.textMsgPh1.isEmpty() && mbrRcd && !mbrRcd->phone2.isEmpty()) {
    rcd.textMsgPh1 = mbrRcd->phone2;
    String s = mbrRcd->firstName + _T(" ") + mbrRcd->lastName + _T("Text Message Dev blank");
    messageBox(s);
    }

  csv << mbrRcd->firstName << Comma;
  csv << mbrRcd->lastName  << Comma;
  csv << rcd.badgeOK       << Comma;

  putAsn(asnRcd);

  csv << vCrlf;
  }
