// MM/YY Control


#include "pch.h"
#include "MmYyCtl.h"


void MmYyCtl::verify() {
Tchar  buf[128];
int    lng = CEdit::GetLine(0, buf, noElements(buf));
String txt;
int    i;
bool   update = false;

  if (lng >= 0) {buf[lng] = 0;   txt = buf;}

  for (i = 0; i < lng; i++) {
    Tchar ch = txt[i];

    if (ch != _T('/') && (ch < _T('0') ||_T('9') < ch)) {txt[i] = _T(' ');   update = true;}
    }

  if (update) {SetWindowText(txt.trim());   SetSel(txt.length(), -1);}
  }


String MmYyCtl::format(TCchar* tc) {
String s = tc;
String mm;
String yy;
int    pos = s.find(_T('/'));

  if (pos < 0) return s;

  mm = s.substr(0, pos);   yy = s.substr(pos+1);

  while (mm.length() < 2) mm = _T('0') + mm;
  while (mm.length() > 2) mm = mm.substr(1);
  while (yy.length() < 2) yy = _T('0') + yy;
  while (yy.length() > 2) yy = yy.substr(1);
  return yy + mm;
  }

