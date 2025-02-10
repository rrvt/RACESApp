// Main Dialog Box


#pragma once
#include "AdrTbl.h"
#include "APicture.h"
#include "CtyTbl.h"
#include "CurMbr.h"
#include "EntTbl.h"
#include "MbrAvailability.h"
#include "MbrGeography.h"
#include "MbrStatus.h"
#include "MbrTbl.h"
#include "MyToolBar.h"
#include "Reports.h"
#include "Resource.h"
#include "StatusBar.h"
#include "RNUtility.h"
#include "WinPos.h"

class  StatusBar;
struct MbrInfo;
class  PathDlgDsc;


enum DlgSource {NilSrc, NewMbrSrc, CurMbrSrc, FmrMbrSrc, RtrMbrSrc};


// RacesAppDlg dialog

class RacesAppDlg : public CDialogEx {

DECLARE_DYNAMIC(RacesAppDlg)

String          helpPath;
MyToolBar       toolBar;
StatusBar       statusBar;

String          path;
bool            dbLoaded;
String          dbPath;

bool            isInitialized;

DlgSource       dlgSource;
bool            readOnly;


AdrRcd          nilAdr;
CtyRcd          nilCty;

MbrStatus       mbrStatus;
MbrAvailability mbrAvailability;
MbrGeography    mbrGeography;
APicture        mbrPic;

Reports reports;

public:

CComboBox  mbrListCtl;
CComboBox  statusCtl;
CComboBox  availabilityCtl;
CComboBox  RespGeographyCtl;
CStatic    recordIDCtl;
CStatic    pictureCtl;

CEdit      firstNameCtl;
CEdit      midInitialCtl;
CEdit      lastNameCtl;
CEdit      suffixCtl;
CEdit      callSignCtl;
CEdit      csExpDateCtl;
CButton    badgeOKCtl;
CStatic    badgeNoCtl;
CEdit      badgeExpDateCtl;

CEdit      mbrStreetAdrCtl;
CEdit      mbrUnitNoCtl;
CEdit      mbrCityCtl;
CEdit      mbrStateCtl;
CEdit      mbrZipCtl;
CEdit      mbrCellPhCtl;
CEdit      mbrLandlineCtl;
CButton    mbrZipOnlyCtl;
CEdit      mbrHomeZipCtl;

CEdit      mbrEmailCtl;
CButton    officerCtl;
CEdit      startDateCtl;
CEdit      dswDateCtl;
CEdit      responderDateCtl;

CEdit      iceFirstNameCtl;
CEdit      iceMidInitialCtl;
CEdit      iceLastNameCtl;
CEdit      iceEmailCtl;

CEdit      iceStreetAdrCtl;
CEdit      iceUnitNoCtl;
CEdit      iceCityCtl;
CEdit      iceStateCtl;
CEdit      iceZipCtl;
CEdit      iceCellPhCtl;
CEdit      iceLandlineCtl;

CEdit      emplNameCtl;
CEdit      emplEmailCtl;
CButton    emplZipOnlyCtl;
CEdit      emplCompanyZipCtl;

CEdit      emplStreetAdrCtl;
CEdit      emplUnitNoCtl;
CEdit      emplCityCtl;
CEdit      emplStateCtl;
CEdit      emplZipCtl;
CEdit      emplCellPhCtl;
CEdit      emplLandlineCtl;

CEdit      handHeldCtl;
CEdit      portMobileCtl;
CEdit      portPacketCtl;
CEdit      otherEquipCtl;
CEdit      multilingualCtl;
CEdit      otherCapCtl;

CEdit      limitationsCtl;
CEdit      commentsCtl;
CEdit      skillCertsCtl;
CEdit      eocCertCtl;
CStatic    picPathCtl;
CStatic    lastUpdateCtl;


           RacesAppDlg(TCchar* helpPth, CWnd* pParent = nullptr);
  virtual ~RacesAppDlg();

  virtual BOOL OnInitDialog();

// Dialog Data

#ifdef AFX_DESIGN_TIME
  enum { IDD = IDD_RacesApp };
#endif

protected:

  virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual void OnOK() { }

  DECLARE_MESSAGE_MAP()

private:

  void            setupToolBar();
  void            loadDatabase();
  void            loadMbrs(DlgSource src);

  bool            setEntity(EntRcd* ent, AdrRcd*& adr, CtyRcd*& cty);
  void            saveMember();

  void            saveNewMember();
  int             getMbrEntity();
  int             getICEEntity();
  int             getEmplEntity();
  int             addEntity(EntRcd& ent);
  int             addCity(CtyRcd&   cty);
  TCchar*         getTxtPh(int entId);

  int             getChk(CButton& ctl);

  bool            setField(String& fld, TCchar* tc);        // only if not equal
  bool            setField(int&   fld, int      v);

  void            setDate(CEdit& ctl, TCchar* txt) {ctl.SetWindowText(expandDate(txt));}
  void            setZip( CEdit& ctl, TCchar* txt) {ctl.SetWindowText(expandZip(txt));}
  void            setPhn( CEdit& ctl, TCchar* txt) {ctl.SetWindowText(expandPhone(txt));}

  void            initScreen();
  void            setLabels();
  void            clrLabels();

  void            clrLbl(CEdit& ctl, TCchar* txt)
                             {Cstring lbl;   ctl.GetWindowText(lbl);   if (lbl == txt) clear(ctl);}
  void            clrLbl(CStatic& ctl, TCchar* txt)
                             {Cstring lbl;   ctl.GetWindowText(lbl);   if (lbl == txt) clear(ctl);}


  String&         getToday();
  int             getNextBadgeNo();

  void            setTitle();
  void            setStatus(DlgSource src, bool rdOnly);
  void            setPath(TCchar* path);
  void            chkMbrPicture();


public:

  afx_msg void    onLoadDatabase();
  afx_msg void    onSelectMbr();
  afx_msg void    onNewMember();
  afx_msg void    onLoadCurMbrs() {loadMbrs(CurMbrSrc);}
  afx_msg void    onLoadFmrMbrs() {loadMbrs(FmrMbrSrc);}
  afx_msg void    onLoadRtrMbrs() {loadMbrs(RtrMbrSrc);}
  afx_msg void    onEditRecords();
  afx_msg void    onCheckList();

  afx_msg void    onExcelRpt()       {reports.excelRpt();}
  afx_msg void    onGoogleRpt()      {reports.googleRpt();}
  afx_msg void    onEverBridgeRpt()  {reports.everBridgeRpt();}
  afx_msg void    onCSBadgeRpt()     {reports.csBadgeRpt();}
  afx_msg void    onDateBadgeRpt()   {reports.dateBadgeRpt();}
  afx_msg void    onContactByNmRpt() {reports.contactNm();}
  afx_msg void    onContactByCSRpt() {reports.contactCS();}
  afx_msg void    onResponderCnts()  {reports.responderCnts();}
  afx_msg void    onCallSignList()   {reports.callSignList();}
  afx_msg void    onMemberIDs()      {reports.memberIDs();}



  afx_msg void    onOption05();
  afx_msg void    onOption06();
  afx_msg void    onOption07();
  afx_msg void    onOption08();
  afx_msg void    onOption09();

  afx_msg void    onHelp();
  afx_msg void    onUpdateDbExit();

  afx_msg int     OnCreate(LPCREATESTRUCT lpCreateStruct);
  afx_msg LRESULT OnResetToolBar(WPARAM wParam, LPARAM lParam);
  afx_msg void    onAbout();

