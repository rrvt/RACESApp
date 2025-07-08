// Member Info -- Used in reports


#include "pch.h"
#include "MbrInfo.h"
#include "AsnTbl.h"
#include "EntTbl.h"
#include "Database.h"
#include "LocTbl.h"
#include "MbrSearch.h"
#include "Resource.h"
#include "StsTbl.h"

#include "MessageBox.h"


bool MbrInfo::set(MbrRcd* rcd) {

  mbrEnt  = entTbl.find(rcd->mbrEntityID);   if (!mbrEnt) return false;
  mbrRcd  = rcd;
  emplEnt = entTbl.find(rcd->emplEntityID);
  iceEnt  = entTbl.find(rcd->iCE_EntityID);
  asnRcd  = asnTbl.find(rcd->assgnPrefID);
  locRcd  = locTbl.find(rcd->locationPrefID);
  stsRcd  = stsTbl.find(rcd->statusID);

  key     = mbrEnt->lastName + mbrEnt->firstName + mbrEnt->middleInitial + rcd->callSign;
  curMbr  = stsRcd && stsRcd->abbreviation != _T("Fmr") ? true : false;

  return true;
  }


void MbrInfo::copy(MbrInfo& mi) {
  key         = mi.key;           mbrRcd   = mi.mbrRcd;
  mbrEnt      = mi.mbrEnt;        emplEnt  = mi.emplEnt;
  iceEnt      = mi.iceEnt;        asnRcd   = mi.asnRcd;
  locRcd      = mi.locRcd;        stsRcd   = mi.stsRcd;
  }


int fldList[] = {IDC_MbrFirstName,        IDC_MbrLastName,        IDC_MbrCallsign,
                 IDC_MbrStreetAdr,        IDC_MbrCity,            IDC_MbrState,
                 IDC_MbrZip,              IDC_MbrCellPh,          IDC_MbrLandline,
                 IDC_MbrHomeZip,          IDC_MbrEmail,           IDC_ICEFirstName,
                 IDC_ICELastName,         IDC_ICEeMail,           IDC_ICEStreetAdr,
                 IDC_ICECity,             IDC_ICEZip,             IDC_ICECellPh,
                 IDC_ICELandline,         IDC_EmplName,           IDC_EmplEmail,
                 IDC_EmplStreetAdr,       IDC_EmplCity,           IDC_EmplZip,
                 IDC_EmplCellPh,          IDC_EmplLandline,       IDC_EmplCompanyZip,
                 IDC_HandHeld,            IDC_PortMobile,         IDC_PortPacket,
                 IDC_OtherEquip,          IDC_Multilingual,       IDC_OtherCapabilities,
                 IDC_Limitations,         IDC_Comments,           IDC_SkillCerts,
                 IDC_EOCCert
                 };


bool MbrInfo::find(MbrSearch* srch, TCchar* tgt, int curFld, int& field) {
int i;

  if (curFld) return findInOneFld(srch, tgt, curFld);

  for (i = 0; i < noElements(fldList); i++)
                           {field = fldList[i];   if (findInOneFld(srch, tgt, field)) return true;}
  field = 0;   return false;
  }


