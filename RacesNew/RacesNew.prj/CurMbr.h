// Current Member Descriptor



#pragma once
#include "AdrTbl.h"
#include "CtyTbl.h"
#include "EntTbl.h"
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
EntRcd* ent;
EntRcd* ice;
EntRcd* empl;

          CurMbr() : nMod(0), info(0), rcd(0), ent(0), ice(0), empl(0) { }
         ~CurMbr() { }

  void    clear() {rcd = 0; ent = 0; ice = 0; empl = 0;}

  bool    set(void* info);

  String& getIdent();

  void    rcdDirty()  {if (!rcd)  return;    rcd->setDirty();   nMod++;}
  void    entDirty()  {setDirty(ent);}
  void    iceDirty()  {setDirty(ice);}
  void    emplDirty() {setDirty(empl);}

  void    setDirty(EntRcd* ent) {if (!ent)  return;    ent->setDirty();   nMod++;}
  void    setDirty(AdrRcd* adr) {if (!adr)  return;    adr->setDirty();   nMod++;}
  void    setDirty(CtyRcd* cty) {if (!cty)  return;    cty->setDirty();   nMod++;}

  AdrRcd* addAdrTbl(AdrRcd& rcd) {return adrTbl.add(rcd);   nMod++;}
  CtyRcd* addCtyTbl(CtyRcd& rcd) {return ctyTbl.add(rcd);   nMod++;}
  EntRcd* addEntTbl(EntRcd& rcd) {return entTbl.add(rcd);   nMod++;}
  MbrRcd* addMbrTbl(MbrRcd& rcd) {return mbrTbl.add(rcd);   nMod++;}

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
  };


extern CurMbr curMbr;

