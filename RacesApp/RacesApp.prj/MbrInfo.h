// Member Info -- Used in reports


#pragma once
#include "ExpandableP.h"
#include "IterT.h"

class AsnRcd;
class EntRcd;
class LocRcd;
class MbrRcd;
class StsRcd;
class MbrSearch;


struct MbrInfo {
String  key;
bool    curMbr;                       // Current Member, i.e. status != "Fmr"
MbrRcd* mbrRcd;
EntRcd* mbrEnt;
EntRcd* emplEnt;
EntRcd* iceEnt;
AsnRcd* asnRcd;
LocRcd* locRcd;
StsRcd* stsRcd;

  MbrInfo() : mbrRcd(0) { }
  MbrInfo(MbrInfo& mi) {copy(mi);}

  MbrInfo& operator=  (MbrInfo& mi) {copy(mi); return *this;}

  bool     set(MbrRcd* rcd);
  bool     find(MbrSearch* srch, TCchar* tgt, int curFld, int& field);    // returns field ID
  bool     findInOneFld(MbrSearch* srch, TCchar* tgt, int curFld);

  // Required for Insertion Sort, i.e. data = dtm;
  bool     operator>= (MbrInfo& mi) {return key >= mi.key;}
  bool     operator== (MbrInfo& mi) {return key == mi.key;}

  // Required for qsort, ==, >, <= and assignment (=)
  bool     operator>  (MbrInfo& mi) {return key >  mi.key;}
  bool     operator<= (MbrInfo& mi) {return key <= mi.key;}

private:

  bool cmpMbrFirstName(     MbrSearch* srch, TCchar* tgt);
  bool cmpMbrLastName(      MbrSearch* srch, TCchar* tgt);
  bool cmpCallSign(         MbrSearch* srch, TCchar* tgt);
  bool cmpMbrStreetAdr(     MbrSearch* srch, TCchar* tgt);
  bool cmpMbrCity(          MbrSearch* srch, TCchar* tgt);
  bool cmpMbrState(         MbrSearch* srch, TCchar* tgt);
  bool cmpMbrZip(           MbrSearch* srch, TCchar* tgt);
  bool cmpCellPh(           MbrSearch* srch, TCchar* tgt);
  bool cmpMbrLandline(      MbrSearch* srch, TCchar* tgt);
  bool cmpMbrHomeZip(       MbrSearch* srch, TCchar* tgt);
  bool cmpMbrEmail(         MbrSearch* srch, TCchar* tgt);
  bool cmpICEFirstName(     MbrSearch* srch, TCchar* tgt);
  bool cmpICELastName(      MbrSearch* srch, TCchar* tgt);
  bool cmpICEeMail(         MbrSearch* srch, TCchar* tgt);
  bool cmpICEStreetAdr(     MbrSearch* srch, TCchar* tgt);
  bool cmpICECity(          MbrSearch* srch, TCchar* tgt);
  bool cmpICEZip(           MbrSearch* srch, TCchar* tgt);
  bool cmpICECellPh(        MbrSearch* srch, TCchar* tgt);
  bool cmpICELandline(      MbrSearch* srch, TCchar* tgt);
  bool cmpEmplName(         MbrSearch* srch, TCchar* tgt);
  bool cmpEmplEmail(        MbrSearch* srch, TCchar* tgt);
  bool cmpEmplStreetAdr(    MbrSearch* srch, TCchar* tgt);
  bool cmpEmplCity(         MbrSearch* srch, TCchar* tgt);
  bool cmpEmplZip(          MbrSearch* srch, TCchar* tgt);
  bool cmpEmplCellPh(       MbrSearch* srch, TCchar* tgt);
  bool cmpEmplLandline(     MbrSearch* srch, TCchar* tgt);
  bool cmpEmplCompanyZip(   MbrSearch* srch, TCchar* tgt);
  bool cmpHandHeld(         MbrSearch* srch, TCchar* tgt);
  bool cmpPortMobile(       MbrSearch* srch, TCchar* tgt);
  bool cmpPortPacket(       MbrSearch* srch, TCchar* tgt);
  bool cmpOtherEquip(       MbrSearch* srch, TCchar* tgt);
  bool cmpMultilingual(     MbrSearch* srch, TCchar* tgt);
  bool cmpOtherCapabilities(MbrSearch* srch, TCchar* tgt);
  bool cmpLimitations(      MbrSearch* srch, TCchar* tgt);
  bool cmpComments(         MbrSearch* srch, TCchar* tgt);
  bool cmpSkillCerts(       MbrSearch* srch, TCchar* tgt);
  bool cmpEOCCert(          MbrSearch* srch, TCchar* tgt);

  bool cmpStreetAdr(EntRcd* ent, MbrSearch* srch, TCchar* tgt);
  bool cmpCity(     EntRcd* ent, MbrSearch* srch, TCchar* tgt);
  bool cmpZip(      EntRcd* ent, MbrSearch* srch, TCchar* tgt);

  void copy(MbrInfo& mi);
  };




