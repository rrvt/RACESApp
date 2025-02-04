// Dead Record Removal


#include "pch.h"
#include "DeadRcds.h"
#include "CurMbr.h"
#include "Database.h"


int DeadRcds::fix() {
int n = 0;

  csv << _T("Deleted Member Records") << vCrlf;
  n += removeDeadMemberRcds();
  csv << _T("Deleted Entity Records") << vCrlf;
  n += removeDeadEntityRcds();
  csv << _T("Deleted Address Records") << vCrlf;
  n += removeDeadAddrRcds();
  csv << _T("Deleted City/State Records") << vCrlf;
  n += removeDeadCityRcds();
  csv << _T("Deleted ") <<  n << _T(" records.") << vCrlf;

  return n;
  }


int DeadRcds::removeDeadMemberRcds() {
MbrIter iter(mbrTbl);
MbrRcd* rcd;
int     n = 0;

  for (rcd = iter(); rcd; rcd = iter++)
                  if (!rcd->mbrEntityID && rcd->callSign.isEmpty()) {curMbr.removeMbr(rcd);   n++;}
  return n;
  }


int DeadRcds::removeDeadEntityRcds() {
EntIter iter(entTbl);
EntRcd* rcd;
long    id;
String  dsp;
int     n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->getId();   dsp = rcd->firstName + _T(" ") + rcd->lastName;

    if (!entityRcdNeeded(id)) {
      csv << rcd->getId()   << Comma;
      csv << rcd->firstName << Comma;
      csv << rcd->lastName  << Comma;
      csv << vCrlf;    curMbr.removeEnt(rcd);   n++;
      }
    }

  return n;
  }


bool DeadRcds::entityRcdNeeded(long id) {
MbrIter iter(mbrTbl);
MbrRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) {
    if (rcd->isRemoved()) continue;
    if (rcd->mbrEntityID  == id) return true;
    if (rcd->emplEntityID == id) return true;
    if (rcd->iCE_EntityID == id) return true;
    }

  return false;
  }


int DeadRcds::removeDeadAddrRcds() {
AdrIter iter(adrTbl);
AdrRcd* rcd;
long    id;
String  dsp;
int     n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->getId();    dsp = rcd->address1;

    if (!addrRcdNeeded(id)) {
      csv << rcd->getId()  << Comma;
      csv << rcd->address1 << Comma;
      csv << rcd->address2 << Comma;
      csv << vCrlf;    curMbr.removeAdr(rcd);   n++;
      }
      }

  return n;
  }



bool DeadRcds::addrRcdNeeded(long id) {
EntIter    iter(entTbl);
EntRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (!rcd->isRemoved() && rcd->addrID  == id) return true;

  return false;
  }


int DeadRcds::removeDeadCityRcds() {
CtyIter iter(ctyTbl);
CtyRcd* rcd;
long    id;
String  dsp;
int     n = 0;

  for (rcd = iter(); rcd; rcd = iter++) {

    id = rcd->getId();   dsp = rcd->city + _T(", ") + rcd->state + _T(" ") + rcd->zip;

    if (!cityRcdNeeded(id)) {
      csv << rcd->getId() << Comma;
      csv << rcd->city  << Comma;
      csv << rcd->state << Comma;
      csv << rcd->zip   << Comma;
      csv << vCrlf;    curMbr.removeCty(rcd);   n++;
      }
    }

  return n;
  }



bool DeadRcds::cityRcdNeeded(long id) {
EntIter    iter(entTbl);
EntRcd* rcd;

  for (rcd = iter(); rcd; rcd = iter++) if (!rcd->isRemoved() && rcd->cityStID  == id) return true;

  return false;
  }




