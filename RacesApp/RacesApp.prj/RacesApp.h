// RacesApp.h -- Template for a Dialog Box Application


#pragma once
#include "CDialogApp.h"


class RacesApp : public CDialogApp {
public:

UINT  m_nAppLook;

  RacesApp() noexcept;

public:

  virtual BOOL InitInstance();
  virtual int  ExitInstance();
  };


extern RacesApp theApp;
