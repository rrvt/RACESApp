// Manipulate a Single Picture


#pragma once
#include "FileName.h"



class APicture {

CStatic& ctl;
String   dbRootPath;
String   path;
bool     visible;
CDialog& dlg;
int      horzLowBnd;
int      horzUpBnd;
int      vertLowBnd;
int      vertUpBnd;

public:

  APicture(CStatic& picCtl, CDialog& dialog);
 ~APicture() { }

  void clear();

  void setRootPath(TCchar* path) {dbRootPath = getPath(path);}

  void set(TCchar* picPath) {path = dbRootPath + picPath;   visible = true;   set();}

  void check(int w, int h);

  void set();

private:

  void setBnds();
  };

