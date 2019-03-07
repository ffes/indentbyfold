#include <windows.h>
#include "NppPlugin.h"

CNppPlugin::CNppPlugin()
{
	m_hDllModule = NULL;
}

CNppPlugin::~CNppPlugin()
{
}

void CNppPlugin::OnDllProcessAttach( HINSTANCE hDLLInstance )
{
	m_hDllModule = ( HMODULE ) hDLLInstance;
}

void CNppPlugin::OnDllProcessDetach() const
{
}

void CNppPlugin::nppSetInfo( const NppData& nppd )
{
	m_nppMsgr.setNppData( nppd );
	OnNppSetInfo( nppd );
}
