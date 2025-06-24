// Fix Database Records


#pragma once


class FixDB {

public:

  FixDB() { }
 ~FixDB() { }

  int addr();

private:

  bool findEnt(uint adrId);
  };

