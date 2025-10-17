// XML Parser -- Data goes into the XMLstore (see XMLstore.h)


#pragma once
#include "ArchiveB.h"

class XMLstore;


enum XMLType {NilTag, DeclTag, ElementTag, StartTag, EndTag, AttribTag};



class XMLparser {
XMLstore& xmlStore;

TCchar* p;
public:

  XMLparser(XMLstore& store) : xmlStore(store) { }
 ~XMLparser() { }

  void input(ArchiveB& ar);
  void output(ArchiveB& ar);

private:

  bool    readLine(ArchiveB& ar, String& s);
  XMLType getType(String& s, String& tag);

  XMLparser() : xmlStore(*(XMLstore*)0) { }
  };

