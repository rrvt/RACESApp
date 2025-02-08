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

  bool     get(MbrRcd* rcd);

  // Required for Insertion Sort, i.e. data = dtm;
  bool     operator>= (MbrInfo& mi) {return key >= mi.key;}
  bool     operator== (MbrInfo& mi) {return key == mi.key;}

  // Required for qsort, ==, >, <= and assignment (=)
  bool     operator>  (MbrInfo& mi) {return key >  mi.key;}
  bool     operator<= (MbrInfo& mi) {return key <= mi.key;}

private:

  void copy(MbrInfo& mi);
  };


typedef DatumPtrT<MbrInfo, String> MbrInfoP;              // Usually defined just before iterator
class InfoRpts;
typedef IterT<InfoRpts, MbrInfo> InfoIter;


#if 0
class InfoRpts {

ExpandableP<MbrInfo, String, MbrInfoP, 2> data;

public:

  InfoRpts() { }
 ~InfoRpts() { }

  void info();
  void dspBadges(BadgeSort badgeSort);
  void former(FmrSort key);

private:

  String getDateKey(String& d);
  String decodeDate(String& d);

  // returns either a pointer to data (or datum) at index i in array or zero

  MbrInfo* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int   nData()      {return data.end();}                  // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename InfoIter;
  };

#endif
