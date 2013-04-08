#ifndef __NPP_PLUGIN_MENU_H__
#define __NPP_PLUGIN_MENU_H__
//----------------------------------------------------------------------------

#include "NppMessager.h"

class CNppPluginMenu
{
protected:
	static void funcEmpty() { }

protected:
	static CNppMessager m_nppMsgr;

public:
	CNppPluginMenu();
	virtual ~CNppPluginMenu();

	void setNppData( const NppData& nppd );
};

//----------------------------------------------------------------------------
#endif
