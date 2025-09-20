// Current Members Prioritized


#pragma once
#include "ExpandableP.h"
#include "IterT.h"

struct MbrInfo;
class  AsnRcd;


class PLDsc {
public:
String   key;
MbrInfo* info;

  PLDsc() : info(0) {}
 ~PLDsc() { }


  // Needed for Insertion Sort of Primary Key
  bool operator== (PLDsc& r) {return key == r.key;}
  bool operator>= (PLDsc& r) {return key >= r.key;}
  };


class PriorityList;
typedef DatumPtrT<PLDsc, String>   PLDscP;
typedef IterT<PriorityList, PLDsc> PLIter;


class PriorityList {

ExpandableP<PLDsc, String, PLDscP, 2> data;

public:

  PriorityList();
 ~PriorityList() { }

private:

  int getPriority(AsnRcd* asnRcd);

  // returns either a pointer to data (or datum) at index i in array or zero

  PLDsc* datum(int i) {return 0 <= i && i < nData() ? data[i] : 0;}

  int   nData()      {return data.end();}                  // returns number of data items in array

  void  removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename PLIter;
  };

