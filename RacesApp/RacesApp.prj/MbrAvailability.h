// Availability Drop Down List

#pragma once

class MbrRcd;


class MbrAvailability {

CComboBox& listCtl;

public:

  MbrAvailability(CComboBox& ctl) : listCtl(ctl) { }
 ~MbrAvailability() { }

  void load();
  void set(MbrRcd* rcd);
  void setDefault();
  int  isDefault();
  bool isNonResp() {return getAbbr() == _T("N");}
  int  getID();

private:

  String getAbbr();

  MbrAvailability() : listCtl(*(CComboBox*)0) { }
  };

