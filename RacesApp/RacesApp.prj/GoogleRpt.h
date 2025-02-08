// Google Earch Report


#pragma once
#include "ReportBase.h"

class  AdrRcd;
class  EntRcd;
struct MbrInfo;


class GoogleRpt : public ReportBase {

public:

  GoogleRpt(TCchar* path) : ReportBase(path) { }
 ~GoogleRpt() { }

  void operator() ();

private:

  void header();
  bool output(MbrInfo& info, bool workAddr);
  bool addrAvail(EntRcd* rcd, AdrRcd*& addrRcd);
  void putEntity(EntRcd* rcd, AdrRcd*& addrRcd);

  GoogleRpt() : ReportBase(0) { }
  };

