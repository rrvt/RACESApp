// Member IDs, i.e. Call Signs alone and Call Signs, Names, etc...


#pragma once
#include "ReportBase.h"
#include "CurMbrList.h"


enum MbrIDList {CallSignList, PlusIDsList, SuffixList};


class MbrIDs : public ReportBase {
public:

  MbrIDs(TCchar* path) : ReportBase(path) { }

  void operator() (MbrIDList listType);

private:

  MbrIDs() : ReportBase(0) { }
  };

