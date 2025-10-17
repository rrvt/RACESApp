// Replaces CArchiveBase to allow for Unicode internally and ansi in external files
// Copyright Bob -- K6RWY, 2019


#include "pch.h"
#include "ArchiveB.h"


ArManip aClrTabs;
ArManip aTab;
ArManip aCenter;
ArManip aRight;

ArManip aBeginLine;
ArManip aEndLine;
ArManip aSetHex;
ArManip aCrlf;            // add to stream to terminate a line on display: dsp << "xyz" << dCrlf;


static ArManipInt& setupManipInt(ArManipInt::Func func, int    val);
static ArManipDbl& setupManipDbl(ArManipDbl::Func func, double val);



//ArchiveB::ArchiveB(TCchar* fileName, int mode) : ArchPos(fileName, mode) {initialize();}



void ArchiveB::initialize() {

  aClrTabs.n   = this; aClrTabs.func   = ArchiveB::doClrTabs;
  aTab.n       = this; aTab.func       = ArchiveB::doTab;
  aCenter.n    = this; aCenter.func    = ArchiveB::doCenter;
  aRight.n     = this; aRight.func     = ArchiveB::doRight;
  aBeginLine.n = this; aBeginLine.func = ArchiveB::doBeginLine;
  aEndLine.n   = this; aEndLine.func   = ArchiveB::doEndLine;
  aSetHex.n    = this; aSetHex.func    = ArchiveB::doSetHex;
  aCrlf.n      = this; aCrlf.func      = ArchiveB::doCrlf;
  }


ArchiveB& ArchiveB::append(Cchar*  cs) {ToUniCode uni(cs);   return append(uni());}

ArchiveB& ArchiveB::append(long v)
     {nmbr.longVal = v;   nmbr.typ = IntNmbrTyp;    append(nmbr());   nmbr.clear();  return *this;}


ArchiveB& ArchiveB::append(ulong v)
     {nmbr.longVal = v;   nmbr.typ = UIntNmbrTyp;   append(nmbr());   nmbr.clear();  return *this;}


ArchiveB& ArchiveB::append(double v)
     {nmbr.dblVal = v;    nmbr.typ = DblNmbTyp;     append(nmbr());   nmbr.clear();  return *this;}


ArchiveB& ArchiveB::append(Date& dt) {String s = dt;   return append(s);}


ArchiveB& ArchiveB::flush() {write(arLine);   return *this;}


// Set left margin (no. chars)

ArManipDbl& aSetLMargin(double val)  {return setupManipDbl(ArchiveB::doSetLMargin, val);}
ArchiveB& ArchiveB::doSetLMargin(ArchiveB& n, double v) {n.setLMargin(v);    return n;}


ArManipDbl& aSetRMargin(double val)  {return setupManipDbl(ArchiveB::doSetRMargin, val);}
ArchiveB& ArchiveB::doSetRMargin(ArchiveB& n, double v) {n.setRMargin(v);    return n;}

// Set width (length) of line in file (no. chars)

ArManipInt& aPageWidth(int val)  {return setupManipInt(ArchiveB::doPageWidth, val);}
ArchiveB& ArchiveB::doPageWidth(ArchiveB& n, int v) {n.setPageWidth(v);    return n;}


ArManipInt& aSetTab(int val) {return setupManipInt(ArchiveB::doSetTab, val);}
ArchiveB& ArchiveB::doSetTab(ArchiveB& n, int v) {n.setTab(v);    return n;}

ArManipInt& aSetRTab(int val) {return setupManipInt(ArchiveB::doSetRTab, val);}
ArchiveB& ArchiveB::doSetRTab(ArchiveB& n, int v) {n.setRTab(v);    return n;}


ArManipInt& aSetWidth(int val) {return setupManipInt(ArchiveB::doSetWidth, val);}
ArchiveB& ArchiveB::doSetWidth(ArchiveB& n, int v) {n.nmbr.width = v;  return n;}


ArManipInt& aSetPrec( int val) {return setupManipInt(ArchiveB::doSetPrec,  val);}
ArchiveB& ArchiveB::doSetPrec(ArchiveB& n, int v) {n.nmbr.prec  = v;  return n;}


ArManipInt& setupManipInt(ArManipInt::Func func, int val)
          {NewAlloc(ArManipInt);   ArManipInt* m = AllocNode;  m->set(func, val); return *m;}

ArManipDbl& setupManipDbl(ArManipDbl::Func func, double val)
          {NewAlloc(ArManipDbl);   ArManipDbl* m = AllocNode;  m->set(func, val); return *m;}

ArManipStg& setupManipStg(ArManipStg::Func func, TCchar* val)
          {NewAlloc(ArManipStg);   ArManipStg* m = AllocNode;  m->set(func, val); return *m;}



int ArchiveB::spaces(int nSpaces)
                {int i;   for (i = 0; i < nSpaces; i++) arLine.append(_T(' '));   return nSpaces;}




/////----------------

#if 0
ArchiveB& ArchiveB::operator << (NotePad& np) {
NtPdIter iter(np);
Note*    nt;

  arLine.clear();   nmbr.clear();

  for (nt = iter(); nt; nt = iter++) {
    if (nt->leftMgn  >= 0)   setLMargin(nt->leftMgn);
    if (nt->rightMgn >= 0)   setRMargin(nt->rightMgn);
    if (nt->clrTabs)         clrTabs();
    if (nt->noteTab.pos) {   if (nt->noteTab.right) setRTab(nt->noteTab.pos);
                             else                   setTab( nt->noteTab.pos);
                             }
    if (nt->tabSeen)         tab();
    if (nt->center)          center();
    if (nt->right)           right();
    if (nt->beginLine)       beginULine();
    if (!nt->line.isEmpty()) arLine.append(nt->line);
    if (nt->nmbr.typ)       {nmbr = nt->nmbr;  append(nmbr());}
    if (nt->endLine)         endULine();
    if (nt->crlf)            crlf();
    }

  flush();   return *this;
  }
#endif

