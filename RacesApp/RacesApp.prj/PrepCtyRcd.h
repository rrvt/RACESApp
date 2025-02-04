// Prepare City Record


#pragma once
#include "CtyTbl.h"


class PrepCtyRcd {

CtyRcd rcd;

public:

          PrepCtyRcd() { }
         ~PrepCtyRcd() { }

  void    setCity(TCchar* tc)  {rcd.city  = tc;}
  void    setState(TCchar* tc) {rcd.state = tc;}
  void    setZip(TCchar* tc)   {rcd.zip   = compressZip(tc);}

  bool    isDifferent(CtyRcd* ctyRcd);
  CtyRcd* add();

  String compressZip(TCchar* tc);

private:
  };

