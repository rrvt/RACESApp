// My ToolBar


#pragma once


#include "TBButton.h"
#include "ToolBarBase.h"


struct CbxItem;


class MyToolBar : public ToolBarBase {

TBCboBox& rptMenu;
TBButton  button;

public:

  MyToolBar();
 ~MyToolBar() { }

  bool addButton( uint id, TCchar* caption);
  bool setCboItems(   uint id, uint idr) {return ToolBarBase::setCboItems(id, idr);}
  bool setCboItems(   uint id, CCbxItem cbxItem[], int n)
                                        {return ToolBarBase::setCboItems(id, cbxItem, n);}
  void setCboCaption(uint id, TCchar* txt);
  void setCboWthPrct(uint id, int percent);
  void setCboHeight( uint id);
  void dispatch(     uint id);
  };



////////-----------

