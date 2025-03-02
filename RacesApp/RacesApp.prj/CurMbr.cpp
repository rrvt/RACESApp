// Current Member Descriptor


#include "pch.h"
#include "CurMbr.h"
#include "MessageBox.h"


CurMbr curMbr;


bool CurMbr::set(MbrInfo* info) {

  if (!info) return false;

  this->info = info;
  rcd        = info->mbrRcd  ? info->mbrRcd  : &nilRcd;
  mbr        = info->mbrEnt  ? info->mbrEnt  : &nilEnt;
  ice        = info->iceEnt  ? info->iceEnt  : &nilEnt;
  empl       = info->emplEnt ? info->emplEnt : &nilEnt;

  return true;
  }


String& CurMbr::getIdent() {

  ident.clear();

  if (!rcd || !mbr) return ident;
                                                    ident  = mbr->firstName;
  if (!ident.isEmpty() && !mbr->lastName.isEmpty()) ident += _T(' ');
  if (!mbr->lastName.isEmpty())                     ident += mbr->lastName;

  if (!ident.isEmpty() && !rcd->callSign.isEmpty()) ident += _T(", ");
  if (!rcd->callSign.isEmpty())                     ident += rcd->callSign;

  return ident;
  }


bool CurMbr::updateDB(TCchar* dbPath) {

  if (update && msgYesNoBox(_T("Update database?")) == IDYES) {

    if (!ctyTbl.store(dbPath)) return false;
    if (!adrTbl.store(dbPath)) return false;
    if (!entTbl.store(dbPath)) return false;
    if (!mbrTbl.store(dbPath)) return false;
    }

  return true;
  }

