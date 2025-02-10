// Contact List sorted by Name and Call Sign


#pragma once
#include "ReportBase.h"
#include "CurMbrList.h"


class ContactRpt : public ReportBase {

bool callSignSort;

public:

  ContactRpt(TCchar* path) : ReportBase(path), callSignSort(false) { }
 ~ContactRpt() { }

 void operator() (CurMbrSort sort);

private:

//  void output(  CurMbrData& item);
//  void setTabs( CurMbrList& list);
//  void setTabs2(CurMbrList& list);
//  void setTabs3(CurMbrList& list);
  void header();
  void output(CurMbrData* item);

  bool isCSsort() {return callSignSort;}

  ContactRpt() : ReportBase(0) { }
  };

