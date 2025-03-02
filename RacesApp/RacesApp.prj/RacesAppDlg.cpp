// RacesAppDlg.cpp : implementation file
//

#include "pch.h"
#include "RacesAppDlg.h"
#include "AboutDlg.h"
#include "AddrList.h"
#include "ChkListDlg.h"
#include "Database.h"
#include "Date.h"
#include "DeadRcds.h"
#include "GetPathDlg.h"
#include "History.h"
#include "IniFile.h"
#include "MbrBadgeNo.h"
#include "MemberList.h"
#include "MessageBox.h"
#include "PrepEntRcd.h"
#include "Utility.h"
#include "SaveRcdDlg.h"
#include "SearchDlg.h"
#include "StatusBar.h"
#include "ZipList.h"


static TCchar* GlobalSect   = _T("Global");
static TCchar* DBFileKey    = _T("DBfile");
static TCchar* ApplProcdKey = _T("ApplProcd");
static TCchar* PictureKey   = _T("Picture");
static TCchar* GroupsKey    = _T("GroupsIO");
static TCchar* TrainingKey  = _T("Training");


IMPLEMENT_DYNAMIC(RacesAppDlg, CDialogEx)



RacesAppDlg::RacesAppDlg(TCchar* helpPth, CWnd* pParent) : CDialogEx(IDD_RacesApp, pParent),
                                helpPath(helpPth), toolBar(), statusBar(), dbLoaded(false),
                                isInitialized(false), dlgSource(NilSrc), readOnly(false),
                                mbrStatus(statusCtl),
                                mbrAvailability(availabilityCtl), mbrGeography(RespGeographyCtl),
                                mbrPic(pictureCtl, *this), srch(0) {}


RacesAppDlg::~RacesAppDlg() {winPos.~WinPos();}                             //deleteCtl.CleanUp();




BEGIN_MESSAGE_MAP(RacesAppDlg, CDialogEx)
  ON_COMMAND(      ID_LoadDatabase,      &onLoadDatabase)
  ON_COMMAND(      ID_NewMember,         &onNewMember)
  ON_COMMAND(      ID_LoadCurMbrs,       &onLoadCurMbrs)
  ON_COMMAND(      ID_LoadFmrMbrs,       &onLoadFmrMbrs)
  ON_COMMAND(      ID_EditRecords,       &onEditRecords)
  ON_CBN_SELCHANGE(IDC_MemberList,       &onSelectMbr)
  ON_COMMAND(      ID_CheckList,         &onCheckList)

  ON_CBN_SELCHANGE(ID_ReportMenu,        &onDispatch)         // Send Command Message with ID_...
  ON_COMMAND(      ID_ExcelReport,       &onExcelRpt)
  ON_COMMAND(      ID_GoogleRpt,         &onGoogleRpt)
  ON_COMMAND(      ID_EverBridgeRpt,     &onEverBridgeRpt)
  ON_COMMAND(      ID_CSBadgeRpt,        &onCSBadgeRpt)
  ON_COMMAND(      ID_DateBadgeRpt,      &onDateBadgeRpt)
  ON_COMMAND(      ID_ContactByNm,       &onContactByNmRpt)
  ON_COMMAND(      ID_ContactByCS,       &onContactByCSRpt)
  ON_COMMAND(      ID_ResponderCnts,     &onResponderCnts)
  ON_COMMAND(      ID_CallSignList,      &onCallSignList)
  ON_COMMAND(      ID_MemberIDs,         &onMemberIDs)
  ON_COMMAND(      ID_SuffixList,        &onSuffixList)
  ON_COMMAND(      ID_FormerMbrs,        &onFormerList)

  ON_COMMAND(      ID_LoadRtrMbrs,       &onLoadRtrMbrs)
  ON_COMMAND(      ID_RemoveFmr,         &onRemoveFmr)

  ON_COMMAND(      ID_SanitizeDB,        &onSanitizeDB)

  ON_COMMAND(      ID_IntroHelp,         &onHelp)
  ON_COMMAND(      ID_About,             &onAbout)
  ON_COMMAND(      ID_UpdateDBExit,      &onUpdateDbExit)

  ON_COMMAND(      ID_Left,              &onLeft)
  ON_COMMAND(      ID_Find,              &onFind)
  ON_COMMAND(      ID_FindNext,          &onFindNext)
  ON_COMMAND(      ID_Right,             &onRight)

  ON_BN_CLICKED(   IDC_PickPicPath,      &onPickPicPath)

  ON_EN_SETFOCUS(  IDC_MbrFirstName,     &onClearMbrfirstname)
  ON_EN_SETFOCUS(  IDC_MbrMiddleInitial, &onClearMbrMiddleInitial)
  ON_EN_SETFOCUS(  IDC_MbrLastName,      &onClearMbrLastName)
  ON_EN_SETFOCUS(  IDC_Suffix,           &onClearSuffix)

  ON_EN_SETFOCUS(  IDC_MbrCallsign,      &onClearMbrCallsign)
  ON_EN_SETFOCUS(  IDC_CallSignExpDate,  &onClearCallSignExpDate)
  ON_EN_SETFOCUS(  IDC_BadgeExpDate,     &onClearBadgeExpDate)
  ON_CBN_SETFOCUS( IDC_MbrStreetAdr,     &onStartMbrStreetAdr)
  ON_CBN_SELCHANGE(IDC_MbrStreetAdr,     &onSelectMbrStreetAdr)
  ON_CBN_KILLFOCUS(IDC_MbrStreetAdr,     &onLeaveMbrStreetAdr)
  ON_EN_SETFOCUS(  IDC_MbrUnitNo,        &onClearMbrUnitNo)
  ON_EN_KILLFOCUS( IDC_MbrUnitNo,        &onLeaveMbrUnitNo)
  ON_EN_SETFOCUS(  IDC_MbrCity,          &onClearMbrCity)
  ON_EN_SETFOCUS(  IDC_MbrState,         &onClearMbrState)
  ON_CBN_SETFOCUS( IDC_MbrZip,           &onStartMbrZip)
  ON_CBN_SELCHANGE(IDC_MbrZip,           &onSelectMbrzip)
  ON_CBN_KILLFOCUS(IDC_MbrZip,           &onLeaveMbrZip)
  ON_EN_SETFOCUS(  IDC_MbrCellPh,        &onClearMbrCellPh)
  ON_EN_SETFOCUS(  IDC_MbrLandline,      &onClearMbrLandline)
  ON_CBN_SETFOCUS( IDC_MbrHomeZip,       &onStartMbrHomeZip)
  ON_CBN_SELCHANGE(IDC_MbrHomeZip,       &onSelectMbrHomeZip)
  ON_CBN_KILLFOCUS(IDC_MbrHomeZip,       &onLeaveMbrHomeZip)
  ON_EN_SETFOCUS(  IDC_MbrEmail,         &onClearMbrEmail)
  ON_EN_SETFOCUS(  IDC_StartDate,        &onClearStartDate)
  ON_EN_SETFOCUS(  IDC_DSWDate,          &onClearDSWDate)
  ON_EN_SETFOCUS(  IDC_ResponderDate,    &onClearResponderDate)

  ON_EN_SETFOCUS(  IDC_ICEFirstName,     &onClearIceFirstName )
  ON_EN_SETFOCUS(  IDC_ICEMiddleInitial, &onClearIceMidInitial)
  ON_EN_SETFOCUS(  IDC_ICELastName,      &onClearIceLastName)
  ON_EN_KILLFOCUS( IDC_ICELastName,      &onLeaveIceName)
  ON_EN_SETFOCUS(  IDC_ICEeMail,         &onClearIceEmail)
  ON_CBN_SETFOCUS( IDC_ICEStreetAdr,     &onStartIceStreetAdr)
  ON_CBN_SELCHANGE(IDC_ICEStreetAdr,     &onSelectIceStreetAdr)
  ON_CBN_KILLFOCUS(IDC_ICEStreetAdr,     &onLeaveIceStreetAdr)
  ON_EN_SETFOCUS(  IDC_ICEUnitNo,        &onClearIceUnitNo)
  ON_EN_KILLFOCUS( IDC_ICEUnitNo,        &onLeaveIceUnitNo)
  ON_EN_SETFOCUS(  IDC_ICECity,          &onClearIceCity)
  ON_EN_SETFOCUS(  IDC_ICEState,         &onClearIceState)
  ON_CBN_SETFOCUS( IDC_ICEZip,           &onStartIceZip)
  ON_CBN_SELCHANGE(IDC_ICEZip,           &onSelectIceZip)
  ON_CBN_KILLFOCUS(IDC_ICEZip,           &onLeaveIceZip)
  ON_EN_SETFOCUS(  IDC_ICECellPh,        &onClearIceCellPh)
  ON_EN_SETFOCUS(  IDC_ICELandline,      &onClearIceLandline)

  ON_EN_SETFOCUS(  IDC_EmplName,         &onClearEmplName)
  ON_EN_SETFOCUS(  IDC_EmplEmail,        &onClearEmplEmail)
  ON_CBN_SETFOCUS( IDC_EmplStreetAdr,    &onStartEmplStreetAdr)
  ON_CBN_SELCHANGE(IDC_EmplStreetAdr,    &onSelectEmplStreetAdr)
  ON_CBN_KILLFOCUS(IDC_EmplStreetAdr,    &onLeaveEmplStreetAdr)
  ON_EN_SETFOCUS(  IDC_EmplUnitNo,       &onClearEmplUnitNo)
  ON_EN_KILLFOCUS( IDC_EmplUnitNo,       &onLeaveEmplUnitNo)
  ON_EN_SETFOCUS(  IDC_EmplCity,         &onClearEmplCity)
  ON_EN_SETFOCUS(  IDC_EmplState,        &onClearEmplState)
  ON_CBN_SETFOCUS( IDC_EmplZip,          &onStartEmplZip)
  ON_CBN_SELCHANGE(IDC_EmplZip,          &onSelectEmplZip)
  ON_CBN_KILLFOCUS(IDC_EmplZip,          &onLeaveEmplZip)
  ON_EN_SETFOCUS(  IDC_EmplCellPh,       &onClearEmplCellPh)
  ON_EN_SETFOCUS(  IDC_EmplLandline,     &onClearEmplLandline)
  ON_CBN_SETFOCUS( IDC_EmplCompanyZip,   &onStartEmplCompanyZip)
  ON_CBN_SELCHANGE(IDC_EmplCompanyZip,   &onSelectEmplCompanyZip)
  ON_CBN_KILLFOCUS(IDC_EmplCompanyZip,   &onLeaveEmplCompanyZip)

  ON_EN_KILLFOCUS( IDC_MbrCellPh,        &onLeaveMbrCellPh)
  ON_EN_KILLFOCUS( IDC_MbrLandline,      &onLeaveMbrlandline)
  ON_EN_KILLFOCUS( IDC_ICECellPh,        &onLeaveIceCellPh)
  ON_EN_KILLFOCUS( IDC_ICELandline,      &onLeaveICELandline)
  ON_EN_KILLFOCUS( IDC_EmplCellPh,       &onLeaveEmplCellPh)
  ON_EN_KILLFOCUS( IDC_EmplLandline,     &onLeaveEmplLandline)

  ON_WM_CREATE()
  ON_REGISTERED_MESSAGE(AFX_WM_RESETTOOLBAR, &OnResetToolBar)
  ON_NOTIFY_EX(         TTN_NEEDTEXT, 0,     &OnTtnNeedText)         // Do ToolTips
  ON_WM_MOVE()
  ON_WM_SIZE()
