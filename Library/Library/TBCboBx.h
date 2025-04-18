// Tool Bar Combo Box


#pragma once

struct CbxItem;


class TBCboBx : public CMFCToolBarComboBoxButton {

uint                       id;
int                        maxChars;
CMFCToolBarComboBoxButton* actual;

public:

String caption;

              TBCboBx(uint myId) : CMFCToolBarComboBoxButton(myId, -1), id(myId), maxChars(0),
                                                                                      actual(0) { }
             ~TBCboBx() { }

  TBCboBx*    install(int           noChars);
  TBCboBx*    install(int           idr,              TCchar* caption);
  TBCboBx*    install(const CbxItem cbxItem[], int n, TCchar* caption);

  // The following functions deal with the installed combo box.
  void        clear() {if (getActual()) actual->RemoveAllItems();}
  bool        setCaption();
  void        setCaption(TCchar* caption) {this->caption = caption;   setCaption();}
  bool        addItem(TCchar* txt, int val);
  bool        addItemSorted(TCchar* txt, int val);
  uint        getCount() {return actual ? actual->GetCount() : 0;}
  void        setWidth();
  void        setHeight();
  bool        getCurSel(String& s, void*& data);

  int         find(TCchar* tc);
  bool        setCurSel(int index);
  bool        setCurSel(TCchar* tc);

  uint        getId() {return id;}

private:

  bool        getActual() {if (!actual) actual = GetByCmd(id);   return actual != 0;}

  bool        add(TCchar* txt, int data);
  TBCboBx*    finInstall(TCchar* caption);
  void        setMaxChars(TCchar* txt) {int t;  t = _tcslen(txt);  if (t > maxChars) maxChars = t;}
  };

