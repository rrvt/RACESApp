// Utility Functions


#pragma once

inline TCchar* get(CStatic& ctl) {static Cstring cs;   ctl.GetWindowText(cs);   return cs;}
inline TCchar* get(CEdit&   ctl) {static Cstring cs;   ctl.GetWindowText(cs);   return cs;}
inline TCchar* get(int        v) {static String s(v);  return s;}

inline TCchar* set(CStatic&   ctl, TCchar* txt) {ctl.SetWindowText(txt);   return txt;}
inline TCchar* set(CEdit&     ctl, TCchar* txt) {ctl.SetWindowText(txt);   return txt;}
inline bool    set(CButton&   ctl, bool    chk) {ctl.SetCheck(chk);        return chk;}

       void    setPicture(CStatic& ctl, TCchar* path);

inline void    clear(CStatic&   ctl) {ctl.SetWindowText(_T(""));}
inline void    clear(CEdit&     ctl) {ctl.SetWindowText(_T(""));}
inline void    clear(CButton&   ctl) {set(ctl, false);}
inline void    clear(CComboBox& ctl) {ctl.SetCurSel(-1);}
inline void    reset(CComboBox& ctl) {ctl.ResetContent();}


inline void    clrLbl(CEdit& ctl, TCchar* txt)
                             {Cstring lbl;   ctl.GetWindowText(lbl);   if (lbl == txt) clear(ctl);}

int    getInt(CStatic& ctl);
String expandZip(TCchar* tc);
String compressZip(TCchar* tc);

bool   isEarlier(TCchar* updateDate);

#if 0
void disableBttn(CButton& ctl);
void enableBttn( CButton& ctl);
#endif