END_MESSAGE_MAP()


void RacesAppDlg::DoDataExchange(CDataExchange* pDX) {
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_MemberList, mbrListCtl);
    DDX_Control(pDX, IDC_RecordID, recordIDCtl);
    DDX_Control(pDX, IDC_MbrFirstName, firstNameCtl);
    DDX_Control(pDX, IDC_MbrMiddleInitial, midInitialCtl);
    DDX_Control(pDX, IDC_MbrLastName, lastNameCtl);
    DDX_Control(pDX, IDC_Suffix, suffixCtl);
    DDX_Control(pDX, IDC_MbrCallsign, callSignCtl);
    DDX_Control(pDX, IDC_CallSignExpDate, csExpDateCtl);
    DDX_Control(pDX, IDC_BadgeOK, badgeOKCtl);
    DDX_Control(pDX, IDC_BadgeNo, badgeNoCtl);
    DDX_Control(pDX, IDC_BadgeExpDate, badgeExpDateCtl);
    DDX_Control(pDX, IDC_MbrStreetAdr, mbrStreetAdrCtl);
    DDX_Control(pDX, IDC_MbrUnitNo, mbrUnitNoCtl);
    DDX_Control(pDX, IDC_MbrCity, mbrCityCtl);
    DDX_Control(pDX, IDC_MbrState, mbrStateCtl);
    DDX_Control(pDX, IDC_MbrZip, mbrZipCtl);
    DDX_Control(pDX, IDC_MbrCellPh, mbrCellPhCtl);
    DDX_Control(pDX, IDC_MbrLandline, mbrLandlineCtl);
    DDX_Control(pDX, IDC_MbrZipOnly, mbrZipOnlyCtl);
    DDX_Control(pDX, IDC_MbrHomeZip, mbrHomeZipCtl);
    DDX_Control(pDX, IDC_MbrEmail, mbrEmailCtl);
    DDX_Control(pDX, IDC_StartDate, startDateCtl);
    DDX_Control(pDX, IDC_DSWDate, dswDateCtl);
    DDX_Control(pDX, IDC_ResponderDate, responderDateCtl);
    DDX_Control(pDX, IDC_ICEFirstName, iceFirstNameCtl);
    DDX_Control(pDX, IDC_ICEMiddleInitial, iceMidInitialCtl);
    DDX_Control(pDX, IDC_ICELastName, iceLastNameCtl);
    DDX_Control(pDX, IDC_ICEeMail, iceEmailCtl);
    DDX_Control(pDX, IDC_ICEStreetAdr, iceStreetAdrCtl);
    DDX_Control(pDX, IDC_ICEUnitNo, iceUnitNoCtl);
    DDX_Control(pDX, IDC_ICECity, iceCityCtl);
    DDX_Control(pDX, IDC_ICEState, iceStateCtl);
    DDX_Control(pDX, IDC_ICEZip, iceZipCtl);
    DDX_Control(pDX, IDC_ICECellPh, iceCellPhCtl);
    DDX_Control(pDX, IDC_ICELandline, iceLandlineCtl);
    DDX_Control(pDX, IDC_EmplName, emplNameCtl);
    DDX_Control(pDX, IDC_EmplEmail, emplEmailCtl);
    DDX_Control(pDX, IDC_EmplStreetAdr, emplStreetAdrCtl);
    DDX_Control(pDX, IDC_EmplUnitNo, emplUnitNoCtl);
    DDX_Control(pDX, IDC_EmplCity, emplCityCtl);
    DDX_Control(pDX, IDC_EmplState, emplStateCtl);
    DDX_Control(pDX, IDC_EmplZip, emplZipCtl);
    DDX_Control(pDX, IDC_EmplCellPh, emplCellPhCtl);
    DDX_Control(pDX, IDC_EmplLandline, emplLandlineCtl);
    DDX_Control(pDX, IDC_EmplZipOnly, emplZipOnlyCtl);
    DDX_Control(pDX, IDC_EmplCompanyZip, emplCmpZipCtl);
    DDX_Control(pDX, IDC_HandHeld, handHeldCtl);
    DDX_Control(pDX, IDC_PortMobile, portMobileCtl);
    DDX_Control(pDX, IDC_PortPacket, portPacketCtl);
    DDX_Control(pDX, IDC_OtherEquip, otherEquipCtl);
    DDX_Control(pDX, IDC_Multilingual, multilingualCtl);
    DDX_Control(pDX, IDC_OtherCapabilities, otherCapCtl);
    DDX_Control(pDX, IDC_Limitations, limitationsCtl);
    DDX_Control(pDX, IDC_Comments, commentsCtl);
    DDX_Control(pDX, IDC_SkillCerts, skillCertsCtl);
    DDX_Control(pDX, IDC_EOCCert, eocCertCtl);
    DDX_Control(pDX, IDC_LastUpdate, lastUpdateCtl);
    DDX_Control(pDX, IDC_Officer, officerCtl);
    DDX_Control(pDX, IDC_MbrStatus, statusCtl);
    DDX_Control(pDX, IDC_Geography, RespGeographyCtl);
    DDX_Control(pDX, IDC_Availability, availabilityCtl);
    DDX_Control(pDX, IDC_Picture, pictureCtl);
    DDX_Control(pDX, IDC_PicPath, picPathCtl);
}


int RacesAppDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) {

  if (CDialogEx::OnCreate(lpCreateStruct) == -1) return -1;

  return 0;
  }


BOOL RacesAppDlg::OnInitDialog() {
CRect winRect;

  CDialogEx::OnInitDialog();

  GetWindowRect(&winRect);   winPos.setDLUToPxls(winRect, DlgWidth, DlgDepth);

  if (!toolBar.create(this, IDR_TOOLBAR)) return false;

  SetBackgroundColor(RGB(255,255,255));               // toolBar.move(winRect);

  if (!statusBar.create(this, IDC_StatusBar)) return false;

  statusBar.setReady();

  winPos.initialPos(this, winRect);   toolBar.move(winRect);   statusBar.move(winRect);

  iniFile.read(GlobalSect, DBFileKey, path);   loadDatabase();


  isInitialized = true;  setTitle();    readOnly = true;

  return true;
  }


