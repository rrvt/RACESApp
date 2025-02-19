// MM/YY Control


#pragma once


class MmYyCtl : public CEdit {
public:

  MmYyCtl() { }
 ~MmYyCtl() { }

  void verify();

  String format(TCchar* tc);
  };

