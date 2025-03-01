// SearchDlg.cpp : implementation file
//

#include "pch.h"
#include "SearchDlg.h"
#include "IniFile.h"
#include "Resource.h"

static TCchar* Section          = _T("SearchDefaults");
static TCchar* TargetKey        = _T("Target");
static TCchar* WholeWordKey     = _T("WholeWord");
static TCchar* CurFldOnlyKey    = _T("CurFldOnly");
static TCchar* CaseSensitiveKey = _T("CaseSensitive");
static TCchar* AttributesKey    = _T("Attributes");

// SearchDlg dialog

IMPLEMENT_DYNAMIC(SearchDlg, CDialogEx)


BEGIN_MESSAGE_MAP(SearchDlg, CDialogEx)
END_MESSAGE_MAP()


SearchDlg::SearchDlg(CWnd* pParent) : CDialogEx(IDD_Search, pParent), target(_T("")),
                                      wholeWord(FALSE), curFldOnly(FALSE), caseSensitive(FALSE),                                                attributes(0) { }
SearchDlg::~SearchDlg() { }



BOOL SearchDlg::OnInitDialog() {

  iniFile.read(Section, TargetKey,        target,    _T(""));
  iniFile.read(Section, WholeWordKey,     wholeWord,     0);
  iniFile.read(Section, CurFldOnlyKey,    curFldOnly,    0);
  iniFile.read(Section, CaseSensitiveKey, caseSensitive, 0);
  iniFile.read(Section, AttributesKey,    attributes,    0);

  CDialogEx::OnInitDialog();   return TRUE;
  }


void SearchDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text(pDX, IDC_SrchTgt,        target);
  DDX_Check(pDX, IDC_WholeWord,     wholeWord);
  DDX_Check(pDX, IDC_CurFldOnly,    curFldOnly);
  DDX_Check(pDX, IDC_CaseSensitive, caseSensitive);
  DDX_Radio(pDX, IDC_WholeFld,      attributes);
  }

void SearchDlg::OnOK() {
  CDialogEx::OnOK();

  iniFile.write(Section, TargetKey,        target);
  iniFile.write(Section, WholeWordKey,     wholeWord);
  iniFile.write(Section, CurFldOnlyKey,    curFldOnly);
  iniFile.write(Section, CaseSensitiveKey, caseSensitive);
  iniFile.write(Section, AttributesKey,    attributes);
  }
