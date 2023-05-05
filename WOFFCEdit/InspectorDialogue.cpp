// InspectorDialogue.cpp : implementation file
//

#include "pch.h"
#include "afxdialogex.h"
#include "InspectorDialogue.h"


// InspectorDialogue dialog

IMPLEMENT_DYNAMIC(InspectorDialogue, CDialogEx)

InspectorDialogue::InspectorDialogue(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG2, pParent)
{

}

InspectorDialogue::~InspectorDialogue()
{
}

void InspectorDialogue::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(InspectorDialogue, CDialogEx)
END_MESSAGE_MAP()


// InspectorDialogue message handlers
