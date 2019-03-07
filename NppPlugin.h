#pragma once

#include "NppMessager.h"

class CNppPlugin
{
protected:
	CNppMessager  m_nppMsgr;
	HMODULE       m_hDllModule;
	TCHAR         m_szDllFileName[100];
	TCHAR         m_szIniFileName[100];

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

	const TCHAR* getDllFileName() const  {
		return m_szDllFileName;
	}
	HMODULE getDllModule() const  {
		return m_hDllModule;
	}
	const TCHAR* getIniFileName() const  {
		return m_szIniFileName;
	}
	HWND getNppWnd() const  {
		return m_nppMsgr.getNppWnd();
	}

};
