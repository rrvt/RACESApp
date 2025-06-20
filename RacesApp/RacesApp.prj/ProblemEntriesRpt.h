// Problem Entries Report


#pragma once
#include "ReportBase.h"

struct MbrInfo;


class ProblemEntriesRpt : public ReportBase {

public:

  ProblemEntriesRpt(TCchar* path) : ReportBase(path) { }
 ~ProblemEntriesRpt() { }

  void operator() ();

private:

  bool isProblem(MbrInfo& info);

  void output(MbrInfo& info);
  };

