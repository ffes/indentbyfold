#pragma once

#include "NppPluginMenu.h"

class IBFMenu : public CNppPluginMenu
{
public:
	enum NMenuItems {
	    N_REINDENT_FILE = 0,
	    N_SEPARATOR1,
		N_OPEN_INLINE_MANUAL,
	    N_SEPARATOR2,
	    N_ABOUT,

	    N_NBFUNCITEMS
	};
	static FuncItem arrFuncItems[N_NBFUNCITEMS];

public:
	static void		reIndentFile();
	static void		openOnlineManual();
	static void		aboutDlg();
};
