// MS Access Starting and Running for commands it does well...


#include "pch.h"
#include "MsAccess.h"
#include "AppFile.h"
#include "Executable.h"
#include "FileSrch.h"




void MsAccess::compact(TCchar* path) {
AppFile    appFile(_T("C:\\Program Files\\Microsoft*"));
String     exePath;
FileSrch   fileSrch;
Executable executable;

  exePath = appFile.find(_T("*ACCESS*"));

  executable.start(3, exePath.str(), path, _T("/compact"));

  executable.wait();
  }

