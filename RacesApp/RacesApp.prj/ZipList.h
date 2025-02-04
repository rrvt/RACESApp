// Zip code list, sorted


#pragma once
#include "CtyTbl.h"


class ZipDtm {

CtyRcd* rcd;

public:

String zip;

  ZipDtm() : rcd(0) { }
 ~ZipDtm() { }


  void add(CtyRcd* ctyRcd) {rcd = ctyRcd;   zip = ctyRcd->zip;}

  CtyRcd* operator() () {return rcd;}

  bool operator>= (ZipDtm& d)  {return zip >= d.zip;}
  bool operator== (String key) {return zip == key;}
  bool operator>  (String key) {return zip >  key;}
  bool operator<  (String key) {return zip <  key;}
  };


class ZipList;
typedef DatumPtrT<ZipDtm, String> ZipDtmP;
typedef IterT<ZipList, ZipDtm>    ZipIter;


class ZipList {

ExpandableP<ZipDtm, String, ZipDtmP, 2> data;

public:

          ZipList() { }
         ~ZipList() { }

  void    load();

  int     add(CEdit& cityCtl, CEdit& stateCtl, CEdit& zipCtl);

  CtyRcd* add(CtyRcd* ctyRcd);

  CtyRcd* find(TCchar* tc);

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  ZipDtm* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int    nData()      {return data.end();}                // returns number of data items in array
                                                          // not necessarily private
  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename ZipIter;
  };


extern ZipList zipList;
