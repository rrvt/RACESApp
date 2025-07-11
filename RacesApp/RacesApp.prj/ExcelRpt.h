//Excel Report


#pragma once


#include "ReportBase.h"

struct MbrInfo;


class ExcelRpt : public ReportBase {
public:

  ExcelRpt(TCchar* path) : ReportBase(path) { }

  void operator() ();

private:

  void header();
  void output(MbrInfo& info);

  ExcelRpt() : ReportBase(0) { }
  };

