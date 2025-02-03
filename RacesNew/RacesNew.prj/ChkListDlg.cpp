// ChkListDlg.cpp : implementation file
//

#include "pch.h"
#include "ChkListDlg.h"
#include "Resource.h"
#include "afxdialogex.h"


// ChkListDlg dialog

IMPLEMENT_DYNAMIC(ChkListDlg, CDialogEx)

ChkListDlg::ChkListDlg(CWnd* pParent) : CDialogEx(IDD_CheckList, pParent),
                                        nameCallSign(_T("")), applicationProc(FALSE),
                                        picture(FALSE),       groupsIO(FALSE),
                                        trainingIntro(FALSE) { }

ChkListDlg::~ChkListDlg() { }


void ChkListDlg::DoDataExchange(CDataExchange* pDX) {
  CDialogEx::DoDataExchange(pDX);
  DDX_Text( pDX, IDC_NameCalSign,   nameCallSign);
  DDX_Check(pDX, IDC_Application,   applicationProc);
  DDX_Check(pDX, IDC_Picture,       picture);
  DDX_Check(pDX, IDC_GroupsIO,      groupsIO);
  DDX_Check(pDX, IDC_TrainingIntro, trainingIntro);
  }


BEGIN_MESSAGE_MAP(ChkListDlg, CDialogEx)
END_MESSAGE_MAP()


// ChkListDlg message handlers
