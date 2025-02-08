// Utility Functions


#include "pch.h"
#include "RNUtility.h"
#include "Date.h"

#include "MessageBox.h"


static String adjFrag(String& frag);


int getInt(CStatic& ctl) {
Cstring cs;
uint    pos;

  ctl.GetWindowText(cs);    return cs.stoi(pos);
  }



String& replaceCrlf(TCchar* tc) {
String        s;
static String t;   t.clear();
int           i;
int           n;

  if (!tc) return t;

  s = tc;

  for (n = s.length(), i = 0; i < n; i++) {
    Tchar ch = s[i];

    if (ch == _T('\r')) continue;
    if (ch == _T('\n')) {t += _T("; "); continue;}
    t += ch;
    }
  return t;
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

  if (!s.isEmpty()) s+= _T("; "); s += prefix;  s += _T(' ') + replaceCrlf(body);   return s;
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


#if 0
void disableBttn(CButton& ctl) {
uint style = ctl.GetButtonStyle();
uint before = style;

  style |= WS_DISABLED;

String s;   s.format(_T("Before %0x, After %0x"), before, style);
messageBox(s);
  ctl.SetButtonStyle(style);
  }


void enableBttn(CButton& ctl) {
uint style = ctl.GetButtonStyle();
uint before = style;

  style &= WS_DISABLED ^ -1;

  String s;   s.format(_T("Before %0x, After %0x"), before, style);
  messageBox(s);

  ctl.SetButtonStyle(style);
  }
#endif


///--------------------

#if 1
#else
HBITMAP hBitmap = image.Detach();   if (!hBitmap) return;

        ctl.SetBitmap(hBitmap);



  ctl.GetClientRect(&rect);

  ctl.ReleaseDC(dc);
#endif
#if 0
CImage image;
    if (SUCCEEDED(image.Load(_T("path/to/your/image.jpg")))) // Replace with your image path
    {
        // Get the picture control's device context
        CDC* pDC = m_pictureCtrl.GetDC();
        if (pDC)
        {
            // Get the picture control's rectangle
            CRect rect;
            m_pictureCtrl.GetClientRect(&rect);

            // Draw the image
            image.StretchBlt(*pDC, rect);

            // Release the device context
            m_pictureCtrl.ReleaseDC(pDC);
///----------------
void CMyDialog::LoadImage(const CString& filePath)
{
    if (m_pictureCtrl.Load(filePath))
    {
        // Adjust Picture Control size to fit the image
        m_pictureCtrl.SetBitmapDimension(m_pictureCtrl.GetImageWidth(), m_pictureCtrl.GetImageHeight());
        m_pictureCtrl.Invalidate();
    }
    else
    {
        // Handle loading error
        MessageBox(_T("Failed to load image."), _T("Error"), MB_OK | MB_ICONERROR);
    }
}

#endif

