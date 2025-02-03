// Address List, sorted


#pragma once
#include "AdrTbl.h"


class AdrDtm {

AdrRcd* rcd;

public:

String addr;

  AdrDtm() : rcd(0) { }
 ~AdrDtm() { }

  void add(AdrRcd* adrRcd) {rcd = adrRcd;   addr = adrRcd->address1;}

  AdrRcd* operator() () {return rcd;}

  bool operator>= (AdrDtm& d)  {return addr >= d.addr;}
  bool operator== (String key) {return addr == key;}
  bool operator>  (String key) {return addr >  key;}
  bool operator<  (String key) {return addr <  key;}
  };


class AddrList;
typedef DatumPtrT<AdrDtm, String> AddrDtmP;
typedef IterT<AddrList, AdrDtm>   AddrIter;


class AddrList {

ExpandableP<AdrDtm, String, AddrDtmP, 2> data;

public:
          AddrList() { }
         ~AddrList() { }

  void    load();

  int     add(CEdit& streetCtl, CEdit& unitCtl);

  AdrRcd* add(AdrRcd* adrRcd);

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  AdrDtm* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int    nData()      {return data.end();}                // returns number of data items in array
                                                          // not necessarily private
  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename AddrIter;
  };


extern AddrList addrList;

