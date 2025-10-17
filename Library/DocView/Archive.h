// Archive for Doc/View Apps


#pragma once
#include "ArchiveB.h"



class Archive : public ArchiveB {
public:

  Archive(TCchar* fileName, int mode) : ArchiveB(fileName, mode) { }
  Archive(String& fileName, int mode) : ArchiveB(fileName, mode) { }
  Archive(void*   arbObj,   int mode) : ArchiveB(arbObj,   mode) { }


  ArchiveB& operator << (NotePad& np);
  };

