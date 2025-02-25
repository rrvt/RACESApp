// Member Info -- Used in reports


#pragma once
#include "ExpandableP.h"
#include "IterT.h"

class AsnRcd;
class EntRcd;
class LocRcd;
class MbrRcd;
class StsRcd;


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

  // Required for Insertion Sort, i.e. data = dtm;
  bool     operator>= (MbrInfo& mi) {return key >= mi.key;}
  bool     operator== (MbrInfo& mi) {return key == mi.key;}

  // Required for qsort, ==, >, <= and assignment (=)
  bool     operator>  (MbrInfo& mi) {return key >  mi.key;}
  bool     operator<= (MbrInfo& mi) {return key <= mi.key;}

private:

  void copy(MbrInfo& mi);
  };