bool MbrInfo::findInOneFld(MbrSearch* srch, TCchar* tgt, int curFld) {

  switch (curFld) {
    case IDC_MbrFirstName     : if (cmpMbrFirstName(srch, tgt))      return true; break;
    case IDC_MbrLastName      : if (cmpMbrLastName(srch, tgt))       return true; break;
    case IDC_MbrCallsign      : if (cmpCallSign(srch, tgt))          return true; break;
    case IDC_MbrStreetAdr     : if (cmpMbrStreetAdr(srch, tgt))      return true; break;
    case IDC_MbrCity          : if (cmpMbrCity(srch, tgt))           return true; break;
    case IDC_MbrState         : if (cmpMbrState(srch, tgt))          return true; break;
    case IDC_MbrZip           : if (cmpMbrZip(srch, tgt))            return true; break;
    case IDC_MbrCellPh        : if (cmpCellPh(srch, tgt))            return true; break;
    case IDC_MbrLandline      : if (cmpMbrLandline(srch, tgt))       return true; break;
    case IDC_MbrHomeZip       : if (cmpMbrHomeZip(srch, tgt))        return true; break;
    case IDC_MbrEmail         : if (cmpMbrEmail(srch, tgt))          return true; break;
    case IDC_ICEFirstName     : if (cmpICEFirstName(srch, tgt))      return true; break;
    case IDC_ICELastName      : if (cmpICELastName(srch, tgt))       return true; break;
    case IDC_ICEeMail         : if (cmpICEeMail(srch, tgt))          return true; break;
    case IDC_ICEStreetAdr     : if (cmpICEStreetAdr(srch, tgt))      return true; break;
    case IDC_ICECity          : if (cmpICECity(srch, tgt))           return true; break;
    case IDC_ICEZip           : if (cmpICEZip(srch, tgt))            return true; break;
    case IDC_ICECellPh        : if (cmpICECellPh(srch, tgt))         return true; break;
    case IDC_ICELandline      : if (cmpICELandline(srch, tgt))       return true; break;
    case IDC_EmplName         : if (cmpEmplName(srch, tgt))          return true; break;
    case IDC_EmplEmail        : if (cmpEmplEmail(srch, tgt))         return true; break;
    case IDC_EmplStreetAdr    : if (cmpEmplStreetAdr(srch, tgt))     return true; break;
    case IDC_EmplCity         : if (cmpEmplCity(srch, tgt))          return true; break;
    case IDC_EmplZip          : if (cmpEmplZip(srch, tgt))           return true; break;
    case IDC_EmplCellPh       : if (cmpEmplCellPh(srch, tgt))        return true; break;
    case IDC_EmplLandline     : if (cmpEmplLandline(srch, tgt))      return true; break;
    case IDC_EmplCompanyZip   : if (cmpEmplCompanyZip(srch, tgt))    return true; break;
    case IDC_HandHeld         : if (cmpHandHeld(srch, tgt))          return true; break;
    case IDC_PortMobile       : if (cmpPortMobile(srch, tgt))        return true; break;
    case IDC_PortPacket       : if (cmpPortPacket(srch, tgt))        return true; break;
    case IDC_OtherEquip       : if (cmpOtherEquip(srch, tgt))        return true; break;
    case IDC_Multilingual     : if (cmpMultilingual(srch, tgt))      return true; break;
    case IDC_OtherCapabilities: if (cmpOtherCapabilities(srch, tgt)) return true; break;
    case IDC_Limitations      : if (cmpLimitations(srch, tgt))       return true; break;
    case IDC_Comments         : if (cmpComments(srch, tgt))          return true; break;
    case IDC_SkillCerts       : if (cmpSkillCerts(srch, tgt))        return true; break;
    case IDC_EOCCert          : if (cmpEOCCert(srch, tgt))           return true; break;
    }

  return false;
  }


bool MbrInfo::cmpMbrFirstName(MbrSearch* srch, TCchar* tgt)
                                          {return mbrEnt && srch->compare(mbrEnt->firstName, tgt);}

bool MbrInfo::cmpMbrLastName(MbrSearch* srch, TCchar* tgt)
                                          {return mbrEnt && srch->compare(mbrEnt->lastName,  tgt);}

bool MbrInfo::cmpCallSign(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->callSign,  tgt);}

bool MbrInfo::cmpMbrStreetAdr(MbrSearch* srch, TCchar* tgt)
                                          {return mbrEnt && cmpStreetAdr(mbrEnt, srch, tgt);}

bool MbrInfo::cmpMbrCity(MbrSearch* srch, TCchar* tgt) {return cmpCity(mbrEnt, srch, tgt);}

bool MbrInfo::cmpMbrState(MbrSearch* srch, TCchar* tgt) {
CtyRcd* ctyRcd = mbrEnt ? ctyTbl.find(mbrEnt->cityStID) : 0;

  return ctyRcd && srch->compare(ctyRcd->state, tgt);
  }

bool MbrInfo::cmpMbrZip(MbrSearch* srch, TCchar* tgt)  {return cmpZip(mbrEnt, srch, tgt);}

bool MbrInfo::cmpCellPh(MbrSearch* srch, TCchar* tgt)
                                          {return mbrEnt && srch->compare(mbrEnt->phone2, tgt);}

bool MbrInfo::cmpMbrLandline(MbrSearch* srch, TCchar* tgt)
                                          {return mbrEnt && srch->compare(mbrEnt->phone1, tgt);}

bool MbrInfo::cmpMbrHomeZip(MbrSearch* srch, TCchar* tgt)
                                          {return mbrEnt && srch->compare(mbrEnt->locationZip, tgt);}

bool MbrInfo::cmpMbrEmail(MbrSearch* srch, TCchar* tgt)
                                          {return mbrEnt && srch->compare(mbrEnt->eMail, tgt);}

