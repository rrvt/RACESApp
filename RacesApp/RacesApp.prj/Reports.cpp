// Races App Reports


#include "pch.h"
#include "Reports.h"
#include "BadgeRpt.h"
#include "ContactRpt.h"
#include "EverBridgeRpt.h"
#include "ExcelRpt.h"
#include "FileName.h"
#include "FmrPeriodDlg.h"
#include "FormerRpt.h"
#include "GetPathDlg.h"
#include "GoogleRpt.h"
#include "MbrIDs.h"
#include "PathDlgDsc.h"
#include "ProblemEntriesRpt.h"
#include "ResponderCntRpt.h"


void Reports::excelRpt() {
PathDlgDsc dsc = {_T("Excel Report"), getPathDsc(_T("Excel")), _T("csv"), _T("*.csv")};
String     path = getOutputPath(dsc);
ExcelRpt   excelRpt(path);

  excelRpt();
  }


void Reports::googleRpt() {
PathDlgDsc dsc = {_T("Google Report"), getPathDsc(_T("Google")), _T("csv"), _T("*.csv")};
String     path = getOutputPath(dsc);
GoogleRpt  googleRpt(path);

  googleRpt();
  }



void Reports::everBridgeRpt() {
PathDlgDsc dsc = {_T("Everbridge Report"), getPathDsc(_T("Everbridge")), _T("csv"), _T("*.csv")};
String     path = getOutputPath(dsc);
EverBridgeRpt  everBridgeRpt(path);

  everBridgeRpt();
  }


void Reports::csBadgeRpt() {
PathDlgDsc dsc = {_T("Badges by Callsign Report"), getPathDsc(_T("BadgesByCallSign")),
                                                                           _T("txt"), _T("*.txt")};
String     path = getOutputPath(dsc);
BadgeRpt   badgeRpt(path);

  badgeRpt(CallSignSort);
  }


void Reports::dateBadgeRpt() {
PathDlgDsc dsc = {_T("Badges by Date Report"), getPathDsc(_T("BadgesByDate")),
                                                                           _T("txt"), _T("*.txt")};
String     path = getOutputPath(dsc);
BadgeRpt   badgeRpt(path);

  badgeRpt(BadgeDateSort);
  }


void Reports::contactNm() {
PathDlgDsc dsc = {_T("Contact List by Name Report"), getPathDsc(_T("ContactListByName")),
                                                                           _T("csv"), _T("*.csv")};
String     path = getOutputPath(dsc);
ContactRpt contactRpt(path);

  contactRpt(MemberSort);
  }


void Reports::contactCS() {
PathDlgDsc dsc = {_T("Contact List by Call Sign Report"), getPathDsc(_T("ContactListByCallSign")),
                                                                           _T("csv"), _T("*.csv")};
String     path = getOutputPath(dsc);
ContactRpt contactRpt(path);

  contactRpt(CallSignSort);
  }


void Reports::responderCnts() {
PathDlgDsc dsc = {_T("Responder Counts by Attribute Report"), getPathDsc(_T("ResponderCounts")),
                                                                           _T("txt"), _T("*.txt")};
String     path = getOutputPath(dsc);
ResponderCntRpt responderCntRpt(path);

  responderCntRpt();
  }


void Reports::callSignList() {
PathDlgDsc dsc = {_T("Call Sign List"), getPathDsc(_T("CallSigns")), _T("txt"), _T("*.txt")};
String     path = getOutputPath(dsc);
MbrIDs     mbrIDs(path);

  mbrIDs(CallSignList);
  }


void Reports::memberIDs() {
PathDlgDsc dsc = {_T("Member IDs List"), getPathDsc(_T("MemberInfo")), _T("csv"), _T("*.csv")};
String     path = getOutputPath(dsc);
MbrIDs     mbrIDs(path);

  mbrIDs(PlusIDsList);
  }


void Reports::suffixList() {
PathDlgDsc dsc = {_T("Suffix List"), getPathDsc(_T("SuffixList")), _T("csv"), _T("*.csv")};
String     path = getOutputPath(dsc);
MbrIDs     mbrIDs(path);

  mbrIDs(SuffixList);
  }


void Reports::formerList() {
PathDlgDsc   dsc = {_T("Former Member List"), getPathDsc(_T("FormerMbrList")),
                                                                           _T("csv"), _T("*.csv")};
String       path = getOutputPath(dsc);
FormerRpt    rpt(path);
FmrPeriodDlg dlg;

  if (dlg.DoModal() == IDOK) rpt(dlg.begP, dlg.endP);
  }


void Reports::problemEntries() {
PathDlgDsc        dsc = {_T("Problem Entries"), getPathDsc(_T("ProblemEntries")),
                                                                           _T("csv"), _T("*.csv")};
String            path = getOutputPath(dsc);
ProblemEntriesRpt rpt(path);

  rpt();
  }



String& Reports::getPathDsc(TCchar* fileName) {
static String path;

  if (!reportPath.isEmpty()) {path = reportPath;   path = getPath(path);}

  path += fileName;   return path;
  }


TCchar* Reports::getOutputPath(PathDlgDsc& dsc)
                                 {return getSaveAsPathDlg(dsc, reportPath) ? reportPath.str() : 0;}

