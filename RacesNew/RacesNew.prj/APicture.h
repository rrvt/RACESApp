// Manipulate a Single Picture


#pragma once



class APicture {

CStatic& ctl;
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

  void set(TCchar* picPath) {path = picPath;   visible = true;   set();}

  void check(int w, int h);

  void set();

private:

  void setBnds();
  };

