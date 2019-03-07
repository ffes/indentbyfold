#pragma once

#include "NppMessager.h"

class CNppPlugin
{
protected:
	CNppMessager  m_nppMsgr;
	HMODULE       m_hDllModule;

public:
	CNppPlugin();
	virtual ~CNppPlugin();

	// called from DllMain
	void OnDllProcessAttach( HINSTANCE hDLLInstance );
	void OnDllProcessDetach() const;

	// standard n++ plugin functions
	virtual void         nppBeNotified( SCNotification* pscn ) = 0;
	virtual FuncItem*    nppGetFuncsArray( int* pnbFuncItems ) = 0;
	virtual const TCHAR* nppGetName() = 0;
	virtual LRESULT      nppMessageProc( UINT /*uMessage*/, WPARAM /*wParam*/, LPARAM /*lParam*/ )  {
		return 1;
	}
	void                 nppSetInfo( const NppData& nppd );

	// common n++ notification
	virtual void OnNppSetInfo( const NppData& /*nppd*/ )  { }

	HMODULE getDllModule() const  {
		return m_hDllModule;
	}

	HWND getNppWnd() const  {
		return m_nppMsgr.getNppWnd();
	}
};
