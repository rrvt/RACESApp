// My ToolBar


#include "pch.h"
#include "MyToolBar.h"
#include "Resource.h"

static int NoOfButtonControls =  2;
static int NoOfButtons        =  6;



MyToolBar::MyToolBar() : rptMenu(createCboBox(ID_ReportMenu)), button(ID_SaveMember)
                        {toolBarDim.initialize(NoOfButtonControls, NoOfButtons);}


bool MyToolBar::addButton( uint id, TCchar* caption) {
  if (id == button.getId()) return add(button,  id, caption);

  return false;
  }


//bool MyToolBar::setCboItems(uint id, int idr) {return setCboItems(id, idr);}


//bool MyToolBar::setCboItems(uint id, CbxItem cbxItem[], int n) {return setCboItems(id, cbxItem, n);}


void MyToolBar::setCboCaption(uint id, TCchar* txt)
                             {if (id == rptMenu.getId()) ToolBarBase::setCboCaption(rptMenu, txt);}


void MyToolBar::setCboWthPrct(uint id, int percent)
                         {if (id == rptMenu.getId()) ToolBarBase::setCboWthPrct(rptMenu, percent);}



void MyToolBar::setCboHeight(uint id)
  {if (id == rptMenu.getId()) ToolBarBase::setCboHeight(rptMenu);}


void MyToolBar::dispatch(uint id) {ToolBarBase::dispatch(rptMenu);}


