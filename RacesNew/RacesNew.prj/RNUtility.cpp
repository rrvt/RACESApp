// Utility Functions


#include "pch.h"
#include "RNUtility.h"
#include "Date.h"

#include "MessageBox.h"


int getInt(CStatic& ctl) {
Cstring cs;
uint    pos;

  ctl.GetWindowText(cs);    return cs.stoi(pos);
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

