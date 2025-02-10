// Report Base -- Operations used several places


#pragma once
#include "Archive.h"
#include "CSVOut.h"

class MbrRcd;
class EntRcd;
class AsnRcd;
class LocRcd;
class StsRcd;


class ReportBase {

String  csvPath;

public:

Archive ar;
CSVOut  csv;

  ReportBase(TCchar* path) : csvPath(path), ar(path, Archive::Write|Archive::Create), csv(ar)  { }
 ~ReportBase() { }

  void    memberHdr();
  void    callsignHdr();
  void    employerHdr();
  void    iceHdr();
  void    handHeldHdr();
  void    limitationsHdr();
  void    preferencesHdr();
  void    locationHdr();
  void    commentHdr();
  void    shirtSizeHdr();
  void    skillsHdr();

  void    putEntity(EntRcd* ent, MbrRcd* rcd = 0);
  void    putTxtPh(   MbrRcd& rcd);
  void    putDates(   MbrRcd& rcd);
  void    putHandHeld(MbrRcd& rcd);
  void    putAsn(     AsnRcd* asnRcd);
  void    putLoc(     LocRcd* locRcd);
  void    putSts(     StsRcd* stsRcd);
  void    putSkills(  MbrRcd& rcd);

  void    msgCount(int count);

private:

  ReportBase() : ar((TCchar*)0, 0), csv(*(Archive*)0) { }
  };

