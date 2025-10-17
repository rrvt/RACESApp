// My ToolBar


#include "pch.h"
#include "MyToolBar.h"
#include "Resource.h"

static int NoOfButtonControls =  2;
static int NoOfButtons        =  6;



MyToolBar::MyToolBar() : rptMenu(ID_ReportMenu), button(ID_SaveMember)
                        {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}


bool MyToolBar::addButton( uint id, TCchar* caption) {
  if (id == button.getId()) return add(button,  id, caption);

  return false;
  }


bool MyToolBar::addMenu(uint id, int idr, TCchar* caption) {
  if (id == rptMenu.getId())  return add(rptMenu,  id, idr, caption);

  return false;
  }


bool MyToolBar::addMenu(uint id, CbxItem cbxItem[], int n, TCchar* caption) {
  if (id == rptMenu.getId())   return add(rptMenu,  id, cbxItem, n, caption);

  return false;
  }


void MyToolBar::setWthPercent(uint id, int prcnt) {
  if (id == rptMenu.getId()) {ToolBarBase::setWthPercent(rptMenu,     prcnt);   return;}
  }


void MyToolBar::setWidth(uint id) {
  if (id == rptMenu.getId()) {ToolBarBase::setWidth(rptMenu);      return;}
  Invalidate();
  }


void MyToolBar::setHeight( uint id) {
  if (id == rptMenu.getId()) ToolBarBase::setHeight(rptMenu);
  }


void MyToolBar::dispatch(uint id) {
  if (id == rptMenu.getId()) ToolBarBase::dispatch(rptMenu);
  }


