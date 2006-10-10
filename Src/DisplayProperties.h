#ifndef PropertyDialog_h_included
#define PropertyDialog_h_included

typedef enum { PLEFT, PRIGHT, PNONE } PROPSIDE;
struct Property
{ 
	CString name;
	PROPSIDE side;
	CString value; 
	Property() { }
	Property(LPCTSTR tname, PROPSIDE tside, LPCTSTR tvalue) : name(tname), side(tside), value(tvalue) { }
};

class PropertyList : public CList<Property>
{
public:
	PropertyList() { }
	void AddProperty(LPCTSTR name, PROPSIDE side, LPCTSTR value) { Property prop(name, side, value); AddTail(prop); }
	void AddProperty(LPCTSTR name, PROPSIDE side, int value) { CString sval; sval.Format(_T("%d"), value); Property prop(name, side, sval); AddTail(prop); }
	void AddProperty(LPCTSTR name, PROPSIDE side, unsigned int value) { CString sval; sval.Format(_T("%d"), value); Property prop(name, side, sval); AddTail(prop); }
	void AddProperty(LPCTSTR name, PROPSIDE side, __int64 value) { CString sval; sval.Format(_T("%d"), value); Property prop(name, side, sval); AddTail(prop); }
};

void DisplayProperties(CWnd * parent, const PropertyList & props);

#endif // PropertyDialog_h_included