void RacesAppDlg::onLoadDatabase() {
PathDlgDsc dsc(_T("Database"), 0, _T("accdb"), _T("*.accdb"));

  if (!getOpenDlg(dsc, path)) return;

  iniFile.writeString(GlobalSect, DBFileKey, path);

  loadDatabase();   curMbr.initialize();
  }


void RacesAppDlg::loadDatabase() {

  dbLoaded = database.load(path);

  if (dbLoaded) {
    dbPath = path;   mbrPic.setRootPath(path);

    memberList.create();   mbrStatus.load();   mbrAvailability.load();

    mbrGeography.load();   addrList.load();    zipList.load();

    onLoadCurMbrs();       setPath(dbPath);    initScreen();
    }
  }


void RacesAppDlg::onNewMember() {
String          s;
MbrBadgeNo      mbrBadgeNo;

  updateMbr();

  reset(mbrListCtl);    curMbr.initialize();   setTitle();

  initScreen();

  s.format(_T("%i"), mbrBadgeNo.findNext());   set(badgeNoCtl, s);

  mbrStatus.setDefault();   mbrAvailability.setDefault();   mbrGeography.setDefault();

  set(startDateCtl, getTodayExpd());

  setStatus(NewMbrSrc, false);

  firstNameCtl.SetFocus();    setFirstName();   firstNameCtl.SetSel(0, -1);
  }


// onLoadCurMbrs, onLoadFmrMbrs, onLoadRtrMbrs

void RacesAppDlg::loadMbrs(DlgSource src) {
MbrListIter iter(memberList);
MbrInfo*    info;
MbrRcd*     mbrRcd;
EntRcd*     mbrEnt;
StsRcd*     stsRcd;
String      id;
int         indx;

  CDialogEx::OnInitDialog();   mbrListCtl.ResetContent();

  for (info = iter(); info; info = iter++) {
    mbrRcd = info->mbrRcd;
    mbrEnt = info->mbrEnt;
    stsRcd = info->stsRcd;

    switch (src) {
      case CurMbrSrc: if (stsRcd->abbreviation == _T("Fmr")) continue;   break;
      case FmrMbrSrc: if (stsRcd->abbreviation != _T("Fmr")) continue;   break;
      case RtrMbrSrc: if (stsRcd->abbreviation != _T("Fmr")) continue;
                      if (!isEarlier(mbrRcd->updateDate))    continue;   break;
      }

    id = mbrEnt->lastName + _T(", ") + mbrEnt->firstName + _T(", ") + mbrRcd->callSign;

    indx = mbrListCtl.AddString(id);    if (indx < 0) continue;

    mbrListCtl.SetItemDataPtr(indx, info);
    }

  setStatus(src, true);
  }


void RacesAppDlg::onEditRecords() {false;   setStatus(dlgSource, false);}



void RacesAppDlg::onLeft() {setSrch();   if (srch->left()) onSelectMbr();}


void RacesAppDlg::onFind() {
SearchDlg dlg;

  if (dlg.DoModal() == IDOK) {

    setSrch();

    srch->wholeWord     = dlg.wholeWord;
    srch->curFldOnly    = dlg.curFldOnly;
    srch->caseSensitive = dlg.caseSensitive;
    srch->attributes    = dlg.attributes;

    if (srch->find(dlg.target)) {onSelectMbr();   setCtlFocus();}
    }
  }


void RacesAppDlg::onFindNext()
                            {setSrch();   if (srch->findNext()) {onSelectMbr();   setCtlFocus();}}


void RacesAppDlg::setCtlFocus() {
int   id  = srch->getFieldID();
CWnd* wnd = GetDlgItem(id);

  if (wnd) wnd->SetFocus();
  }


void RacesAppDlg::onRight() {setSrch();   if (srch->right()) onSelectMbr();}


void RacesAppDlg::onSelectMbr() {
int             indx = mbrListCtl.GetCurSel();    if (indx < 0) return;
AdrRcd*         adrRcd;
CtyRcd*         ctyRcd;
String          tgt;

  updateMbr();

  setLabels();   mbrPic.clear();

  if (!curMbr.set((MbrInfo*)mbrListCtl.GetItemDataPtr(indx))) return;

  mbrStatus.set(curMbr.rcd);
  mbrAvailability.set(curMbr.rcd);
  mbrGeography.set(curMbr.rcd);

  set(recordIDCtl,     get(curMbr.rcd->getId()));
  set(firstNameCtl,    curMbr.mbr->firstName);
  set(midInitialCtl,   curMbr.mbr->middleInitial);
  set(lastNameCtl,     curMbr.mbr->lastName);
  set(suffixCtl,       curMbr.mbr->suffix);
  set(callSignCtl,     curMbr.rcd->callSign);
  set(csExpDateCtl,    expandDate(curMbr.rcd->fCCExpiration));
  set(badgeOKCtl,      curMbr.rcd->badgeOK);
  set(badgeNoCtl,      get(curMbr.rcd->badgeNumber));
  set(badgeExpDateCtl, expandDate(curMbr.rcd->badgeExpDate));

  if (!setEntity(curMbr.mbr, adrRcd, ctyRcd)) return;

  set(mbrStreetAdrCtl,        adrRcd->address1);
  set(mbrUnitNoCtl,           adrRcd->address2);
  set(mbrCityCtl,             ctyRcd->city);
  set(mbrStateCtl,            ctyRcd->state);
  set(mbrZipCtl,              expandZip(ctyRcd->zip));
  set(mbrCellPhCtl,           expandPhone(curMbr.mbr->phone2));
  set(mbrLandlineCtl,         expandPhone(curMbr.mbr->phone1));
  set(mbrZipOnlyCtl,          curMbr.mbr->addrIsPO);
  set(mbrHomeZipCtl,          expandZip(curMbr.mbr->locationZip));

  set(mbrEmailCtl,            curMbr.mbr->eMail);
  set(officerCtl,             curMbr.rcd->isOfficer);
  set(startDateCtl,           expandDate(curMbr.rcd->startDate));
  set(dswDateCtl,             expandDate(curMbr.rcd->dSWDate));
  set(responderDateCtl,       expandDate(curMbr.rcd->responder));

  if (setEntity(curMbr.ice, adrRcd, ctyRcd)) {
    set(iceFirstNameCtl,      curMbr.ice->firstName);
    set(iceMidInitialCtl,     curMbr.ice->middleInitial);
    set(iceLastNameCtl,       curMbr.ice->lastName);
    set(iceEmailCtl,          curMbr.ice->eMail);
    set(iceStreetAdrCtl,      adrRcd->address1);
    set(iceUnitNoCtl,         adrRcd->address2);

    set(iceCityCtl,           ctyRcd->city);
    set(iceStateCtl,          ctyRcd->state);
    set(iceZipCtl,            expandZip(ctyRcd->zip));
    set(iceCellPhCtl,         expandPhone(curMbr.ice->phone2));
    set(iceLandlineCtl,       expandPhone(curMbr.ice->phone1));
    }

  if (setEntity(curMbr.empl, adrRcd, ctyRcd)) {
    set(emplNameCtl,            curMbr.empl->firstName);
    set(emplEmailCtl,           curMbr.empl->eMail);
    set(emplStreetAdrCtl,       adrRcd->address1);
    set(emplUnitNoCtl,          adrRcd->address2);
    set(emplCityCtl,            ctyRcd->city);
    set(emplStateCtl,           ctyRcd->state);
    set(emplZipCtl,             expandZip(ctyRcd->zip));
    set(emplCellPhCtl,          expandPhone(curMbr.empl->phone2));
    set(emplLandlineCtl,        expandPhone(curMbr.empl->phone1));
    set(emplZipOnlyCtl,         curMbr.empl->addrIsPO);
    set(emplCmpZipCtl,          expandZip(curMbr.empl->locationZip));
    }
  set(handHeldCtl,              curMbr.rcd->handHeld);
  set(portMobileCtl,            curMbr.rcd->portMobile);
  set(portPacketCtl,            curMbr.rcd->portPacket);
  set(otherEquipCtl,            curMbr.rcd->otherEquip);
  set(multilingualCtl,          curMbr.rcd->multilingual);
  set(otherCapCtl,              curMbr.rcd->otherCapabilities);
  set(limitationsCtl,           curMbr.rcd->limitations);
  set(commentsCtl,              curMbr.rcd->comments);
  set(skillCertsCtl,            curMbr.rcd->skillCertifications);
  set(eocCertCtl,               curMbr.rcd->eOC_Certifications);

  set(picPathCtl,               curMbr.rcd->image);

  set(lastUpdateCtl,            expandDate(curMbr.rcd->updateDate));

  mbrPic.set(curMbr.rcd->image);   mbrPic.set();

  setStatus(dlgSource, true);   setTitle();
  }


