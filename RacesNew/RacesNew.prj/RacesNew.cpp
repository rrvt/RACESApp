// RacesNew.h -- Template for a Dialog Box Application


#include "pch.h"
#include "RacesNew.h"
#include "RacesNewDlg.h"
#include "IniFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


RacesNew theApp;                         // The one and only RacesNew object
IniFile   iniFile;


// RacesNew construction

RacesNew::RacesNew() noexcept : CDialogApp(this) { }


// RacesNew initialization -- Start the MFC Dialog Box

BOOL RacesNew::InitInstance() {
RacesNewDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  dlg.DoModal();

  m_pMainWnd = 0;   return 0;
  }


int RacesNew::ExitInstance() {return CWinApp::ExitInstance();}

