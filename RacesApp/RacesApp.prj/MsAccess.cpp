// MS Access Starting and Running for commands it does well...


#include "pch.h"
#include "MsAccess.h"
#include "AppFile.h"
#include "Executable.h"
#include "FileSrch.h"
#include "IniFileEx.h"


static TCchar* Sect   = _T("MsAccess");
static TCchar* ExeKey = _T("ExePath");

void MsAccess::compact(TCchar* path) {
String     exePath;
FileSrch   fileSrch;
Executable executable;

  if (!iniFile.read(Sect, ExeKey, exePath)) {

    AppFile appFile(_T("C:\\Program Files\\Microsoft*"));

    exePath = appFile.find(_T("*ACCESS*"));

    iniFile.write(Sect, ExeKey, exePath);
    }

  executable.start(3, exePath.str(), path, _T("/compact"));

  executable.wait();
  }

