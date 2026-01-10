// Google Earch Report


#include "pch.h"
#include "GoogleRpt.h"
#include "AdrTbl.h"
#include "AsnTbl.h"
#include "CtyTbl.h"
#include "EntTbl.h"
#include "LocTbl.h"
#include "MemberList.h"
//#include "MessageBox.h"
#include "MbrTbl.h"
#include "PriorityList.h"
#include "Utility.h"
#include "StsTbl.h"


void GoogleRpt::operator() () {
PriorityList pl;
PLIter       iter(pl);
PLDsc*       dsc;
int          count;

  header();

  for (count = 0, dsc = iter(); dsc; dsc = iter++) if (dsc->info) {
    if (output(*dsc->info, false)) count++;   if (output(*dsc->info, true)) count++;
    }

  msgCount(count);
  }


void GoogleRpt::header() {
  csv << _T("Call Sign")   << Comma;
  csv << _T("Name")        << Comma;
  csv << _T("Status")      << Comma;
  csv << _T("Type")        << Comma;
  csv << _T("Priority")    << Comma;
  csv << _T("Location")    << Comma;
  csv << _T("Limitations") << Comma;
  csv << _T("Addr Type")   << Comma;
  csv << _T("Address")     << Comma;
  csv << _T("Cell")        << Comma;
  csv << _T("Phone")       << Comma;
  csv << _T("eMail")       << Comma;
  csv << _T("SMS Text")    << Comma;
  csv << _T("Languages")   << Comma;
  csv << _T("Equipment")   << Comma;
  csv << _T("Other")       << Comma;
  csv << _T("Comment")     << Comma;
  csv << _T("Label")       << Comma;
  csv << vCrlf;
  }


bool GoogleRpt::output(MbrInfo& info, bool workAddr) {
MbrRcd& rcd             = *info.mbrRcd;
EntRcd* mbrEnt          =  info.mbrEnt;
EntRcd* emplEnt         =  info.emplEnt;
AsnRcd* asnRcd          =  info.asnRcd;
LocRcd* locRcd          =  info.locRcd;
StsRcd* stsRcd          =  info.stsRcd;
AdrRcd* addrRcd;

String  s;
String  addrType        = workAddr ? _T("Work") : _T("Home");

EntRcd* r               = workAddr ? emplEnt : mbrEnt;
bool    avail           = addrAvail(r, addrRcd);

  if (workAddr && !avail) return false;

  csv << rcd.callSign << Comma;

  s = mbrEnt->firstName + _T(' ') + mbrEnt->lastName;
  if (!mbrEnt->suffix.isEmpty()) s += mbrEnt->suffix;
  csv << s << Comma;

  if (stsRcd) {
    s = stsRcd->abbreviation == "Act" ? _T("Active") : _T("Inactive");
    csv << s << Comma;
    }
  else csv << Comma;

  s =  rcd.responder.trim().isEmpty() ? _T("Non-Responder") : _T("Responder");
  s += rcd.dSWDate.trim().isEmpty()   ? _T(" - No DSW")     : _T(" - DSW");
  csv << s << Comma;

  if (asnRcd) {
    s = asnRcd->aPKey;
    if      (s == _T("P")) s = _T("1st Call");
    else if (s == _T("E")) s = _T("not 1st Call");
    else if (s == _T("G")) s = _T("General");
    else if (s == _T("L")) s = _T("Last Call");
    else if (s == _T("A")) s = _T("ARES Only");
    else if (s == _T("N")) s = _T("Non-Responder");
    else                   s = asnRcd->txt;
    csv << s << Comma;
    }
  else csv << _T("ARES Only") << Comma;

  if (locRcd) {
    s = locRcd->key;
    if      (s == _T("A")) s = _T("Anywhere in city");
    else if (s == _T("5")) s = _T("Within 5 miles");
    else if (s == _T("1")) s = _T("Within 1 mile");
    else if (s == _T("N")) s = _T("Within neighborhood");
    else                   s = locRcd->txt;
    csv << s << Comma;
    }
  else csv << _T("Anywhere") << Comma;

  csv << utl.replaceCrlf(rcd.limitations) << Comma;

  csv << addrType << Comma;

  putEntity(r, addrRcd);

  csv << expandPhone(rcd.textMsgPh1) << Comma;

  csv << mbrEnt->eMail << Comma;

  csv << rcd.multilingual << Comma;

  s.clear();

  appdAttr(s, _T("HT:"),    rcd.handHeld);
  appdAttr(s, _T("Port:"),  rcd.portMobile);
  appdAttr(s, _T("Pkt:"),   rcd.portPacket);
  appdAttr(s, _T("Other:"), rcd.otherEquip);

  csv << s << Comma;

  csv << utl.replaceCrlf(rcd.otherEquip) << Comma;

  csv << utl.replaceCrlf(rcd.comments) << Comma;

  s = mbrEnt->lastName + _T(" - ") + rcd.callSign;  if (workAddr) s += _T(" - Wrk");

  csv << s << Comma;

  csv << vCrlf;    return true;
  }


bool GoogleRpt::addrAvail(EntRcd* rcd, AdrRcd*& addrRcd) {

  if (!rcd) return false;

  addrRcd = adrTbl.find(rcd->addrID);

  return addrRcd && (!addrRcd->address1.isEmpty() || rcd->addrIsPO);
  }


void GoogleRpt::putEntity(EntRcd* rcd, AdrRcd*& addrRcd) {
CtyRcd* cityRcd = ctyTbl.find(rcd->cityStID);
String        s;

  if (rcd->addrIsPO) {
    s.clear();
    if (!cityRcd->city.isEmpty())                                     s += cityRcd->city;
    if (!cityRcd->state.isEmpty())   {if (!s.isEmpty()) s += _T(" "); s += cityRcd->state;}
    if (!rcd->locationZip.isEmpty())
                                {if (!s.isEmpty()) s += _T(" "); s += expandZip(rcd->locationZip);}
    csv << s << Comma;
    }

  else {
    s.clear();
    if (addrRcd) s += addrRcd->address1;

    if (cityRcd) {
      s += cityRcd->city.isEmpty()  ? String(_T(", San Jose")) : _T(", ") + cityRcd->city;
      s += cityRcd->state.isEmpty() ? String(_T(" CA"))        : _T(" ")  + cityRcd->state;
      if (cityRcd->zip.isEmpty()) s += _T(" ")  + expandZip(cityRcd->zip);
      }
    csv << s << Comma;
    }

  s = expandPhone(rcd->phone2);   csv << s << Comma;
  s = expandPhone(rcd->phone1);   csv << s << Comma;
  }


///---------------