void RacesAppDlg::onCheckList() {
ChkListDlg dlg;
String     sect;

  if (dlgSource == NilSrc) return;

//  sect = curMbr.ent->firstName + _T(' ') + curMbr.ent->lastName + _T(", ") + mbrRcd->callSign;
  sect = curMbr.getIdent();

  dlg.nameCallSign = sect;
  iniFile.read(sect, ApplProcdKey, dlg.applicationProc, false);
  iniFile.read(sect, PictureKey,   dlg.picture,         false);
  iniFile.read(sect, GroupsKey,    dlg.groupsIO,        false);
  iniFile.read(sect, TrainingKey,  dlg.trainingIntro,   false);

  if (dlg.DoModal() == IDOK) {
    iniFile.write(sect, ApplProcdKey, dlg.applicationProc);
    iniFile.write(sect, PictureKey,   dlg.picture);
    iniFile.write(sect, GroupsKey,    dlg.groupsIO);
    iniFile.write(sect, TrainingKey,  dlg.trainingIntro);
    }
  }

void RacesAppDlg::updateMbr() {
SaveRcdDlg dlg;

  if (!curMbr.isModified()) return;

  dlg.editable = !readOnly;   if (readOnly && dlg.DoModal() != IDOK) return;

  readOnly = !dlg.editable;

  switch (dlgSource) {
    case NewMbrSrc    : saveNewMember(); break;
    case CurMbrSrc    :
    case FmrMbrSrc    :
    case RtrMbrSrc    : saveMember();    break;
    case NilSrc       :
    default           : break;
    }
  curMbr.resetModified();
  }


void RacesAppDlg::onRemoveFmr() {
String s;

  if (dlgSource != RtrMbrSrc || !curMbr.rcd || !curMbr.mbr) return;

  s  = _T("Delete: ") + curMbr.getIdent();    //  ent->firstName + _T(' ') + curMbr.ent->lastName;
                                              //  s += _T(", ") + curMbr.rcd->callSign;

  if (msgYesNoBox(s) == IDYES) {curMbr.removeMbr();   messageBox(_T("Deleting"));}
  }


void RacesAppDlg::onSanitizeDB() {
String   csvPath = getPath(dbPath);    csvPath += _T("DeadRcdData.csv");
DeadRcds deadRcds(csvPath);
int      n;
String   s;

  n = deadRcds.fix();   s.format(_T("%i Records Marked as Deleted"), n);   messageBox(s);
  }


void RacesAppDlg::onHelp() {
String topic = helpPath; topic += _T(">Introduction");

  ::HtmlHelp(GetSafeHwnd(), topic,  HH_DISPLAY_TOC, 0);
  }


void RacesAppDlg::onAbout() {AboutDlg aboutDlg; aboutDlg.DoModal();}


void RacesAppDlg::onUpdateDbExit() {

  updateMbr();

  if (!curMbr.updateDB(dbPath)) messageBox(_T("Something went wrong while updating database!"));

  CDialogEx::OnOK();
  }


void RacesAppDlg::onPickPicPath() {
String     rootPath = dbPath;
PathDlgDsc pathDlg;
String     picPath;
int        pos;

  if (readOnly) return;

  rootPath = getPath(rootPath);   pos = rootPath.length() - 1;

  rootPath = getPath(rootPath.substr(0, pos));   picPath = rootPath + _T("Images\\");

  pathDlg = pathDlg(_T("Member Photo"), picPath, _T("jpg"), _T("*.jpg"));

  if (!getOpenDlg(pathDlg, picPath)) return;

  pos = rootPath.length();   picPath = picPath.substr(pos);   picPath = _T("..\\") + picPath;

  picPathCtl.SetWindowText(picPath);

  mbrPic.set(picPath);
  }


void RacesAppDlg::initScreen() {
  setLabels();              clear(badgeOKCtl);
  clear(badgeNoCtl);        clear(recordIDCtl);       clear(mbrZipOnlyCtl);
  clear(officerCtl);        clear(emplZipOnlyCtl);    clear(handHeldCtl);
  clear(portMobileCtl);     clear(portPacketCtl);     clear(otherEquipCtl);
  clear(multilingualCtl);   clear(otherCapCtl);       clear(limitationsCtl);
  clear(commentsCtl);       clear(skillCertsCtl);     clear(eocCertCtl);
  clear(lastUpdateCtl);     mbrPic.clear();
  }


// Labels in the fields just before being edited

static TCchar* FirstNameLbl     = _T("<First Name>");
static TCchar* MiddleInitialLbl = _T("<I>");
static TCchar* LastNameLbl      = _T("<Last Name>");
static TCchar* SuffixLbl        = _T("<Ttl>");
static TCchar* CallLbl          = _T("<FCC>");
static TCchar* CSExpDateLbl     = _T("<Expires>");
static TCchar* BgExpDateLbl     = _T("<Expires>");
static TCchar* StreetAddrLbl    = _T("<Street Address>");
static TCchar* UnitNoLbl        = _T("<Unit #>");
static TCchar* CityLbl          = _T("<City>");
static TCchar* StateLbl         = _T("<S>");
static TCchar* ZipLbl           = _T("<Zip>");
static TCchar* CellPhLbl        = _T("<Cell Phone>");
static TCchar* LandLineLbl      = _T("<Landline>");
static TCchar* HomeZipLbl       = _T("<Home Zip>");
static TCchar* EmailLbl         = _T("<eMail Address>");
static TCchar* DateLbl          = _T("<m/d/yr>");
static TCchar* CompanyNameLbl   = _T("<Company Name>");
static TCchar* CompanyZipLbl    = _T("<Cmpy Zip>");
static TCchar* PicPathLbl       = _T("<Picture Path>");


void RacesAppDlg::setLabels() {
  setFirstName();                           set(  midInitialCtl, MiddleInitialLbl);
  set(    lastNameCtl, LastNameLbl);        set(  suffixCtl,     SuffixLbl);
  set(    callSignCtl, CallLbl);
  set(   csExpDateCtl, CSExpDateLbl);       set(     badgeOKCtl, false);
  set(     badgeNoCtl, _T("123"));          set(badgeExpDateCtl, BgExpDateLbl);

  set(mbrStreetAdrCtl, StreetAddrLbl);      set(   mbrUnitNoCtl, UnitNoLbl);
  set(     mbrCityCtl, CityLbl);            set(    mbrStateCtl, StateLbl);
  set(      mbrZipCtl, ZipLbl);             set(   mbrCellPhCtl, CellPhLbl);
  set( mbrLandlineCtl, LandLineLbl);        set(  mbrHomeZipCtl, HomeZipLbl);

  set(     mbrEmailCtl, EmailLbl);          set(      officerCtl, false);
  set(    startDateCtl, DateLbl);           set(      dswDateCtl, DateLbl);
  set(responderDateCtl, DateLbl);

  set( iceFirstNameCtl, FirstNameLbl);      set(iceMidInitialCtl, MiddleInitialLbl);
  set(  iceLastNameCtl, LastNameLbl);       set(     iceEmailCtl, EmailLbl);
  set( iceStreetAdrCtl, StreetAddrLbl);     set(    iceUnitNoCtl, UnitNoLbl);
  set(      iceCityCtl, CityLbl);           set(     iceStateCtl, StateLbl);
  set(       iceZipCtl, ZipLbl);            set(    iceCellPhCtl, CellPhLbl);
  set(  iceLandlineCtl, LandLineLbl);

  set(       emplNameCtl, CompanyNameLbl);  set(      emplEmailCtl, EmailLbl);
  set(  emplStreetAdrCtl, StreetAddrLbl);   set(     emplUnitNoCtl, UnitNoLbl);
  set(       emplCityCtl, CityLbl);         set(      emplStateCtl, StateLbl);
  set(        emplZipCtl, ZipLbl);          set(     emplCellPhCtl, CellPhLbl);
  set(   emplLandlineCtl, LandLineLbl);     set( emplCmpZipCtl, CompanyZipLbl);
  set(        picPathCtl, PicPathLbl);
  }


void RacesAppDlg::setFirstName() {set(firstNameCtl, FirstNameLbl);}


void RacesAppDlg::onClearMbrfirstname()     {clrLbl(firstNameCtl,      FirstNameLbl);}
void RacesAppDlg::onClearMbrMiddleInitial() {clrLbl(midInitialCtl,     MiddleInitialLbl);}
void RacesAppDlg::onClearMbrLastName()      {clrLbl(lastNameCtl,       LastNameLbl);}
void RacesAppDlg::onClearSuffix()           {clrLbl(suffixCtl,         SuffixLbl);}
void RacesAppDlg::onClearMbrCallsign()      {clrLbl(callSignCtl,       CallLbl);}
void RacesAppDlg::onClearCallSignExpDate()  {clrLbl(csExpDateCtl,      CSExpDateLbl);}
void RacesAppDlg::onClearBadgeExpDate()     {clrLbl(badgeExpDateCtl,   BgExpDateLbl);}

