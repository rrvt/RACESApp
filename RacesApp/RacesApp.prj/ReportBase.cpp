// Report Base -- Operations used several places


#include "pch.h"
#include "ReportBase.h"
#include "CSVOut.h"
#include "Database.h"
#include "MessageBox.h"
#include "Utility.h"



void ReportBase::memberHdr() {
  csv << _T("BadgeNumber") << Comma;
  csv << _T("mbrFirstName") << Comma;
  csv << _T("mbrMiddleInitial") << Comma;
  csv << _T("mbrLastName") << Comma;
  csv << _T("mbrSuffix") << Comma;
  csv << _T("mbrStreet") << Comma;
  csv << _T("mbrAptSuite") << Comma;
  csv << _T("mbrCity") << Comma;
  csv << _T("mbrState") << Comma;
  csv << _T("mbrZip") << Comma;
  csv << _T("mbrAddrIsPO") << Comma;
  csv << _T("mbrLocationZip") << Comma;
  csv << _T("mbrPrimaryEmail") << Comma;
  csv << _T("mbrSecondaryEmail") << Comma;

  csv << _T("mbrPhone") << Comma;
  csv << _T("mbrCell") << Comma;
  csv << _T("txtDevPrim") << Comma;
  csv << _T("txtDevSec") << Comma;
  }


void ReportBase::callsignHdr() {
  csv << _T("CallSign") << Comma;
  csv << _T("FCCExpiration") << Comma;
  csv << _T("StartDate") << Comma;
  csv << _T("DSWDate") << Comma;
  csv << _T("BadgeExpDate") << Comma;
  csv << _T("Responder") << Comma;
  }


void ReportBase::employerHdr() {
  csv << _T("emplFirstName") << Comma;
  csv << _T("emplMiddleInitial") << Comma;
  csv << _T("emplLastName") << Comma;
  csv << _T("emplSuffix") << Comma;
  csv << _T("emplStreet") << Comma;
  csv << _T("emplAptSuite") << Comma;
  csv << _T("emplCity") << Comma;
  csv << _T("emplState") << Comma;
  csv << _T("emplZip") << Comma;
  csv << _T("emplAddrIsPO") << Comma;
  csv << _T("emplLocationZip") << Comma;
  csv << _T("emplEmail") << Comma;
  csv << _T("emplPhone") << Comma;
  csv << _T("emplCell") << Comma;
  }


void ReportBase::iceHdr() {
  csv << _T("iceFirstName") << Comma;
  csv << _T("iceMiddleInitial") << Comma;
  csv << _T("iceLastName") << Comma;
  csv << _T("iceSuffix") << Comma;
  csv << _T("iceStreet") << Comma;
  csv << _T("iceAptSuite") << Comma;
  csv << _T("iceCity") << Comma;
  csv << _T("iceState") << Comma;
  csv << _T("iceZip") << Comma;
  csv << _T("iceAddrIsPO") << Comma;
  csv << _T("iceLocationZip") << Comma;
  csv << _T("iceEmail") << Comma;
  csv << _T("icePhone") << Comma;
  csv << _T("iceCell") << Comma;
  }


void ReportBase::handHeldHdr() {
  csv << _T("Handheld") << Comma;
  csv << _T("PortMobile") << Comma;
  csv << _T("PortPacket") << Comma;
  csv << _T("OtherEquip") << Comma;
  csv << _T("Multilingual") << Comma;
  csv << _T("OtherCapabilities") << Comma;
  }



void ReportBase::limitationsHdr() {
  csv << _T("Limitations") << Comma;
  }


void ReportBase::preferencesHdr() {
  csv << _T("AssgnPrefKey") << Comma;
  csv << _T("AssgnPrefDsc") << Comma;
  }


void ReportBase::locationHdr() {
  csv << _T("LocationPrefKey") << Comma;
  csv << _T("LocationPref") << Comma;
  }


void ReportBase::commentHdr() {
  csv << _T("Comments") << Comma;
  }


void ReportBase::shirtSizeHdr() {
  csv << _T("ShirtSize") << Comma;
  csv << _T("IsOfficer") << Comma;
  csv << _T("StatusAbr") << Comma;
  csv << _T("StatusDsc") << Comma;
  }


