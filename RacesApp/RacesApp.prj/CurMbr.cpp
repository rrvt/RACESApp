// Current Member Descriptor


#include "pch.h"
#include "CurMbr.h"
#include "MbrInfo.h"
#include "MessageBox.h"


CurMbr curMbr;


bool CurMbr::set(void* info) {
MbrInfo* ptr = (MbrInfo*) info;

  if (!ptr) return false;

  this->info = ptr;
  rcd      = ptr->mbrRcd  ? ptr->mbrRcd  : &nilRcd;
  ent      = ptr->mbrEnt  ? ptr->mbrEnt  : &nilEnt;
  ice      = ptr->iceEnt  ? ptr->iceEnt  : &nilEnt;
  empl     = ptr->emplEnt ? ptr->emplEnt : &nilEnt;

  return true;
  }


String& CurMbr::getIdent() {

  ident.clear();

  if (!rcd || !ent) return ident;
                                                    ident  = ent->firstName;
  if (!ident.isEmpty() && !ent->lastName.isEmpty()) ident += _T(' ');
  if (!ent->lastName.isEmpty())                     ident += ent->lastName;

  if (!ident.isEmpty() && !rcd->callSign.isEmpty()) ident += _T(", ");
  if (!rcd->callSign.isEmpty())                     ident += rcd->callSign;

  return ident;
  }


bool CurMbr::updateDB(TCchar* dbPath) {

  if (nMod && msgYesNoBox(_T("Update database?")) == IDYES) {

    if (!ctyTbl.store(dbPath)) return false;
    if (!adrTbl.store(dbPath)) return false;
    if (!entTbl.store(dbPath)) return false;
    if (!mbrTbl.store(dbPath)) return false;
    }

  return true;
  }

