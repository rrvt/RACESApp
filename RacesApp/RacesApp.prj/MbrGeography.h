// Member Geography List


#pragma once

class MbrRcd;



class MbrGeography {

CComboBox& listCtl;

public:

  MbrGeography(CComboBox& ctl) : listCtl(ctl) { }
 ~MbrGeography() { }

  void load();
  void set(MbrRcd* rcd);
  void setDefault();
  int  isDefault();
  int  getID();

private:

  MbrGeography() : listCtl(*(CComboBox*)0) { }
  };