void RacesAppDlg::clearMbrStreetAdr()       {clrLbl(mbrStreetAdrCtl,   StreetAddrLbl);}
void RacesAppDlg::clearMbrZip()             {clrLbl(mbrZipCtl,         ZipLbl);}
void RacesAppDlg::clearMbrHomeZip()         {clrLbl(mbrHomeZipCtl,     HomeZipLbl);}
void RacesAppDlg::clearIceStreetAdr()       {clrLbl(iceStreetAdrCtl,   StreetAddrLbl);}
void RacesAppDlg::clearIceZip()             {clrLbl(iceZipCtl,         ZipLbl);}
void RacesAppDlg::clearEmplStreetAdr()      {clrLbl(emplStreetAdrCtl,  StreetAddrLbl);}
void RacesAppDlg::clearEmplZip()            {clrLbl(emplZipCtl,        ZipLbl);}
void RacesAppDlg::clearEmplCompanyZip()     {clrLbl(emplCmpZipCtl,     CompanyZipLbl);}

void RacesAppDlg::onClearMbrUnitNo()        {clrLbl(mbrUnitNoCtl,      UnitNoLbl);}
void RacesAppDlg::onClearMbrCity()          {clrLbl(mbrCityCtl,        CityLbl);}
void RacesAppDlg::onClearMbrState()         {clrLbl(mbrStateCtl,       StateLbl);}
void RacesAppDlg::onClearMbrCellPh()        {clrLbl(mbrCellPhCtl,      CellPhLbl);}
void RacesAppDlg::onClearMbrLandline()      {clrLbl(mbrLandlineCtl,    LandLineLbl);}
void RacesAppDlg::onClearMbrEmail()         {clrLbl(mbrEmailCtl,       EmailLbl);}
void RacesAppDlg::onClearStartDate()        {clrLbl(startDateCtl,      DateLbl);}
void RacesAppDlg::onClearDSWDate()          {clrLbl(dswDateCtl,        DateLbl);}
void RacesAppDlg::onClearResponderDate()    {clrLbl(responderDateCtl,  DateLbl);}

void RacesAppDlg::onClearIceFirstName()     {clrLbl(iceFirstNameCtl,   FirstNameLbl);}
void RacesAppDlg::onClearIceMidInitial()    {clrLbl(iceMidInitialCtl,  MiddleInitialLbl);}
void RacesAppDlg::onClearIceLastName()      {clrLbl(iceLastNameCtl,    LastNameLbl);}
void RacesAppDlg::onClearIceEmail()         {clrLbl(iceEmailCtl,       EmailLbl);}
void RacesAppDlg::onClearIceUnitNo()        {clrLbl(iceUnitNoCtl,      UnitNoLbl);}
void RacesAppDlg::onClearIceCity()          {clrLbl(iceCityCtl,        CityLbl);}
void RacesAppDlg::onClearIceState()         {clrLbl(iceStateCtl,       StateLbl);}
void RacesAppDlg::onClearIceCellPh()        {clrLbl(iceCellPhCtl,      CellPhLbl);}
void RacesAppDlg::onClearIceLandline()      {clrLbl(iceLandlineCtl,    LandLineLbl);}

void RacesAppDlg::onClearEmplName()         {clrLbl(emplNameCtl,       CompanyNameLbl);}
void RacesAppDlg::onClearEmplEmail()        {clrLbl(emplEmailCtl,      EmailLbl);}
void RacesAppDlg::onClearEmplUnitNo()       {clrLbl(emplUnitNoCtl,     UnitNoLbl);}
void RacesAppDlg::onClearEmplCity()         {clrLbl(emplCityCtl,       CityLbl);}
void RacesAppDlg::onClearEmplState()        {clrLbl(emplStateCtl,      StateLbl);}
void RacesAppDlg::onClearEmplCellPh()       {clrLbl(emplCellPhCtl,     CellPhLbl);}
void RacesAppDlg::onClearEmplLandline()     {clrLbl(emplLandlineCtl,   LandLineLbl);}


void RacesAppDlg::onLeaveMbrCellPh()
               {String s = compressPhone(get(mbrCellPhCtl));    set(mbrCellPhCtl, expandPhone(s));}

void RacesAppDlg::onLeaveMbrlandline()
           {String s = compressPhone(get(mbrLandlineCtl));    set(mbrLandlineCtl, expandPhone(s));}

void RacesAppDlg::onLeaveIceCellPh()
               {String s = compressPhone(get(iceCellPhCtl));    set(iceCellPhCtl, expandPhone(s));}

void RacesAppDlg::onLeaveICELandline()
           {String s = compressPhone(get(iceLandlineCtl));    set(iceLandlineCtl, expandPhone(s));}

void RacesAppDlg::onLeaveEmplCellPh()
             {String s = compressPhone(get(emplCellPhCtl));    set(emplCellPhCtl, expandPhone(s));}

void RacesAppDlg::onLeaveEmplLandline()
         {String s = compressPhone(get(emplLandlineCtl));    set(emplLandlineCtl, expandPhone(s));}


void RacesAppDlg::onStartMbrStreetAdr()
                     {clrLbl(mbrStreetAdrCtl, StreetAddrLbl);     addrList.load(mbrStreetAdrCtl);}
void RacesAppDlg::onSelectMbrStreetAdr()  {addrList.getSel(mbrStreetAdrCtl);}
void RacesAppDlg::onLeaveMbrStreetAdr()   {addrList.set(mbrStreetAdrCtl,  mbrUnitNoCtl);}
void RacesAppDlg::onLeaveMbrUnitNo()      {addrList.add(mbrStreetAdrCtl,  mbrUnitNoCtl);}

void RacesAppDlg::onStartIceStreetAdr()
                     {clrLbl(iceStreetAdrCtl,   StreetAddrLbl);   addrList.load(iceStreetAdrCtl);}
void RacesAppDlg::onSelectIceStreetAdr()  {addrList.getSel(iceStreetAdrCtl);}
void RacesAppDlg::onLeaveIceStreetAdr()   {addrList.set(iceStreetAdrCtl,  iceUnitNoCtl);}
void RacesAppDlg::onLeaveIceUnitNo()      {addrList.add(iceStreetAdrCtl,  iceUnitNoCtl);}

void RacesAppDlg::onStartEmplStreetAdr()
                     {clrLbl(emplStreetAdrCtl,  StreetAddrLbl);   addrList.load(emplStreetAdrCtl);}
void RacesAppDlg::onSelectEmplStreetAdr() {addrList.getSel(emplStreetAdrCtl);}
void RacesAppDlg::onLeaveEmplStreetAdr()  {addrList.set(emplStreetAdrCtl, emplUnitNoCtl);}
void RacesAppDlg::onLeaveEmplUnitNo()     {addrList.add(emplStreetAdrCtl, emplUnitNoCtl);}

void RacesAppDlg::onStartMbrZip()         {clrLbl(mbrZipCtl, ZipLbl);   zipList.load(mbrZipCtl);}
void RacesAppDlg::onSelectMbrzip()        {zipList.set(mbrZipCtl,  mbrCityCtl,  mbrStateCtl);}
void RacesAppDlg::onLeaveMbrZip()         {zipList.add(mbrZipCtl,  mbrCityCtl,  mbrStateCtl);}

void RacesAppDlg::onStartMbrHomeZip()
                                {clrLbl(mbrHomeZipCtl, HomeZipLbl);   zipList.load(mbrHomeZipCtl);}
void RacesAppDlg::onSelectMbrHomeZip() {zipList.set(mbrHomeZipCtl, mbrCityCtl,  mbrStateCtl);}
void RacesAppDlg::onLeaveMbrHomeZip()  {zipList.add(mbrHomeZipCtl, mbrCityCtl,  mbrStateCtl);}


void RacesAppDlg::onLeaveIceName() {
PrepAdrRcd prepRcd;

  prepRcd.setAddress(get(mbrStreetAdrCtl));   prepRcd.setUnitNo(get(mbrUnitNoCtl));

  addrList.add(prepRcd.add());
  }


void RacesAppDlg::onStartIceZip()      {clrLbl(iceZipCtl, ZipLbl);   zipList.load(iceZipCtl);}
void RacesAppDlg::onSelectIceZip()     {zipList.set(iceZipCtl,  iceCityCtl,  iceStateCtl);}
void RacesAppDlg::onLeaveIceZip()      {zipList.add(iceZipCtl,  iceCityCtl,  iceStateCtl);}

void RacesAppDlg::onStartEmplZip()     {clrLbl(emplZipCtl, ZipLbl);   zipList.load(emplZipCtl);}
void RacesAppDlg::onSelectEmplZip()    {zipList.set(emplZipCtl, emplCityCtl, emplStateCtl);}
void RacesAppDlg::onLeaveEmplZip()     {zipList.add(emplZipCtl, emplCityCtl, emplStateCtl);}

void RacesAppDlg::onStartEmplCompanyZip()
                             {clrLbl(emplCmpZipCtl, CompanyZipLbl);   zipList.load(emplCmpZipCtl);}
void RacesAppDlg::onSelectEmplCompanyZip() {zipList.set(emplCmpZipCtl, emplCityCtl, emplStateCtl);}
void RacesAppDlg::onLeaveEmplCompanyZip()  {zipList.add(emplCmpZipCtl, emplCityCtl, emplStateCtl);}


