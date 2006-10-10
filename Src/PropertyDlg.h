#ifndef PropertyDlg_h_included
#define PropertyDlg_h_included

#ifndef CMoveConstraint_h
#include "CMoveConstraint.h"
#endif

class PropertyList;

// PropertyDlg dialog

class PropertyDlg : public CDialog
{
	DECLARE_DYNAMIC(PropertyDlg)

public:
	PropertyDlg(CWnd* pParent, const PropertyList & props);   // standard constructor
	virtual ~PropertyDlg();

private:
	void DisplayProperties();

// Dialog Data
	//{{AFX_DATA(FileFiltersDlg)
	enum { IDD = IDD_PROPERTYDIALOG };
	CListCtrl  m_list;
	CEdit      m_value_box;
	//}}AFX_DATA

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Generated message map functions
	//{{AFX_MSG(FileFiltersDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	prdlg::CMoveConstraint m_constraint;
	const PropertyList & m_props;
};

#endif // PropertyDlg_h_included
