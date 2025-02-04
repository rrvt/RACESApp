// Prepare Entity Record


#include "pch.h"
#include "PrepEntRcd.h"
#include "CurMbr.h"
#include "MbrTbl.h"



// (408) 555-1212 becomes 4085551212 or
// 408.555.1212 becomes 4085551212 or
// 408-555-1212 becomes 4085551212 or combinations of "()", ' ', '.' & '-'

String PrepEntRcd::compressPhone(TCchar* tc) {
String s = tc;      s.trim();
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



void PrepEntRcd::setCtyRcd(CtyRcd* cty) {


  if (PrepCtyRcd::isDifferent(cty)) cty = PrepCtyRcd::add();

  rcd.cityStID = cty->getId();
  }


void PrepEntRcd::setAdrRcd(AdrRcd* adr) {

  if (PrepAdrRcd::isDifferent(adr)) adr = PrepAdrRcd::add();

  rcd.addrID = adr->getId();
  }


int PrepEntRcd::updateRcd(EntRcd* entRcd) {
int k = 0;
int no;

  if (rcd.middleInitial != entRcd->middleInitial)
                                              {entRcd->middleInitial = rcd.middleInitial;   k++;}
  if (rcd.firstName   != entRcd->firstName)   {entRcd->firstName     = rcd.firstName;       k++;}
  if (rcd.lastName    != entRcd->lastName)    {entRcd->lastName      = rcd.lastName;        k++;}
  if (rcd.eMail       != entRcd->eMail)       {entRcd->eMail         = rcd.eMail;           k++;}
  if (rcd.phone2      != entRcd->phone2)      {entRcd->phone2        = rcd.phone2;          k++;}
  if (rcd.phone1      != entRcd->phone1)      {entRcd->phone1        = rcd.phone1;          k++;}
  if (rcd.cityStID    != entRcd->cityStID)    {entRcd->cityStID      = rcd.cityStID;        k++;}
  if (rcd.addrID      != entRcd->addrID)      {entRcd->addrID        = rcd.addrID;          k++;}
  if (rcd.addrIsPO    != entRcd->addrIsPO)    {entRcd->addrIsPO      = rcd.addrIsPO;        k++;}
  if (rcd.locationZip != entRcd->locationZip) {entRcd->locationZip   = rcd.locationZip;     k++;}

  if (k) curMbr.setDirty(entRcd);

  no = noUsed(entRcd->getId());

  if (no == 1) update(entRcd);
  else         entRcd = curMbr.addEntTbl(rcd);

  return entRcd->getId();
  }


void PrepEntRcd::update(EntRcd* entRcd) {
  entRcd->firstName     = rcd.firstName;
  entRcd->middleInitial = rcd.middleInitial;
  entRcd->lastName      = rcd.lastName;
  entRcd->suffix        = rcd.suffix;
  entRcd->addrID        = rcd.addrID;
  entRcd->cityStID      = rcd.cityStID;
  entRcd->addrIsPO      = rcd.addrIsPO;
  entRcd->locationZip   = rcd.locationZip;
  entRcd->eMail         = rcd.eMail;
  entRcd->phone1        = rcd.phone1;
  entRcd->phone2        = rcd.phone2;
  }


int PrepEntRcd::noUsed(int id) {
MbrIter iter(mbrTbl);
MbrRcd* rcd;
int     count;

  for (count = 0, rcd = iter(); rcd; rcd = iter++)
         if (rcd->mbrEntityID == id || rcd->emplEntityID == id || rcd->iCE_EntityID == id) count++;

  return count;
  }



