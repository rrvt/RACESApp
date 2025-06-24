// Utility Functions


#include "pch.h"
#include "Utility.h"
#include "Date.h"

#include "MessageBox.h"


static String adjFrag(String& frag);


TCchar* set(CStatic&   ctl, TCchar* txt) {String s = txt;   ctl.SetWindowText(s);   return s;}
TCchar* set(CEdit&     ctl, TCchar* txt) {String s = txt;   ctl.SetWindowText(s);   return s;}
TCchar* set(CComboBox& ctl, TCchar* txt) {String s = txt;   ctl.SetWindowText(s);   return s;}

TCchar* set(CStatic&   ctl, TCchar* txt, TCchar* lbl)
                                  {String s = txt && *txt ? txt : lbl;    set(ctl, s);   return s;}
TCchar* set(CEdit&     ctl, TCchar* txt, TCchar* lbl)
                                  {String s = txt && *txt ? txt : lbl;    set(ctl, s);   return s;}
TCchar* set(CComboBox& ctl, TCchar* txt, TCchar* lbl)
                                  {String s = txt && *txt ? txt : lbl;    set(ctl, s);   return s;}




int getInt(CStatic& ctl) {
Cstring cs;
uint    pos;

  ctl.GetWindowText(cs);    return cs.stoi(pos);
  }



// 4085551212 becomes 408.555.1212

String expandPhone(TCchar* tc) {
String s   = tc ? tc : _T("");      s.trim();
int    lng = s.length();
String t;

  if (!lng) return s;

  if (s.find(_T('.')) > 0 || s.find(_T('-')) > 0) return s;

  if (lng >= 10) {t = s.substr(0, 3) + _T('.');   s = s.substr(3);}

  t += s.substr(0, 3) + _T('.') + s.substr(3);   return t;
  }


// (408) 555-1212 becomes 4085551212 or
// 408.555.1212 becomes 4085551212 or
// 408-555-1212 becomes 4085551212 or combinations of "()", ' ', '.' & '-'

String compressPhone(TCchar* tc) {
String s   = tc;      s.trim();
int    lng = s.length();
int    pos = 0;
int    pos2;
Tchar  ch;
String t;

  if (lng <= 7) return s;

  if (lng > 8) {
    if (s[0] == _T('(')) {
      pos = s.findOneOf(_T(") -."), 1);     if (pos < 0) {t = s.substr(1);   return t;}
      t = s.substr(1, pos-1);               pos++;
      for (ch = s[pos]; ch == _T(' '); ch = s[++pos]) continue;    // Remove blanks (408) 555-1212
      }
    else {
      pos = s.findOneOf(_T("-. "));         if (pos < 0) return s;

      t = s.substr(0, pos);                 pos++;
      }
    }

  pos2 = s.findOneOf(_T("-. "), pos);       if (pos2 < 0) {t += s.substr(pos);   return t;}

  t += s.substr(pos, pos2-pos);   pos2++;   t += s.substr(pos2);   return t;
  }


String expandDate(TCchar* tc) {
String dt = tc;
String s;

  if (!dt.length() || dt.find(_T('/')) > 0) return dt;

  s = dt.substr(0, 2) + _T('/') + dt.substr(2, 2) + _T('/') + dt.substr(4);   return s;
  }


String compressDate(TCchar* cs) {
String dt = cs;
int    pos;
int    pos2;
String frag;
String s;

  pos = dt.find(_T('/'));             if (pos < 0) return dt;

  frag = dt.substr(0, pos);           s = adjFrag(frag);   pos++;

  pos2 = dt.find(_T('/'), pos);       if (pos < 0) {s += dt.substr(pos);   return s;}

  frag = dt.substr(pos, pos2-pos);    s += adjFrag(frag);   pos2++;

  frag = dt.substr(pos2);             s += frag.length() < 4 ? adjFrag(frag) : frag;

  return s;
  }


String adjFrag(String& frag) {
int lng;

  for (lng = frag.length(); lng != 2; lng = frag.length()) {
    if (lng > 2) {
      if      (frag[0]     == _T('0')) frag = frag.substr(1);
      else if (frag[lng-1] == _T('0')) frag = frag.substr(0, lng-1);
      else                             frag = frag.substr(0, 2);
      continue;
      }

    frag = _T('0') + frag;
    }

  return frag;
  }


// 951322630 becomes 95132-2630

String expandZip(TCchar* tc) {
String s    = tc;       s.trim();
int    lng = s.length();
String t;

  if (lng <= 5 || s[0] < _T('0') || _T('9') < s[0]) return s;

  t = s.substr(0, 5) + _T('-');   s = s.substr(5);   t += s;   return t;
  }


// 95132-2630 becomes 951322630

String compressZip(TCchar* tc) {
String s   = tc;   s.trim();
int    pos = s.find(_T('-'));
String t;

  if (pos < 0) return s;

  t = s.substr(0, pos);   pos++;   t += s.substr(pos);   return t;
  }


String& appdAttr(String& s, TCchar* prefix, String& body) {

  if (body.isEmpty()) return s;

  if (!s.isEmpty()) s+= _T("; "); s += prefix;  s += _T(' ') + utl.replaceCrlf(body);   return s;
  }


void setPicture(CStatic& ctl, TCchar* path) {
CImage image;              if (image.Load(path) < 0) return;
CDC*   dc;
CRect  rect;
POINT  point;

  dc = ctl.GetDC();   if (!dc) return;

    ctl.GetClientRect(&rect);

    SetStretchBltMode(*dc, HALFTONE);   SetBrushOrgEx(*dc, 0, 0, &point);

    image.Draw(*dc, rect);

  ctl.ReleaseDC(dc);
  }



bool isEarlier(TCchar* updateDate) {
Date      updt(updateDate);
Date      bnd;                        bnd.getToday();
CTimeSpan delta(365 * 3, 0, 0, 0);    bnd -= delta;

  return updt < bnd;
  }



void setMax(String& s, int& max) {int lng = s.length();   if (lng > max) max = lng;}



void addCB(CComboBox& ctl, TCchar* key, void* rcd)
                            {int x = ctl.AddString(key);   if (x >= 0) ctl.SetItemDataPtr(x, rcd);}


// set field only if not equal

bool setField(String& fld, TCchar* tc) {if (fld ==  tc) return false;   fld = tc;    return true;}
bool setField(int&    fld, int      v) {if (fld ==   v) return false;   fld =  v;    return true;}


// Get 2 char date for 1960 -- 2059

uint getDate(TCchar* tc) {
String s = tc;
uint   pos;
uint   dt = s.stoi(pos);

  if (dt < 6000) dt += 10000;   return dt;
  }


String& Utilities::replaceCrlf(TCchar* tc) {
String s;
int    i;
int    n;

  t.clear();   if (!tc) return t;

  s = tc;

  for (n = s.length(), i = 0; i < n; i++) {
    Tchar ch = s[i];

    if (ch == _T('\r')) continue;
    if (ch == _T('\n')) {t += _T("; "); continue;}
    t += ch;
    }

  return t;
  }


String& Utilities::getTodayCmpr() {
Date today;

  today.getToday();   return s = today.format(_T("%m%d%y"));
  }


String& Utilities::getTodayExpd() {
Date today;

  today.getToday();   return s = today.format(_T("%m/%d/%y"));
  }


///------------


