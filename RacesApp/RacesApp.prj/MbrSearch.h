// Member Search


#pragma once


class MbrSearch {

CComboBox& ctl;
String     target;
int        lng;
int        curFld;
int        index;
int        field;
int        n;


public:
BOOL wholeWord;         // Search Parameters
BOOL curFldOnly;
BOOL caseSensitive;
int  attributes;        // 0 - Whole Field, 1 - Anywhere in, 2 - Beginning (i.e. prefix) of

  MbrSearch(CComboBox& control) : ctl(control), lng(0), curFld(0), index(-1), field(0), n(0) { }

  bool left();                          // Returns true if control set to new entry

  bool find(TCchar* tgt);
  bool findNext();

  bool right();

  int  getFieldID() {return field;}

  bool compare(TCchar* tc, TCchar* tgt);

private:

  bool find();
  bool isWord(String& s, int pos);
  bool setCurSel() {return ctl.SetCurSel(index) >= 0;}

  MbrSearch() : ctl(*(CComboBox*)0) { }
  };


