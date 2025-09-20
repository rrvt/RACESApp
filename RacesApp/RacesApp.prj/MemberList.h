// List of Members suitable for sorting

#pragma once
#include "ExpandableP.h"
#include "IterT.h"
#include "MbrInfo.h"


class AsnRcd;


typedef DatumPtrT<MbrInfo, String> MbrInfoP;


class MemberList;
typedef IterT<MemberList, MbrInfo> MbrListIter;


class MemberList {

ExpandableP<MbrInfo, String, MbrInfoP, 2> data;

public:

           MemberList() { }
          ~MemberList() { }

  bool     isEmpty() {return nData() == 0;}

  void     create();

  MbrInfo* add(MbrRcd* mbrRcd);

private:

  // returns either a pointer to data (or datum) at index i in array or zero

  MbrInfo* datum(int i) {return 0 <= i && i < nData() ? data[i] : 0;}

  int      nData()      {return data.end();}                  // returns number of data items in array

  void     removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename MbrListIter;
  };


extern MemberList memberList;
