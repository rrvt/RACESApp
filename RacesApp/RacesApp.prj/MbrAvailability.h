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
  int  getID();

private:

  MbrAvailability() : listCtl(*(CComboBox*)0) { }
  };

