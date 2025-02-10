// Current Member List -- sorted by key


#pragma once
#include "ExpandableP.h"
#include "IterT.h"
#include "MemberList.h"

struct CurMbrData;


enum CurMbrSort {NilSort, MemberSort, CallSignSort, BadgeDateSort};


struct CurMbrData {
String key;
String firstName;
String lastName;
String badgeNumber;
String callSign;
bool   badgeOk;
String badgeExpDate;
String prmPhone;
String celPhone;
String prmText;
String secText;
String prmEmail;
String secEmail;
String employer;
String wrkPhone;
String wrkEmail;


  CurMbrData() : badgeOk(false) { }
  CurMbrData(CurMbrData& mi) {copy(mi);}

  CurMbrData& operator=  (CurMbrData& mi) {copy(mi); return *this;}

  bool get(MbrInfo& info);
  void setKey(CurMbrSort curMbrSort);

  bool isThirdLine();

  // Required for Insertion Sort, i.e. data = dtm;
  bool     operator>= (CurMbrData& mi) {return key >= mi.key;}
  bool     operator== (CurMbrData& mi) {return key == mi.key;}

  // Required for qsort, ==, >, <= and assignment (=)
  bool     operator>  (CurMbrData& mi) {return key >  mi.key;}
  bool     operator<= (CurMbrData& mi) {return key <= mi.key;}

private:

  String getDateKey();

  void copy(CurMbrData& mi);
  };


typedef DatumPtrT<CurMbrData, String> CurMbrDataP;              // Usually defined just before iterator
class CurMbrList;
typedef IterT<CurMbrList, CurMbrData> CMbrIter;



class CurMbrList {

ExpandableP<CurMbrData, String, CurMbrDataP, 2> data;

CurMbrSort sortTyp;
int        maxBgFirstName;
int        maxBgLastName;
int        maxFirstName;
int        maxLastName;
int        maxEmployer;
int        maxPrmEmail;

public:

  CurMbrList(CurMbrSort sort) : sortTyp(sort),   maxBgFirstName(0), maxBgLastName(0),
                                maxFirstName(0), maxLastName(0),    maxEmployer(0),
                                maxPrmEmail(0) {load(sort);}
 ~CurMbrList() { }

  CurMbrSort sort()       {return sortTyp;}
  int        maxFirst()   {return maxFirstName;}
  int        maxBgFirst() {return maxBgFirstName;}
  int        maxLast()    {return maxLastName;}
  int        maxBgLast()  {return maxBgLastName;}
  int        maxEmpl()    {return maxEmployer;}
  int        maxEmail()   {return maxPrmEmail;}
  int        maxName()    {return maxFirstName + maxLastName + 2;}

private:

  void load(CurMbrSort curMbrSort);

  // returns either a pointer to data (or datum) at index i in array or zero

  CurMbrData* datum(int i) {return 0 <= i && i < nData() ? data[i].p : 0;}

  int         nData()      {return data.end();}           // returns number of data items in array
                                                          // not necessarily private
  void        removeDatum(int i) {if (0 <= i && i < nData()) data.del(i);}

  friend typename CMbrIter;
  };

