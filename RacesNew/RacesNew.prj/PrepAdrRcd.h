// Prepare Address Record


#pragma once
#include "AdrTbl.h"


class PrepAdrRcd {

AdrRcd rcd;

public:


          PrepAdrRcd() { }
         ~PrepAdrRcd() { }

  void    setAddress(TCchar* tc) {rcd.address1 = tc;}
  void    setUnitNo(TCchar* tc)  {rcd.address2 = tc;}

  bool    isDifferent(AdrRcd* adrRcd);
  AdrRcd* add();
  };

