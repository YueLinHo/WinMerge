// PropertyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Merge.h"
#include "PropertyDlg.h"
#include "DisplayProperties.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// PropertyDlg dialog

IMPLEMENT_DYNAMIC(PropertyDlg, CDialog)

PropertyDlg::PropertyDlg(CWnd* pParent, const PropertyList & props)
	: CDialog(PropertyDlg::IDD, pParent)
	, m_props(props)
{
	//{{AFX_DATA_INIT(PropertyDlg)
	//}}AFX_DATA_INIT
}

PropertyDlg::~PropertyDlg()
{
}

void PropertyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FileFiltersDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_EDIT, m_value_box);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PropertyDlg, CDialog)
	//{{AFX_MSG_MAP(CJunkDlg)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST, OnItemchangedList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// PropertyDlg message handlers

/**
 * @brief Called before dialog is shown.
 */
BOOL PropertyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// setup handler for resizing this dialog	
	m_constraint.InitializeCurrentSize(this);
	// configure how individual controls adjust when dialog resizes
	m_constraint.ConstrainItem(IDC_LIST, 0, 1, 0, 0.5); // grows right & 50% down
	m_constraint.ConstrainItem(IDC_EDIT, 0, 1, 0.5, 0.5); // grows right, slides 50% down grows 50% down
	m_constraint.SubclassWnd(); // install subclassing
	m_constraint.LoadPosition(_T("ResizeableDialogs"), _T("ItemPropertyDlg"), false); // persist size via registry

	DisplayProperties();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void PropertyDlg::DisplayProperties()
{
	m_list.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100, 0);
	m_list.InsertColumn(1, _T("Side"), LVCFMT_LEFT, 30, 1);
	m_list.InsertColumn(2, _T("Value"), LVCFMT_LEFT, 100, 2);

	for (POSITION pos = m_props.GetHeadPosition(); pos; m_props.GetNext(pos))
	{
		Property prop = m_props.GetAt(pos);
		int index = m_list.InsertItem(m_list.GetItemCount(), prop.name);
		CString side = (prop.side == PNONE ? _T("") : (prop.side == PLEFT ? _T("L") : _T("R")));
		m_list.SetItemText(index, 1, side);
		m_list.SetItemText(index, 2, prop.value);
	}
}

void PropertyDlg::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem < 0) return;
	CString value = m_list.GetItemText(pNMListView->iItem, 2);
	m_value_box.SetWindowText(value);

	*pResult = 0;
}

