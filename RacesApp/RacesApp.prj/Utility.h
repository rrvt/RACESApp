// Utility Functions


#pragma once
#include "MessageBox.h"

class AdrRcd;


class Utilities {

Cstring cs;
String   s;
String   t;

public:

  Utilities() { }
 ~Utilities() { }

  TCchar* get(CStatic&   ctl) {ctl.GetWindowText(cs);   return cs;}
  TCchar* get(CEdit&     ctl) {ctl.GetWindowText(cs);   return cs;}
  TCchar* get(CComboBox& ctl) {ctl.GetWindowText(cs);   return cs;}

  TCchar* get(int          v) {s = v; return s;}

  String& replaceCrlf(TCchar* tc);
  String& getTodayCmpr();                            // returns mmddyy
  String& getTodayExpd();                            // returns mm/dd/yy
  };


extern Utilities utl;


inline bool    set(CButton&   ctl, bool    chk) {ctl.SetCheck(chk);   return chk;}
       TCchar* set(CStatic&   ctl, TCchar* txt);
       TCchar* set(CEdit&     ctl, TCchar* txt);
       TCchar* set(CComboBox& ctl, TCchar* txt);
       TCchar* set(CComboBox& ctl, TCchar* txt, TCchar* lbl);

       TCchar* set(CStatic&   ctl, TCchar* txt, TCchar* lbl);     // If txt empty, set lbl
       TCchar* set(CEdit&     ctl, TCchar* txt, TCchar* lbl);

inline bool    isLabel(CStatic&   ctl, TCchar* lbl) {return (utl.get(ctl) == lbl);}
inline bool    isLabel(CEdit&     ctl, TCchar* lbl) {return (utl.get(ctl) == lbl);}
inline bool    isLabel(CComboBox& ctl, TCchar* lbl) {return (utl.get(ctl) == lbl);}

       void    addCB(CComboBox& ctl, TCchar* key, void* rcd);

       void    setPicture(CStatic& ctl, TCchar* path);

inline void    clear(CStatic&   ctl) {ctl.SetWindowText(_T(""));}
inline void    clear(CEdit&     ctl) {ctl.SetWindowText(_T(""));}
inline void    clear(CButton&   ctl) {set(ctl, false);}
inline void    clear(CComboBox& ctl) {ctl.SetCurSel(-1);}
inline void    reset(CComboBox& ctl) {ctl.ResetContent();}

       void    setMax(String& s, int& max);

inline void    clrLbl(CEdit& ctl, TCchar* txt)
                            {Cstring lbl;   ctl.GetWindowText(lbl);   if (lbl == txt) clear(ctl);}

       int     getInt(CStatic& ctl);


       String  expandPhone(TCchar* tc);                  // 4085551212 becomes 408.555.1212
       String  compressPhone(TCchar* tc);                // 408.555.1212 becomes 4085551212

       String  expandDate(TCchar* tc);
       String  compressDate(TCchar* cs);

       String  expandZip(TCchar* tc);
       String  compressZip(TCchar* tc);

       String& appdAttr(String& s, TCchar* prefix, String& body);

       bool    isEarlier(TCchar* updateDate);

       bool    setField(String& fld, TCchar* tc);        // only if not equal
       bool    setField(int&    fld, int      v);


       uint    getDate(TCchar* tc);                       // Get 2 char date for 1960 -- 2059




////////----------------

