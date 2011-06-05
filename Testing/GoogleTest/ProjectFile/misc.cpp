#include <windows.h>
#include <tchar.h>
#include "UnicodeString.h"

/* codepage.cpp */
int getDefaultCodepage()
{
	return 0;
}


/* StdAfx.cpp */
String LoadResString(UINT id)
{
	TCHAR buf[256];
	LoadString(NULL, id, buf, sizeof(buf));
	return String(buf);
}

/* StdAfx.cpp */
String GetSysError(int nerr)
{
	LPVOID lpMsgBuf;
	String str = _T("?");
	if (FormatMessage( 
		FORMAT_MESSAGE_ALLOCATE_BUFFER | 
		FORMAT_MESSAGE_FROM_SYSTEM | 
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		nerr,
		0, // Default language
		(LPTSTR) &lpMsgBuf,
		0,
		NULL 
		))
	{
		str = (LPCTSTR)lpMsgBuf;
	}
	// Free the buffer.
	LocalFree( lpMsgBuf );
	return str;
}