void RacesAppDlg::saveNewMember() {
Cstring         cs;
MbrRcd          rcd;
String          s;

  curMbr.clear();   clrLabels();
  rcd.badgeNumber    = getInt(badgeNoCtl);
  rcd.statusID       = mbrStatus.getID();
  rcd.assgnPrefID    = mbrAvailability.getID();
  rcd.locationPrefID = mbrGeography.getID();
  rcd.mbrEntityID    = getMbrEntity();   setTitle();
  rcd.textMsgPh1     = getTxtPh(rcd.mbrEntityID);
  rcd.iCE_EntityID   = getICEEntity();
  rcd.emplEntityID   = getEmplEntity();
  rcd.textMsgPh2     = getTxtPh(rcd.emplEntityID);
       callSignCtl.GetWindowText(cs);    rcd.callSign            = cs;
      csExpDateCtl.GetWindowText(cs);    rcd.fCCExpiration       = compressDate(cs);
                                         rcd.badgeOK             = badgeOKCtl.GetCheck();
   badgeExpDateCtl.GetWindowText(cs);    rcd.badgeExpDate        = compressDate(cs);

                                         rcd.isOfficer           = officerCtl.GetCheck();
      startDateCtl.GetWindowText(cs);    rcd.startDate           = compressDate(cs);
        dswDateCtl.GetWindowText(cs);    rcd.dSWDate             = compressDate(cs);
  responderDateCtl.GetWindowText(cs);    rcd.responder           = compressDate(cs);

       handHeldCtl.GetWindowText(cs);    rcd.handHeld            = cs;
     portMobileCtl.GetWindowText(cs);    rcd.portMobile          = cs;
     portPacketCtl.GetWindowText(cs);    rcd.portPacket          = cs;
     otherEquipCtl.GetWindowText(cs);    rcd.otherEquip          = cs;
   multilingualCtl.GetWindowText(cs);    rcd.multilingual        = cs;
       otherCapCtl.GetWindowText(cs);    rcd.otherCapabilities   = cs;
    limitationsCtl.GetWindowText(cs);    rcd.limitations         = cs;
       commentsCtl.GetWindowText(cs);    rcd.comments            = cs;
     skillCertsCtl.GetWindowText(cs);    rcd.skillCertifications = cs;
        eocCertCtl.GetWindowText(cs);    rcd.eOC_Certifications  = cs;
        picPathCtl.GetWindowText(cs);    rcd.image               = cs;
                                         rcd.updateDate          = getTodayCmpr();

  if (rcd.mbrEntityID                   ||   !rcd.callSign.isEmpty()            ||
      !rcd.fCCExpiration.isEmpty()      ||   !rcd.badgeOK                       ||
      !rcd.badgeExpDate.isEmpty()       ||   !rcd.isOfficer                     ||
      !rcd.startDate.isEmpty()          ||   !rcd.dSWDate.isEmpty()             ||
      !rcd.responder.isEmpty()          ||   !rcd.handHeld.isEmpty()            ||
      !rcd.portMobile.isEmpty()         ||   !rcd.portPacket.isEmpty()          ||
      !rcd.otherEquip.isEmpty()         ||   !rcd.multilingual.isEmpty()        ||
      !rcd.otherCapabilities.isEmpty()  ||   !rcd.limitations.isEmpty()         ||
      !rcd.comments.isEmpty()           ||   !rcd.skillCertifications.isEmpty() ||
      !rcd.eOC_Certifications.isEmpty()) {

    curMbr.set(memberList.add(&rcd));
    curMbr.rcdDirty();   curMbr.mbrDirty();   curMbr.iceDirty();   curMbr.emplDirty();
    }

  setStatus(dlgSource, false);
  }


void RacesAppDlg::saveMember() {
PrepEntRcd mbr;
AdrRcd*    adrRcd;
CtyRcd*    ctyRcd;

  if (curMbr.isEmpty()) return;

  clrLabels();

  if (setField(curMbr.rcd->statusID,      mbrStatus.getID()))                   curMbr.rcdDirty();
  if (setField(curMbr.rcd->fCCExpiration, compressDate(get(csExpDateCtl))))     curMbr.rcdDirty();
  if (setField(curMbr.rcd->badgeOK,       badgeOKCtl.GetCheck()))               curMbr.rcdDirty();
  if (setField(curMbr.rcd->badgeExpDate,  compressDate(get(badgeExpDateCtl))))  curMbr.rcdDirty();

  mbr.setFirstName(get(firstNameCtl));
  mbr.setMiddleInit(get(midInitialCtl));
  mbr.setLastName(get(lastNameCtl));
  mbr.setSuffix(get(suffixCtl));
  mbr.setAddress(get(mbrStreetAdrCtl));
  mbr.setUnitNo(get(mbrUnitNoCtl));
  mbr.setCity(get(mbrCityCtl));
  mbr.setState(get(mbrStateCtl));
  mbr.setZip(get(mbrZipCtl));
  mbr.setZipOnly(mbrZipOnlyCtl.GetCheck());
  mbr.setLocZip(get(mbrHomeZipCtl));
  mbr.setEmail(get(mbrEmailCtl));
  mbr.setCellPh(get(mbrCellPhCtl));
  mbr.setLandLine(get(mbrLandlineCtl));
  if (setField(curMbr.rcd->textMsgPh1, mbr.getTxtPh())) curMbr.rcdDirty();

  if (!setEntity(curMbr.mbr, adrRcd, ctyRcd)) return;
  mbr.setAdrRcd(adrRcd);   mbr.setCtyRcd(ctyRcd);
  curMbr.rcd->mbrEntityID = mbr.updateRcd(curMbr.mbr);

  mbr.clear();
  mbr.setFirstName(get(iceFirstNameCtl));
  mbr.setMiddleInit(get(iceMidInitialCtl));
  mbr.setLastName(get(iceLastNameCtl));
  mbr.setAddress(get(iceStreetAdrCtl));
  mbr.setUnitNo(get(iceUnitNoCtl));
  mbr.setCity(get(iceCityCtl));
  mbr.setState(get(iceStateCtl));
  mbr.setZip(get(iceZipCtl));
  mbr.setEmail(get(iceEmailCtl));
  mbr.setCellPh(get(iceCellPhCtl));
  mbr.setLandLine(get(iceLandlineCtl));

  if (!setEntity(curMbr.ice, adrRcd, ctyRcd)) return;
  mbr.setAdrRcd(adrRcd);   mbr.setCtyRcd(ctyRcd);
  curMbr.rcd->iCE_EntityID = mbr.updateRcd(curMbr.ice);

  mbr.clear();
  mbr.setFirstName(get(emplNameCtl));
  mbr.setAddress(get(emplStreetAdrCtl));
  mbr.setUnitNo(get(emplUnitNoCtl));
  mbr.setCity(get(emplCityCtl));
  mbr.setState(get(emplStateCtl));
  mbr.setZip(get(emplZipCtl));
  mbr.setZipOnly(emplZipOnlyCtl.GetCheck());
  mbr.setLocZip(get(emplCmpZipCtl));
  mbr.setEmail(get(emplEmailCtl));
  mbr.setCellPh(get(emplCellPhCtl));
  mbr.setLandLine(get(emplLandlineCtl));
  if (setField(curMbr.rcd->textMsgPh2, mbr.getTxtPh())) curMbr.rcdDirty();

  if (!setEntity(curMbr.empl, adrRcd, ctyRcd)) return;
  mbr.setAdrRcd(adrRcd);   mbr.setCtyRcd(ctyRcd);
  curMbr.rcd->emplEntityID = mbr.updateRcd(curMbr.empl);

  if (setField(curMbr.rcd->handHeld, get(handHeldCtl)))               curMbr.rcdDirty();
  if (setField(curMbr.rcd->portMobile, get(portMobileCtl)))           curMbr.rcdDirty();
  if (setField(curMbr.rcd->portPacket, get(portPacketCtl)))           curMbr.rcdDirty();
  if (setField(curMbr.rcd->otherEquip, get(otherEquipCtl)))           curMbr.rcdDirty();
  if (setField(curMbr.rcd->multilingual, get(multilingualCtl)))       curMbr.rcdDirty();

  if (setField(curMbr.rcd->otherCapabilities, get(otherCapCtl)))      curMbr.rcdDirty();

  if (setField(curMbr.rcd->limitations, get(limitationsCtl)))         curMbr.rcdDirty();
  if (setField(curMbr.rcd->comments, get(commentsCtl)))               curMbr.rcdDirty();
  if (setField(curMbr.rcd->skillCertifications, get(skillCertsCtl)))  curMbr.rcdDirty();
  if (setField(curMbr.rcd->eOC_Certifications, get(eocCertCtl)))      curMbr.rcdDirty();
  if (setField(curMbr.rcd->image, get(picPathCtl)))                   curMbr.rcdDirty();

  curMbr.rcd->updateDate = getTodayCmpr();
  }