void ReportBase::skillsHdr() {
  csv << _T("SkillCertifications") << Comma;
  csv << _T("EOC_Certifications") << Comma;
  csv << _T("UpdateDate") << Comma;
  csv << _T("BadgeOK") << Comma;
  }





void ReportBase::putEntity(EntRcd* ent, MbrRcd* rcd) {
AdrRcd* addrRcd;
CtyRcd* cityRcd;

  if (!ent) {int n = rcd ? 15 : 14;   csv << nCommas(n);   return;}

  csv << ent->firstName      << Comma;
  csv << ent->middleInitial  << Comma;
  csv << ent->lastName       << Comma;
  csv << ent->suffix         << Comma;

  addrRcd = adrTbl.find(ent->addrID);

  if (addrRcd) {
    csv << addrRcd->address1 << Comma;
    csv << addrRcd->address2 << Comma;
    }
  else csv << nCommas(2);

  cityRcd = ctyTbl.find(ent->cityStID);

  if (cityRcd) {
    csv << cityRcd->city  << Comma;
    csv << cityRcd->state << Comma;
    csv << expandZip(cityRcd->zip)   << Comma;
    }
  else csv << nCommas(3);

  csv << ent->addrIsPO       << Comma;
  csv << expandZip(ent->locationZip)    << Comma;
  csv << ent->eMail          << Comma;
  if (rcd) csv << rcd->secondaryEmail << Comma;
  csv << expandPhone(ent->phone1)     << Comma;
  csv << expandPhone(ent->phone2)     << Comma;
  }


void ReportBase::putTxtPh(MbrRcd& rcd) {
  csv << expandPhone(rcd.textMsgPh1) << Comma;
  csv << expandPhone(rcd.textMsgPh2) << Comma;
  }



void ReportBase::putDates(MbrRcd& rcd) {
    csv << expandDate(rcd.fCCExpiration)  << Comma;
    csv << expandDate(rcd.startDate)      << Comma;
    csv << expandDate(rcd.dSWDate)        << Comma;
    csv << expandDate(rcd.badgeExpDate)   << Comma;
    csv << expandDate(rcd.responder)      << Comma;
    }


void ReportBase::putHandHeld(MbrRcd& rcd) {
  csv << utl.replaceCrlf(rcd.handHeld)          << Comma;
  csv << utl.replaceCrlf(rcd.portMobile)        << Comma;
  csv << utl.replaceCrlf(rcd.portPacket)        << Comma;
  csv << utl.replaceCrlf(rcd.otherEquip)        << Comma;
  csv << utl.replaceCrlf(rcd.multilingual)      << Comma;
  csv << utl.replaceCrlf(rcd.otherCapabilities) << Comma;
  }


void ReportBase::putAsn(AsnRcd* asnRcd) {

  if (!asnRcd) {csv << nCommas(2); return;}

  csv << asnRcd->aPKey << Comma;
  csv << asnRcd->txt   << Comma;
  }


void ReportBase::putLoc(LocRcd* locRcd) {

  if (!locRcd) {csv << nCommas(2);   return;}

  csv << locRcd->key << Comma;
  csv << locRcd->txt << Comma;
  }


void ReportBase::putSts(StsRcd* stsRcd) {
  if (!stsRcd) {csv << nCommas(2);   return;}

  csv << stsRcd->abbreviation << Comma;
  csv << stsRcd->description  << Comma;
  }


void ReportBase::putSkills(MbrRcd& rcd) {
  csv << utl.replaceCrlf(rcd.skillCertifications) << Comma;
  csv << utl.replaceCrlf(rcd.eOC_Certifications)  << Comma;
  csv << expandDate(rcd.updateDate)           << Comma;

  csv << rcd.badgeOK             << Comma;
  }


void ReportBase::msgCount(int count)
                                  {String s;   s.format(_T("%i Records"), count);   messageBox(s);}



#if 0
String& ReportBase::replaceCrlf(TCchar* tc) {
String        s;
static String t;
int           i;
int           n;

  if (!tc) return t;

  s = tc;

  for (n = s.length(), i = 0; i < n; i++) {
    Tchar ch = s[i];

    if (ch == _T('\r')) continue;
    if (ch == _T('\n')) {t += _T("; "); continue;}
    t += ch;
    }
  return t;
  }
#endif
