// RacesApp.h -- Template for a Dialog Box Application


#include "pch.h"
#include "RacesApp.h"
#include "RacesAppDlg.h"
#include "IniFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


RacesApp theApp;                         // The one and only RacesApp object
IniFile   iniFile;


// RacesApp construction

RacesApp::RacesApp() noexcept : CDialogApp(this) { }


// RacesApp initialization -- Start the MFC Dialog Box

BOOL RacesApp::InitInstance() {
RacesAppDlg dlg(m_pszHelpFilePath);

  CWinApp::InitInstance();

  iniFile.setAppDataPath(m_pszHelpFilePath, *this);

  dlg.DoModal();

  m_pMainWnd = 0;   return 0;
  }


int RacesApp::ExitInstance() {return CWinApp::ExitInstance();}

