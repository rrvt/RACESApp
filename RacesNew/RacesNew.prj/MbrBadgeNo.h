// Member Badge No


#pragma once
#include "expandable.h"
#include "IterT.h"


struct BdgNo {
int n;

       BdgNo() : n(0) { }
       BdgNo(BdgNo& b) {n = b.n;}

  bool operator>= (BdgNo& bdgNo) {return n >= bdgNo.n;}
  bool operator== (BdgNo& bdgNo) {return n == bdgNo.n;}

  bool operator== (int key) {return n == key;}
  bool operator>  (int key) {return n  > key;}
  bool operator<  (int key) {return n  < key;}

  BdgNo& operator= (BdgNo& bdgNo) {n = bdgNo.n;   return *this;}
  };


class MbrBadgeNo;
typedef IterT<MbrBadgeNo, BdgNo> MbnIter;


class MbrBadgeNo {

int lastBadgeNo;

Expandable<BdgNo, 2> data;

public:

  MbrBadgeNo() { }
 ~MbrBadgeNo() { }

  int    findNext();

private:

  void add(int n) {BdgNo bdgNo;   bdgNo.n = n;   data = bdgNo;}

  // returns either a pointer to datum at index i in array or zero

  BdgNo* datum(int i) {return 0 <= i && i < nData() ? &data[i] : 0;}

  int    nData()      {return data.end();}                // Returns number of data items in array,
                                                          // not necessarily private
  void   removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename MbnIter;
  };

