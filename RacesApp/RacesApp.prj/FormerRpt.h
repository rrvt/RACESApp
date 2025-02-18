// Former Member Report


#pragma once
#include "ReportBase.h"

struct MbrInfo;


class FormerRpt : public ReportBase {

String beg;
String end;

public:

  FormerRpt(TCchar* path) : ReportBase(path) { }

  void operator() (TCchar* begPrd, TCchar* endPrd);

private:

  void header();
  bool output(MbrInfo& rcd);
  bool inPeriod(TCchar* tc);

  FormerRpt() : ReportBase(0) { }
  };

