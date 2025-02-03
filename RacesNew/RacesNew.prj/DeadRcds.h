// Dead Record Removal


#pragma once
#include "Archive.h"
#include "CSVOut.h"


class DeadRcds {

String  csvPath;
Archive ar;
CSVOut  csv;

public:

  DeadRcds(TCchar* pathOut) : csvPath(pathOut), ar(csvPath, Archive::Write|Archive::Create),
                                                                                        csv(ar) { }
 ~DeadRcds() { }

  int fix();

private:

  int  removeDeadMemberRcds();
  int  removeDeadEntityRcds();
  bool entityRcdNeeded(long id);
  int  removeDeadAddrRcds();
  bool addrRcdNeeded(long id);
  int  removeDeadCityRcds();
  bool cityRcdNeeded(long id);
  };

