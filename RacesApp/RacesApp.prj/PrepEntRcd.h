// Prepare Entity Record


#pragma once
#include "EntTbl.h"
#include "PrepAdrRcd.h"
#include "PrepCtyRcd.h"


class PrepEntRcd : public PrepAdrRcd, public PrepCtyRcd {

EntRcd rcd;

public:

       PrepEntRcd() { }
      ~PrepEntRcd() { }

  void clear() {rcd.clear();}

  void setFirstName(TCchar* tc)  {rcd.firstName     = tc;}
  void setMiddleInit(TCchar* tc) {rcd.middleInitial = tc;}
  void setLastName(TCchar* tc)   {rcd.lastName      = tc;}
  void setSuffix(TCchar* tc)     {rcd.suffix        = tc;}
  void setEmail(TCchar* tc)      {rcd.eMail         = tc;}
  void setCellPh(TCchar* tc)     {rcd.phone2        = compressPhone(tc);}
  void setLandLine(TCchar* tc)   {rcd.phone1        = compressPhone(tc);}
  void setZipOnly(int chk)       {rcd.addrIsPO      = chk;}
  void setLocZip(TCchar* tc)     {rcd.locationZip   = compressZip(tc);}

  void setAdrRcd(AdrRcd* adr);
  void setCtyRcd(CtyRcd* cty);

  TCchar* getTxtPh()             {return rcd.phone2;}

  int  updateRcd(EntRcd* entRcd);
  int  noUsed(int id);

private:

  void   update(EntRcd* entRcd);
  String compressPhone(TCchar* tc);
  };

