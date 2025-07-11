// RacesApp.h -- Template for a Dialog Box Application


#include "pch.h"
#include "RacesApp.h"
#include "AddrList.h"
#include "Database.h"
#include "IniFileEx.h"
#include "MemberList.h"
#include "RacesAppDlg.h"
#include "Utilities.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


RacesApp   theApp;                          // The one and only RacesApp object
IniFileEx  iniFile(theApp);
Database   database;
AccessDB   accessDB;
AdrTbl     adrTbl;
AsnTbl     asnTbl;
CtyTbl     ctyTbl;
EntTbl     entTbl;
LocTbl     locTbl;
MbrTbl     mbrTbl;
StsTbl     stsTbl;
MemberList memberList;
AddrList   addrList;                        // The one Address List sorted by address1
Utilities  utl;

// RacesApp construction

RacesApp::RacesApp() noexcept : CDialogApp(this) { }


// RacesApp initialization -- Start the MFC Dialog Box

BOOL RacesApp::InitInstance() {
RacesAppDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath);

  dlg.DoModal();

  m_pMainWnd = 0;   return 0;
  }


int RacesApp::ExitInstance() {clearLibUtilities();   return CDialogApp::ExitInstance();}

