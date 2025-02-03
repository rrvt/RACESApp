// RacesNew.h -- Template for a Dialog Box Application


#pragma once
#include "CDialogApp.h"


class RacesNew : public CDialogApp {
public:

UINT  m_nAppLook;

  RacesNew() noexcept;

public:

  virtual BOOL InitInstance();
  virtual int  ExitInstance();
  };


extern RacesNew theApp;
