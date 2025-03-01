// Current Member Descriptor



#pragma once
#include "AdrTbl.h"
#include "CtyTbl.h"
#include "EntTbl.h"
#include "MbrInfo.h"
#include "MbrTbl.h"

struct MbrInfo;


class CurMbr {

int      nMod;
MbrInfo* info;
MbrRcd   nilRcd;
EntRcd   nilEnt;
String   ident;

public:

MbrRcd* rcd;                         // Local copies of pointers
EntRcd* mbr;
EntRcd* ice;
EntRcd* empl;

          CurMbr() : nMod(0), info(0), rcd(0), mbr(0), ice(0), empl(0) { }
         ~CurMbr() { }

  void    initialize() {nMod = 0; info = 0; ident.clear(); clear();}

  void    clear() {rcd = 0; mbr = 0; ice = 0; empl = 0;}

  bool    set(MbrInfo* info);

  bool    isEmpty() {return !info;}

  String& getIdent();

  void    rcdDirty()  {if (!rcd) return;  rcd->setDirty();   nMod++;}
  void    mbrDirty()  {if (info->mbrEnt)  setDirty(mbr);}
  void    iceDirty()  {if (info->iceEnt)  setDirty(ice);}
  void    emplDirty() {if (info->emplEnt) setDirty(empl);}

  void    setDirty(EntRcd* ent) {if (!ent)  return;    ent->setDirty();   nMod++;}

  AdrRcd* addAdrTbl(AdrRcd& rcd) {AdrRcd* r = adrTbl.add(rcd);   nMod++;   return r;}
  CtyRcd* addCtyTbl(CtyRcd& rcd) {CtyRcd* r = ctyTbl.add(rcd);   nMod++;   return r;}
  EntRcd* addEntTbl(EntRcd& rcd) {EntRcd* r = entTbl.add(rcd);   nMod++;   return r;}
  MbrRcd* addMbrTbl(MbrRcd& rcd) {MbrRcd* r = mbrTbl.add(rcd);   nMod++;   return r;}

  bool    removeMbr() {if (!rcd) return false;   rcd->setRemove();   nMod++;   return true;}

  bool    removeMbr(MbrRcd* rcd)
                      {if (!rcd) return false;   rcd->setRemove();   nMod++;   return true;}
  bool    removeEnt(EntRcd* rcd)
                      {if (!rcd) return false;   rcd->setRemove();   nMod++;   return true;}
  bool    removeAdr(AdrRcd* rcd)
                      {if (!rcd) return false;   rcd->setRemove();   nMod++;   return true;}
  bool    removeCty(CtyRcd* rcd)
                      {if (!rcd) return false;   rcd->setRemove();   nMod++;   return true;}

  bool    updateDB(TCchar* dbPath);

private:

  void    setDirty(AdrRcd* adr) {if (!adr)  return;    adr->setDirty();   nMod++;}
  void    setDirty(CtyRcd* cty) {if (!cty)  return;    cty->setDirty();   nMod++;}

  };


extern CurMbr curMbr;