void RacesAppDlg::setTitle() {
String title;

  title = curMbr.getIdent();

  if (title.isEmpty()) title = _T("RACES Record");

  SetWindowText(title);
  }

void RacesAppDlg::clrLabels() {
  onClearMbrfirstname();      onClearMbrMiddleInitial();    onClearMbrLastName();
  onClearSuffix();
  onClearMbrCallsign();       onClearCallSignExpDate();     onClearBadgeExpDate();
  clearMbrStreetAdr();        onClearMbrUnitNo();           onClearMbrCity();
  onClearMbrState();          clearMbrZip();                onClearMbrCellPh();
  onClearMbrLandline();       clearMbrHomeZip();            onClearMbrEmail();
  onClearStartDate();         onClearDSWDate();             onClearResponderDate();

  onClearIceFirstName();      onClearIceMidInitial();       onClearIceLastName();
  onClearIceEmail();          clearIceStreetAdr();          onClearIceUnitNo();
  onClearIceCity();           onClearIceState();            clearIceZip();
  onClearIceCellPh();         onClearIceLandline();

  onClearEmplName();          onClearEmplEmail();           clearEmplStreetAdr();
  onClearEmplUnitNo();        onClearEmplCity();            onClearEmplState();
  clearEmplZip();             onClearEmplCellPh();          onClearEmplLandline();
  clearEmplCompanyZip();      clrLbl(picPathCtl, PicPathLbl);
  }


bool RacesAppDlg::setEntity(EntRcd* ent, AdrRcd*& adr, CtyRcd*& cty) {
int id;

  if (!ent) return false;

  id = ent->addrID;
  adr = id ? adrTbl.find(id) : &nilAdr;
  if (!adr) {adr = &nilAdr;   ent->addrID = 0;   curMbr.setDirty(ent);}

  id = ent->cityStID;
  cty = id ? ctyTbl.find(id) : &nilCty;
  if (!cty) {cty = &nilCty;   ent->cityStID = 0;   curMbr.setDirty(ent);}

  return true;
  }


int RacesAppDlg::getMbrEntity() {
EntRcd  ent;
Cstring cs;

    firstNameCtl.GetWindowText(cs);   ent.firstName     = cs;
   midInitialCtl.GetWindowText(cs);   ent.middleInitial = cs;
     lastNameCtl.GetWindowText(cs);   ent.lastName      = cs;
       suffixCtl.GetWindowText(cs);   ent.suffix        = cs;
    mbrCellPhCtl.GetWindowText(cs);   ent.phone2       = compressPhone(cs);
  mbrLandlineCtl.GetWindowText(cs);   ent.phone1       = compressPhone(cs);
                                      ent.addrIsPO     = mbrZipOnlyCtl.GetCheck();
   mbrHomeZipCtl.GetWindowText(cs);   ent.locationZip  = compressZip(cs);
     mbrEmailCtl.GetWindowText(cs);   ent.eMail        = cs;

   ent.addrID   = addrList.add(mbrStreetAdrCtl, mbrUnitNoCtl);
   ent.cityStID = zipList.add(mbrZipCtl, mbrCityCtl, mbrStateCtl);

  return addEntity(ent);
  }


TCchar* RacesAppDlg::getTxtPh(int entId)
                    {EntRcd* ent = entTbl.find(entId);   return  ent ? ent->phone2.str() : _T("");}


int RacesAppDlg::getICEEntity() {
EntRcd  ent;
Cstring cs;

   iceFirstNameCtl.GetWindowText(cs);    ent.firstName     = cs;
  iceMidInitialCtl.GetWindowText(cs);    ent.middleInitial = cs;
    iceLastNameCtl.GetWindowText(cs);    ent.lastName      = cs;
       iceEmailCtl.GetWindowText(cs);    ent.eMail         = cs;
      iceCellPhCtl.GetWindowText(cs);    ent.phone2        = compressPhone(cs);
    iceLandlineCtl.GetWindowText(cs);    ent.phone1        = compressPhone(cs);

  ent.addrID   = addrList.add(iceStreetAdrCtl, iceUnitNoCtl);
  ent.cityStID = zipList.add(iceZipCtl, iceCityCtl, iceStateCtl);

  return addEntity(ent);
  }


int RacesAppDlg::getEmplEntity() {
EntRcd  ent;
Cstring cs;
        emplNameCtl.GetWindowText(cs);   ent.firstName   = cs;
       emplEmailCtl.GetWindowText(cs);   ent.eMail       = cs;
      emplCellPhCtl.GetWindowText(cs);   ent.phone2      = compressPhone(cs);
    emplLandlineCtl.GetWindowText(cs);   ent.phone1      = compressPhone(cs);
                                         ent.addrIsPO    = emplZipOnlyCtl.GetCheck();
  emplCmpZipCtl.GetWindowText(cs);   ent.locationZip = compressZip(cs);

  ent.addrID   = addrList.add(emplStreetAdrCtl, emplUnitNoCtl);
  ent.cityStID = zipList.add(emplZipCtl, emplCityCtl, emplStateCtl);

  return addEntity(ent);
  }


int RacesAppDlg::addEntity(EntRcd& ent) {
EntRcd* entRcd;

  if (!ent.firstName.isEmpty()   ||   !ent.middleInitial.isEmpty()  ||   !ent.lastName.isEmpty() ||
      !ent.suffix.isEmpty()      ||    ent.addrID                   ||    ent.cityStID           ||
       ent.addrIsPO              ||   !ent.locationZip.isEmpty()    ||
      !ent.eMail.isEmpty()       ||   !ent.phone2.isEmpty()         ||   !ent.phone1.isEmpty()) {

    entRcd = curMbr.addEntTbl(ent);   return entRcd->getId();
    }

  return 0;
  }


void RacesAppDlg::setStatus(DlgSource src, bool rdOnly) {
String s;

  dlgSource = src;   readOnly = rdOnly;

  switch (dlgSource) {
    case NilSrc    : s = _T("");                break;
    case NewMbrSrc : s = _T("New Member");      break;
    case CurMbrSrc : s = _T("Current Members"); break;
    case FmrMbrSrc : s = _T("Former Members");  break;
    case RtrMbrSrc : s = _T("Retire Members");  break;
    default        : s.clear();                 break;
    }
  s += readOnly ? _T(" -- Read Only") : _T(" -- Editable");

  statusBar.setText(0, s);
  }


void RacesAppDlg::setPath(TCchar* path) {statusBar.setText(1, path);}


void RacesAppDlg::OnMove(int x, int y)
      {CRect winRect;   GetWindowRect(&winRect);   winPos.set(winRect);   CDialogEx::OnMove(x, y);}


void RacesAppDlg::OnSize(UINT nType, int cx, int cy) {
CRect r;

  GetWindowRect(&r);

  if (!isInitialized) {winPos.setInvBdrs(r, cx, cy);   return;}

  winPos.set(cx, cy);   toolBar.move(r);   statusBar.move(r);   CDialogEx::OnSize(nType, cx, cy);

  chkMbrPicture();
  }


void RacesAppDlg::chkMbrPicture() {
CRect r;
int   width;
int   height;

  GetClientRect(&r);

  width  = r.right  - r.left;
  height = r.bottom - r.top;

  mbrPic.check(r.right, r.bottom);
  }


// MainFrame message handlers

LRESULT RacesAppDlg::OnResetToolBar(WPARAM wParam, LPARAM lParam) {setupToolBar();  return 0;}


void RacesAppDlg::setupToolBar() {
CRect winRect;   GetWindowRect(&winRect);   toolBar.set(winRect);

  toolBar.addMenu(ID_ReportMenu,  IDR_ReportMenu, _T("Reports"));
  toolBar.setSeparator(15);
  }


// Do ToolTips

BOOL RacesAppDlg::OnTtnNeedText(UINT id, NMHDR* pNMHDR, LRESULT* pResult)
                                                            {return toolBar.OnTtnNeedText(pNMHDR);}




////--------------

#if 0
bool RacesAppDlg::setPtrs(MbrInfo* info) {

  if (!info) return false;

  currentInfo = info;
  curMbr.rcd      = info->curMbr.rcd  ? info->curMbr.rcd  : &nilRcd;
  curMbr.ent      = info->curMbr.ent  ? info->curMbr.ent  : &nilEnt;
  curMbr.empl     = info->curMbr.empl ? info->curMbr.empl : &nilEnt;
  curMbr.ice      = info->curMbr.ice  ? info->curMbr.ice  : &nilEnt;

  setTitle();   return true;
  }
#endif
#if 1
#else
  if (msgYesNoBox(_T("Update database?")) == IDYES) {

    adrTbl.store(dbPath);
    ctyTbl.store(dbPath);
    entTbl.store(dbPath);
    mbrTbl.store(dbPath);
    }
