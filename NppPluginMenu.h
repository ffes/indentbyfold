#pragma once

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
