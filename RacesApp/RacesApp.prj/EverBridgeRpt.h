// EverBridge Report


#pragma once
#include "ReportBase.h"

struct MbrInfo;



class EverBridgeRpt : public ReportBase {

public:

  EverBridgeRpt(TCchar* path) : ReportBase(path) { }
 ~EverBridgeRpt() { }

  void operator() ();

private:

  void header();
  void output(MbrInfo& info);
  void location(TCchar* title, EntRcd* rcd);
  void phone(TCchar* ph);
  void eMail(TCchar* em);


  EverBridgeRpt() : ReportBase(0) { }
  };

