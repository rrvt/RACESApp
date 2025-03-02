// Member Search


#include "pch.h"
#include "MbrSearch.h"
#include "MbrInfo.h"


bool MbrSearch::left() {index = ctl.GetCurSel() - 1;   return index >= 0 && setCurSel();}


bool MbrSearch::find(TCchar* tgt) {

  target = tgt;   lng = target.length();

  curFld = curFldOnly ? ::GetDlgCtrlID(::GetFocus()) : 0;

  for (index = 0, n = ctl.GetCount(); index < n; index++) if (find()) return setCurSel();

  return false;
  }


bool MbrSearch::findNext() {

  for (index++; index < n; index++) if (find()) return setCurSel();

  return false;
  }


bool MbrSearch::find() {
MbrInfo* info = (MbrInfo*) ctl.GetItemDataPtr(index);

  return info && info->find(this, target, curFld, field);
  }


bool MbrSearch::right() {index = ctl.GetCurSel() + 1;   return index >= 0 && setCurSel();}


bool MbrSearch::compare(TCchar* tc, TCchar* tgt) {
String s = tc;
String t = tgt;
int    pos;

  if (!caseSensitive) {s.lowerCase();  t.lowerCase();}

  pos = s.find(t);   if (pos < 0) return false;

  if (wholeWord && !isWord(s, pos, t.length())) return false;

  switch (attributes) {
    case 0  : return s.length() == t.length();    // Whole Field
    case 1  : return true;                        // Anywhere In
    case 2  : return pos ? false : true;          // Beginning
    }
  return false;
  }


static TCchar* BoundaryChar = _T(" !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");


bool MbrSearch::isWord(String& s, int pos, int lng) {
int    prePos = pos - 1;
int    aftPos = pos + lng;
String preCh  = prePos >= 0         ? s[prePos] : _T(' ');
String aftCh  = aftPos < s.length() ? s[aftPos] : _T(' ');

  return !preCh.findOneOf(BoundaryChar) && !aftCh.findOneOf(BoundaryChar);
  }

