// Archive for Doc/View Apps


#include "pch.h"
#include "Archive.h"
#include "NotePad.h"


ArchiveB& Archive::operator << (NotePad& np) {
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




