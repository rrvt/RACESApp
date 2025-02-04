// Manipulate a Single Picture


#include "pch.h"
#include "APicture.h"
#include "Resource.h"

#include "MessageBox.h"


APicture::APicture(CStatic& picCtl, CDialog& dialog) : ctl(picCtl), visible(false), dlg(dialog),
horzLowBnd(0), horzUpBnd(0), vertLowBnd(0), vertUpBnd(0) { }


void APicture::check(int w, int h) {

  setBnds();

  if (visible) {
    if (w < horzLowBnd || h < vertLowBnd) visible = false;
    return;
    }

  if (w >= horzUpBnd || h >= vertUpBnd) {set(); return;}

  if (w >= horzUpBnd && h >= vertUpBnd) {set();   visible = true;}
  }


// Map Middle of picture to screen units

void APicture::setBnds() {
CRect r;

  if (vertUpBnd) return;

  r.left  =   0;   r.top    =  0;
  r.right = 469;   r.bottom = 13;   dlg.MapDialogRect(&r);

  horzLowBnd = r.right;   vertLowBnd = r.bottom;

  r.right = 499;   r.bottom = 53;   dlg.MapDialogRect(&r);

  horzUpBnd = r.right;    vertUpBnd  = r.bottom;
  }


void APicture::clear() {path.clear();   visible = false;   set();}


void APicture::set() {
CImage image;
CDC*   dc;
CRect  rect;
POINT  point;

  if (!visible)              image.LoadFromResource(AfxGetInstanceHandle(), IDB_PuppyBitMap);
  else if (path.isEmpty() || image.Load(path) < 0) return;

  dc = ctl.GetDC();   if (!dc) return;

    ctl.GetClientRect(&rect);

    SetStretchBltMode(*dc, HALFTONE);   SetBrushOrgEx(*dc, 0, 0, &point);   image.Draw(*dc, rect);

  ctl.ReleaseDC(dc);
  }



