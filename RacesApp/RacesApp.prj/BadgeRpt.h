// Badge Reports


#pragma once
#include "ReportBase.h"
#include "CurMbrList.h"

struct MbrInfo;





class BadgeRpt : public ReportBase {

int tab2;
int tab3;
int tab4;

public:

       BadgeRpt(TCchar* path) : ReportBase(path), tab2(0), tab3(0), tab4(0) { }
      ~BadgeRpt() { }

  void operator() (CurMbrSort sort);

private:

  void output(CurMbrData& item);

       BadgeRpt() : ReportBase(0) { }
  };

