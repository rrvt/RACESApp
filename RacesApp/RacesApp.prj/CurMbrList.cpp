// Current Member List -- sorted by key


#include "pch.h"
#include "CurMbrList.h"
#include "Database.h"
#include "MemberList.h"
#include "Utility.h"



void CurMbrList::load(CurMbrSort curMbrSort) {
MbrListIter iter(memberList);
MbrInfo*    info;

  for (info = iter(); info; info = iter++) {

    if (!info->curMbr) continue;

    CurMbrData curMbrData;

    if (!curMbrData.get(*info)) return;

    curMbrData.setKey(curMbrSort);

    setMax(curMbrData.firstName, maxFirstName);
    setMax(curMbrData.lastName,  maxLastName);
    setMax(curMbrData.employer,  maxEmployer);
    setMax(curMbrData.prmEmail,  maxPrmEmail);
    if (curMbrData.badgeOk) {
      setMax(curMbrData.firstName, maxBgFirstName);
      setMax(curMbrData.lastName,  maxBgLastName);
      }

    data = curMbrData;
    }

  }



bool CurMbrData::get(MbrInfo& info) {
MbrRcd& mbrRcd  = *info.mbrRcd;
EntRcd* mbrEnt  =  info.mbrEnt;        if (!mbrEnt) return false;
EntRcd* emplEnt =  info.emplEnt;

  lastName     = mbrEnt->lastName;      lastName.trim();
  firstName    = mbrEnt->firstName;     firstName.trim();

  callSign     = mbrRcd.callSign;       callSign.trim();
  badgeNumber  = mbrRcd.badgeNumber;    badgeNumber.trim();
  badgeOk      = mbrRcd.badgeOK;        badgeExpDate = mbrRcd.badgeExpDate;
  prmPhone     = mbrEnt->phone1;        celPhone     = mbrEnt->phone2;
  prmText      = mbrRcd.textMsgPh1;     secText      = mbrRcd.textMsgPh2;
  prmEmail     = mbrEnt->eMail;         secEmail     = mbrRcd.secondaryEmail;
  if (emplEnt) {
    employer   = emplEnt->firstName;    wrkPhone     = emplEnt->phone1;
    wrkEmail   = emplEnt->eMail;
    }

  return true;
  }


void CurMbrData::setKey(CurMbrSort curMbrSort) {
  key.clear();
  switch (curMbrSort) {
    case BadgeDateSort: key  = getDateKey();
    case CallSignSort : key += callSign;                          break;
    case MemberSort   : key  = lastName + firstName + callSign;   break;
    case SuffixSort   : key = getSuffixKey();                     break;
    case NilSort      :
    default           : break;
    }
  }



String CurMbrData::getDateKey() {
String yr;
String mn;
String dy;
String s;

  if (badgeExpDate.isEmpty()) return _T("000000");

  mn = badgeExpDate.substr(0, 2);
  dy = badgeExpDate.substr(2, 2);
  yr = badgeExpDate.substr(4);      if (yr.length() == 4) yr = yr.substr(2);

  return s = yr + mn + dy;
  }


String CurMbrData::getSuffixKey() {
String s = callSign;
int    pos = s.findOneOf(_T("0123456789"));
String letter;
String key;

  if (pos > 0) letter = s[pos+1];

  if      (letter < _T('L')) key = _T('0');
  else if (letter < _T('T')) key = _T('1');
  else                       key = _T('2');

  return key += callSign;
  }


void CurMbrData::copy(CurMbrData& mi) {
  key         = mi.key;
  firstName   = mi.firstName;   lastName     = mi.lastName;
  badgeNumber = mi.badgeNumber; callSign     = mi.callSign;
  badgeOk     = mi.badgeOk;     badgeExpDate = mi.badgeExpDate;
  prmPhone    = mi.prmPhone;    celPhone     = mi.celPhone;
  prmText     = mi.prmText;     secText      = mi.secText;
  prmEmail    = mi.prmEmail;    secEmail     = mi.secEmail;
  employer    = mi.employer;    wrkPhone     = mi.wrkPhone;
  wrkEmail    = mi.wrkEmail;
  }


bool CurMbrData::isThirdLine()
                      {return !employer.isEmpty() && (!wrkEmail.isEmpty() || !wrkPhone.isEmpty());}

