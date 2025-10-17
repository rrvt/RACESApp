// Member Status Dropdown List


#pragma once

class MbrRcd;


class MbrStatus {

CComboBox& listCtl;

public:

  MbrStatus(CComboBox& ctl) : listCtl(ctl) {};
 ~MbrStatus() { };

  void load();

  void setDefault();
  int  isDefault();                     // is Default setting or clear
  void set(MbrRcd* rcd);
  int  getID();

private:

  MbrStatus() : listCtl(*(CComboBox*)0) { }
  };

