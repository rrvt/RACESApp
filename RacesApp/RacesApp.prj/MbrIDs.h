// Member IDs, i.e. Call Signs alone and Call Signs, Names, etc...


#pragma once
#include "ReportBase.h"
#include "CurMbrList.h"


class MbrIDs : public ReportBase {
public:

  MbrIDs(TCchar* path) : ReportBase(path) { }

  void operator() (bool plus);

private:

  MbrIDs() : ReportBase(0) { }
  };