#endif
#if 1
#else
  setLabels();              reset(mbrListCtl);        clear(badgeOKCtl);
  clear(badgeNoCtl);        clear(recordIDCtl);       clear(mbrZipOnlyCtl);
  clear(officerCtl);        clear(emplZipOnlyCtl);    clear(handHeldCtl);
  clear(portMobileCtl);     clear(portPacketCtl);     clear(otherEquipCtl);
  clear(multilingualCtl);   clear(otherCapCtl);       clear(limitationsCtl);
  clear(commentsCtl);       clear(skillCertsCtl);     clear(eocCertCtl);
  clear(lastUpdateCtl);     mbrPic.clear();
#endif
#if 1
#else
String first;
String last;
String call;

  if (curMbr.ent && curMbr.rcd) {
    first = curMbr.ent->firstName;
    last  = curMbr.ent->lastName;
    call  = curMbr.rcd->callSign;
    }

  if (!first.isEmpty()) title  = first;
  if (!last.isEmpty())  title += _T(' ') + last;
  if (!call.isEmpty())  title += _T(", ") + call;
#endif
#if 0
String RacesAppDlg::expandDate(TCchar* tc) {
String dt = tc;
String s;

  if (!dt.length() || dt.find(_T('/')) > 0) return dt;

  s = dt.substr(0, 2) + _T('/') + dt.substr(2, 2) + _T('/') + dt.substr(4);   return s;
  }


String RacesAppDlg::compressDate(TCchar* cs) {
String dt = cs;
int    pos;
int    pos2;
String frag;
String s;

  pos = dt.find(_T('/'));             if (pos < 0) return dt;

  frag = dt.substr(0, pos);           s = adjFrag(frag);   pos++;

  pos2 = dt.find(_T('/'), pos);       if (pos < 0) {s += dt.substr(pos);   return s;}

  frag = dt.substr(pos, pos2-pos);    s += adjFrag(frag);   pos2++;

  frag = dt.substr(pos2);             s += adjFrag(frag);

  return s;
  }


// 4085551212 becomes 408.555.1212

String RacesAppDlg::expandPhone(TCchar* tc) {
String s   = tc;      s.trim();
int    lng = s.length();
String t;

  if (!lng) return s;

  if (s.find(_T('.')) > 0 || s.find(_T('-')) > 0) return s;

  if (lng >= 10) {t = s.substr(0, 3) + _T('.');   s = s.substr(3);}

  t += s.substr(0, 3) + _T('.') + s.substr(3);   return t;
  }


// (408) 555-1212 becomes 4085551212 or
// 408.555.1212 becomes 4085551212 or
// 408-555-1212 becomes 4085551212 or combinations of "()", ' ', '.' & '-'

String RacesAppDlg::compressPhone(TCchar* tc) {
String s = tc;      s.trim();
int    lng = s.length();
int    pos = 0;
int    pos2;
Tchar  ch;
String t;

  if (lng <= 7) return s;

  if (lng > 8) {
    if (s[0] == _T('(')) {
      pos = s.findOneOf(_T(") -."), 1);     if (pos < 0) {t = s.substr(1);   return t;}
      t = s.substr(1, pos-1);               pos++;
      for (ch = s[pos]; ch == _T(' '); ch = s[++pos]) continue;    // Remove blanks (408) 555-1212
      }
    else {
      pos = s.findOneOf(_T("-. "));         if (pos < 0) return s;

      t = s.substr(0, pos);                 pos++;
      }
    }

  pos2 = s.findOneOf(_T("-. "), pos);       if (pos2 < 0) {t += s.substr(pos);   return t;}

  t += s.substr(pos, pos2-pos);   pos2++;   t += s.substr(pos2);   return t;
  }


String RacesAppDlg::adjFrag(String& frag) {
int lng;

  for (lng = frag.length(); lng != 2; lng = frag.length()) {
    if (lng > 2) {
      if      (frag[0]     == _T('0')) frag = frag.substr(1);
      else if (frag[lng-1] == _T('0')) frag = frag.substr(0, lng-1);
      else                             frag = frag.substr(0, 2);
      continue;
      }

    frag = _T('0') + frag;
    }

  return frag;
  }
#endif
#if 1
#else
  mbrEnt  = entTbl.find(rcd.mbrEntityID);    if (mbrEnt) rcd.textMsgPh1  = mbrEnt->phone2;
#endif
#if 1
#else
  emplEnt = entTbl.find(rcd.emplEntityID);   if (emplEnt) rcd.textMsgPh2 = emplEnt->phone2;
#endif
#if 0
void RacesAppDlg::onFindICEAddr() {
AddressDlg dlg;

  if (readOnly) return;

  dlg.tgt = get(iceStreetAdrCtl);

  if (dlg.DoModal() == IDOK && dlg.adrRcd) {
    set(iceStreetAdrCtl, dlg.adrRcd->address1);
    set(iceUnitNoCtl,    dlg.adrRcd->address2);
    }
  }


void RacesAppDlg::onFindICEZip() {
CityStateDlg dlg;

  if (readOnly) return;

  dlg.tgt = get(iceZipCtl);

  if (dlg.DoModal() == IDOK && dlg.ctyRcd) {
    set(iceCityCtl,  dlg.ctyRcd->city);
    set(iceStateCtl, dlg.ctyRcd->state);
    set(iceZipCtl,   expandZip(dlg.ctyRcd->zip));
    }
  }


void RacesAppDlg::onFindEmplAddr() {
AddressDlg dlg;

  if (readOnly) return;

  dlg.tgt = get(emplStreetAdrCtl);

  if (dlg.DoModal() == IDOK && dlg.adrRcd) {
    set(emplStreetAdrCtl, dlg.adrRcd->address1);
    set(emplUnitNoCtl,    dlg.adrRcd->address2);
    }
  }


void RacesAppDlg::onFindEmplZip() {
CityStateDlg dlg;

  if (readOnly) return;

  dlg.tgt = get(emplZipCtl);

  if (dlg.DoModal() == IDOK && dlg.ctyRcd) {
    set(emplCityCtl,  dlg.ctyRcd->city);
    set(emplStateCtl, dlg.ctyRcd->state);
    set(emplZipCtl,   expandZip(dlg.ctyRcd->zip));
    }
  }
#endif
#if 0
  ON_BN_CLICKED(   IDC_FindICEAddr,  &onFindICEAddr)
  ON_BN_CLICKED(   IDC_FindICEZip,   &onFindICEZip)
  ON_BN_CLICKED(   IDC_FindEmplAddr, &onFindEmplAddr)
  ON_BN_CLICKED(   IDC_FindEmplZip,  &onFindEmplZip)
#endif
#if 1
#else
CtyRcd* ctyRcd = zipList.find(compressZip(get(mbrZipCtl)));

  if (ctyRcd) {
    set(mbrCityCtl,  ctyRcd->city);
    set(mbrStateCtl, ctyRcd->state);
    set(mbrZipCtl,   expandZip(ctyRcd->zip));
    }
#endif
#if 1
#else
CtyRcd* ctyRcd = zipList.find(compressZip(get(iceZipCtl)));

  if (ctyRcd) {
    set(iceCityCtl,  ctyRcd->city);
    set(iceStateCtl, ctyRcd->state);
    set(iceZipCtl,   expandZip(ctyRcd->zip));
    }
#endif
#if 1
#else
CtyRcd* ctyRcd = zipList.find(compressZip(get(emplZipCtl)));

  if (ctyRcd) {
    set(emplCityCtl,  ctyRcd->city);
    set(emplStateCtl, ctyRcd->state);
    set(emplZipCtl,   expandZip(ctyRcd->zip));
    }
#endif

//void RacesAppDlg::OnCbnCloseupMbrstreetadr() {addrList.set(mbrStreetAdrCtl,  mbrUnitNoCtl);}
//void RacesAppDlg::OnCbnEditchangeMbrstreetadr() {}
//  ON_CBN_CLOSEUP(  IDC_MbrStreetAdr,     &OnCbnCloseupMbrstreetadr)
//      ON_CBN_EDITCHANGE(IDC_MbrStreetAdr, &RacesAppDlg::OnCbnEditchangeMbrstreetadr)
#if 0
  addrList.load(mbrStreetAdrCtl);
  addrList.load(iceStreetAdrCtl);
  addrList.load(emplStreetAdrCtl);
  zipList.load(mbrZipCtl);
  zipList.load(mbrHomeZipCtl);
   zipList.load(iceZipCtl);
   zipList.load(emplZipCtl);
   zipList.load(emplCmpZipCtl);
#endif
#if 0
    String s = dlg.target;
    if (dlg.wholeWord)     s += _T(" wholeWord");
    if (dlg.curFldOnly)    s += _T(" curFldOnly");
    if (dlg.caseSensitive) s += _T(" caseSensitive");

    switch (dlg.attributes) {
      case 0  : s += _T(" Whole field");  break;
      case 1  : s += _T(" Anywhere In");  break;
      case 2  : s += _T(" Beginning Of"); break;
      default : s += _T(" Whoops!");      break;
      }

    messageBox(s);
#endif

