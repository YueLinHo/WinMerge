#include "StdAfx.h"
#include "resource.h"
#include "DisplayProperties.h"
#include "PropertyDlg.h"

void DisplayProperties(CWnd * parent, const PropertyList & props)
{
	PropertyDlg dlg(parent, props);
	dlg.DoModal();
}

