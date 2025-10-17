// My ToolBar


#pragma once


#include "TBCbxMenu.h"
#include "TBButton.h"
#include "ToolBarBase.h"


struct CbxItem;


class MyToolBar : public ToolBarBase {

TBCbxMenu rptMenu;
TBButton  button;

public:

  MyToolBar();
 ~MyToolBar() { }

  bool addButton( uint id, TCchar* caption);
  bool addMenu(   uint id, int idr, TCchar* caption);
  bool addMenu(   uint id, CbxItem cbxItem[], int n, TCchar* caption);
  void dispatch(  uint id);
  void setWthPercent(uint id, int prcnt);            // good for Menus and ComboBoxes
  void setWidth(  uint id);
  void setHeight( uint id);
  };



////////-----------

