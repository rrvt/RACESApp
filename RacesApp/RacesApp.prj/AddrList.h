// Address List, sorted


#pragma once
#include "AdrTbl.h"


class AdrDtm {

String  key;
AdrRcd* rcd;

public:


  AdrDtm() : rcd(0) { }
 ~AdrDtm() { }

  String& add(AdrRcd* adrRcd);               // Returns key

  void    add(CComboBox& ctl);

  AdrRcd* operator() ()      {return rcd;}
  String& getKey()           {return key;}
  bool    inKey(TCchar* tgt) {return key.find(tgt) >= 0;}

  bool operator>= (AdrDtm& d)   {return       key >= d.key;}
  bool operator== (String& key) {return this->key == key;}
  bool operator>  (String& key) {return this->key >  key;}
  bool operator<  (String& key) {return this->key <  key;}
  };


class AddrList;
typedef DatumPtrT<AdrDtm, String> AddrDtmP;
typedef IterT<AddrList, AdrDtm>   AddrIter;


class AddrList {

ExpandableP<AdrDtm, String, AddrDtmP, 2> data;

int    index;
AdrRcd nilRcd;

public:
          AddrList() : index(-1) { }
         ~AddrList() { }

  void    load();

  int     add(CComboBox& streetCtl, CEdit& unitCtl);

  AdrRcd* add(AdrRcd* adrRcd);

  void    load(CComboBox& ctl, CEdit& unitCtl, String& addr1, String& addr2);
  void    load(CComboBox& ctl);

  void    getSel(CComboBox& ctl);
  void    set(CComboBox& ctl, CEdit& unitCtl);

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  AdrDtm* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int    nData()      {return data.end();}                // returns number of data items in array
                                                          // not necessarily private
  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename AddrIter;
  };


extern AddrList addrList;