bool MbrInfo::cmpICEFirstName(MbrSearch* srch, TCchar* tgt)
                                          {return iceEnt && srch->compare(iceEnt->firstName, tgt);}

bool MbrInfo::cmpICELastName(MbrSearch* srch, TCchar* tgt)
                                          {return iceEnt && srch->compare(iceEnt->lastName, tgt);}

bool MbrInfo::cmpICEeMail(MbrSearch* srch, TCchar* tgt)
                                          {return iceEnt && srch->compare(iceEnt->eMail, tgt);}

bool MbrInfo::cmpICEStreetAdr(MbrSearch* srch, TCchar* tgt)
                                          {return cmpStreetAdr(iceEnt, srch, tgt);}

bool MbrInfo::cmpICECity(MbrSearch* srch, TCchar* tgt) {return cmpCity(iceEnt, srch, tgt);}

bool MbrInfo::cmpICEZip(MbrSearch* srch, TCchar* tgt) {return cmpZip(iceEnt, srch, tgt);}

bool MbrInfo::cmpICECellPh(MbrSearch* srch, TCchar* tgt)
                                          {return iceEnt && srch->compare(iceEnt->phone2, tgt);}

bool MbrInfo::cmpICELandline(MbrSearch* srch, TCchar* tgt)
                                          {return iceEnt && srch->compare(iceEnt->phone1, tgt);}

bool MbrInfo::cmpEmplName(MbrSearch* srch, TCchar* tgt)
                                          {return emplEnt && srch->compare(emplEnt->firstName, tgt);}

bool MbrInfo::cmpEmplEmail(MbrSearch* srch, TCchar* tgt)
                                          {return emplEnt && srch->compare(emplEnt->eMail, tgt);}

bool MbrInfo::cmpEmplStreetAdr(MbrSearch* srch, TCchar* tgt)
                                          {return cmpStreetAdr(emplEnt, srch, tgt);}

bool MbrInfo::cmpEmplCity(MbrSearch* srch, TCchar* tgt) {return cmpCity(emplEnt, srch, tgt);}

bool MbrInfo::cmpEmplZip(MbrSearch* srch, TCchar* tgt)  {return cmpZip(emplEnt, srch, tgt);}

bool MbrInfo::cmpEmplCellPh(MbrSearch* srch, TCchar* tgt)
                                          {return emplEnt && srch->compare(emplEnt->phone2, tgt);}

bool MbrInfo::cmpEmplLandline(MbrSearch* srch, TCchar* tgt)
                                          {return emplEnt && srch->compare(emplEnt->phone1, tgt);}

bool MbrInfo::cmpEmplCompanyZip(MbrSearch* srch, TCchar* tgt)
                                          {return emplEnt && srch->compare(emplEnt->locationZip, tgt);}

bool MbrInfo::cmpHandHeld(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->handHeld, tgt);}

bool MbrInfo::cmpPortMobile(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->portMobile, tgt);}

bool MbrInfo::cmpPortPacket(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->portPacket, tgt);}

bool MbrInfo::cmpOtherEquip(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->otherEquip, tgt);}

bool MbrInfo::cmpMultilingual(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->multilingual, tgt);}

bool MbrInfo::cmpOtherCapabilities(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->otherCapabilities, tgt);}

bool MbrInfo::cmpLimitations(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->limitations, tgt);}

bool MbrInfo::cmpComments(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->comments, tgt);}

bool MbrInfo::cmpSkillCerts(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->skillCertifications, tgt);}

bool MbrInfo::cmpEOCCert(MbrSearch* srch, TCchar* tgt)
                                          {return srch->compare(mbrRcd->eOC_Certifications, tgt);}


bool MbrInfo::cmpStreetAdr(EntRcd* ent, MbrSearch* srch, TCchar* tgt) {
AdrRcd* adrRcd = ent ? adrTbl.find(ent->addrID) : 0;

  return adrRcd && srch->compare(adrRcd->address1, tgt);
  }


bool MbrInfo::cmpCity(EntRcd* ent, MbrSearch* srch, TCchar* tgt) {
CtyRcd* ctyRcd = ent ? ctyTbl.find(ent->cityStID) : 0;

  return ctyRcd && srch->compare(ctyRcd->city, tgt);
  }


bool MbrInfo::cmpZip(EntRcd* ent, MbrSearch* srch, TCchar* tgt) {
CtyRcd* ctyRcd = ent ? ctyTbl.find(ent->cityStID) : 0;

  return ctyRcd && srch->compare(ctyRcd->zip, tgt);
  }




//// ------------------------

