// A little history class for real time data collection


#include "pch.h"
#include "History.h"
#include "FileIO.h"
#include "GetPathDlg.h"

#include "MessageBox.h"


#if 0
History::History()  {
#if 0
int    eData = (int)&data[128] + sizeof(HistData);
String s;   s.format(_T("History (0x%08X, 0x%08X"), &data[0], eData);
messageBox(s);
#endif
  }


History::~History() { }
#endif

void History::saveData() {
PathDlgDsc dsc;
String     path;
FileIO     file;
HistIter   iter(*this);
HistData*  h;

  if (!getSaveAsPathDlg(dsc(_T("History"), _T("History"), _T("txt"), _T("*.txt")), path)) return;

  if (!file.open(path, FileIO::Write | FileIO::Create)) return;

  for (h = iter(); h; h = iter++) h->output(file);
  }


void HistData::output(FileIO& file) {
String s;

  s.format(_T("ID: %03i"), id);                 file.write(s);
  s.format(_T("   Flags:  0x%08x"), flags);     file.write(s);
  file.crlf();
  }

