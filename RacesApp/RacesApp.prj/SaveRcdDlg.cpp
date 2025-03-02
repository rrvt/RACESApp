// Save Record Dialog -- Use when readOnly is true


#include "pch.h"
#include "SaveRcdDlg.h"
#include "Resource.h"


// SaveRcdDlg dialog

IMPLEMENT_DYNAMIC(SaveRcdDlg, CDialogEx)


BEGIN_MESSAGE_MAP(SaveRcdDlg, CDialogEx)
END_MESSAGE_MAP()


SaveRcdDlg::SaveRcdDlg(CWnd* pParent) : CDialogEx(IDD_SaveChgs, pParent), editable(FALSE) { }

SaveRcdDlg::~SaveRcdDlg() { }


void SaveRcdDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Check(pDX, IDC_SetEditable, editable);
  }

