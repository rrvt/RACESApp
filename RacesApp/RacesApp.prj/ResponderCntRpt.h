// Responder Counts by Attribute


#pragma once
#include "ReportBase.h"


class ResponderCntRpt : public ReportBase {
public:

  ResponderCntRpt(TCchar* path) : ReportBase(path) { }
 ~ResponderCntRpt() { }

  void operator() ();

private:

  int getRspClass(AsnRcd* asnRcd);

  ResponderCntRpt() : ReportBase(0) { }
  };

