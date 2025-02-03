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
  if (!rcd || !ent) {ident.clear();  return ident;}

  return ident = ent->firstName + _T(' ') + ent->lastName + _T(", ") + rcd->callSign;
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

