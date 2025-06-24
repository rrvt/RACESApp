// Zip code list, sorted


#pragma once
#include "CtyTbl.h"


class ZipDtm {

String  key;
CtyRcd* rcd;

public:


  ZipDtm() : rcd(0) { }
 ~ZipDtm() { }

  String& add(CtyRcd* ctyRcd) {rcd = ctyRcd;   key = ctyRcd->zip;   return key;}

  void    add(CComboBox& ctl);

  CtyRcd* operator() () {return rcd;}
  String& getKey()            {return key;}
  bool    inKey(TCchar* tgt)  {return key.find(tgt) >= 0;}

  bool operator>= (ZipDtm&   d) {return       key >= d.key;}
  bool operator== (String& key) {return this->key == key;}
  bool operator>  (String& key) {return this->key >  key;}
  bool operator<  (String& key) {return this->key <  key;}
  };


class ZipList;
typedef DatumPtrT<ZipDtm, String> ZipDtmP;
typedef IterT<ZipList, ZipDtm>    ZipIter;


class ZipList {

ExpandableP<ZipDtm, String, ZipDtmP, 2> data;
CtyRcd nilRcd;

public:

          ZipList() { }
         ~ZipList() { }

  void    load();

  int     add(CComboBox& zipCtl, CEdit& cityCtl, CEdit& stateCtl);

  CtyRcd* add(CtyRcd* ctyRcd);

  void    load(CComboBox& ctl, TCchar* tc);
  void    load(CComboBox& ctl);
  void    set(CComboBox& ctl, CEdit& cityCtl, CEdit& stateCtl);

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  ZipDtm* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int    nData()      {return data.end();}                // returns number of data items in array
                                                          // not necessarily private
  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename ZipIter;
  };


extern ZipList zipList;



///////------------------

//  int     add(CEdit& cityCtl, CEdit& stateCtl, CEdit& zipCtl);