  afx_msg void    OnMove(int x, int y);
  afx_msg void    OnSize(UINT nType, int cx, int cy);
  afx_msg BOOL    OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult);
  afx_msg void    onUpdateMbr();
  afx_msg void    onDispatch()  {toolBar.dispatch(ID_ReportMenu);}

  afx_msg void    onSanitizeDB();

  afx_msg void    onClearMbrfirstname();
  afx_msg void    onClearMbrMiddleInitial();
  afx_msg void    onClearMbrLastName();
  afx_msg void    onClearSuffix();

  afx_msg void    onClearMbrCallsign();
  afx_msg void    onClearCallSignExpDate();
  afx_msg void    onClearBadgeExpDate();
  afx_msg void    onClearMbrStreetAdr();
  afx_msg void    onClearMbrUnitNo();
  afx_msg void    onClearMbrCity();
  afx_msg void    onClearMbrState();
  afx_msg void    onClearMbrZip();
  afx_msg void    onLeaveMbrzip();
  afx_msg void    onClearMbrCellPh();
  afx_msg void    onLeaveMbrCellPh();
  afx_msg void    onClearMbrLandline();
  afx_msg void    onLeaveMbrlandline();
  afx_msg void    onClearMbrHomeZip();
  afx_msg void    onClearMbrEmail();
  afx_msg void    onClearStartDate();
  afx_msg void    onClearDSWDate();
  afx_msg void    onClearResponderDate();

  afx_msg void    onClearIceFirstName();
  afx_msg void    onClearIceMidInitial();
  afx_msg void    onClearIceLastName();
  afx_msg void    onLeaveIceName();
  afx_msg void    onClearIceEmail();
  afx_msg void    onClearIceStreetAdr();
  afx_msg void    onClearIceUnitNo();
  afx_msg void    onClearIceCity();
  afx_msg void    onClearIceState();
  afx_msg void    onClearIceZip();
  afx_msg void    onLeaveIceZip();
  afx_msg void    onClearIceCellPh();
  afx_msg void    onLeaveIceCellPh();
  afx_msg void    onClearIceLandline();
  afx_msg void    onLeaveICELandline();

  afx_msg void    onClearEmplName();
  afx_msg void    onClearEmplEmail();
  afx_msg void    onClearEmplStreetAdr();
  afx_msg void    onClearEmplUnitNo();
  afx_msg void    onClearEmplCity();
  afx_msg void    onClearEmplState();
  afx_msg void    onClearEmplZip();
  afx_msg void    onLeaveEmplZip();
  afx_msg void    onClearEmplCellPh();
  afx_msg void    onLeaveEmplCellPh();
  afx_msg void    onClearEmplLandline();
  afx_msg void    onLeaveEmplLandline();
  afx_msg void    onClearEmplZipOnly();
  afx_msg void    onClearEmplCompanyZip();
  afx_msg void    onFindICEAddr();
  afx_msg void    onFindICEZip();
  afx_msg void    onFindEmplAddr();
  afx_msg void    onFindEmplZip();
  afx_msg void    onPickPicPath();
  afx_msg void    onRemoveFmr();
};



///-------------------

#if 0
  afx_msg void    changeReady();

  afx_msg void    onTBChange(NMHDR* pNMHDR, LRESULT* pResult);

  afx_msg void    onDispatch();
  afx_msg void    onOption00();
  afx_msg void    onOption01();
  afx_msg void    onOption02();
  afx_msg void    onDispatch1();
  afx_msg void    onOption11();
  afx_msg void    onOption12();

  afx_msg void    onX();
  afx_msg void    onCboBxChange();
  afx_msg void    onCboBx1Change();

  afx_msg void    onTBEditBox();
#endif
  //  int             getMbrAddr();
  //  int             getMbrCity();
//  int             getICEAddr();
//  int             getICECity();
//  int             getEmplAddr();
//  int             getEmplCity();
#if 0
MbrInfo*        currentInfo;
MbrRcd*         mbrRcd;                         // Local copies of pointers
EntRcd*         mbrEnt;
EntRcd*         iceEnt;
EntRcd*         emplEnt;
bool            dirty;

MbrRcd          nilRcd;
EntRcd          nilEnt;
#endif
#if 0
  String          expandDate(TCchar* tc);                    // 010203 becomes 01/02/03
  String          compressDate(TCchar* cs);                // 01/02/03 becomes 010203
  String          expandPhone(TCchar* tc);                  // 4085551212 becomes 408.555.1212
  String          compressPhone(TCchar* tc);                // 408.555.1212 becomes 4085551212
  String          adjFrag(String& frag);
#endif

