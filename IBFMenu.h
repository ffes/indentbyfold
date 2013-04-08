#ifndef __IBF_MENU_H__
#define __IBF_MENU_H__
//---------------------------------------------------------------------------

#include "NppPluginMenu.h"

class IBFMenu : public CNppPluginMenu
{
public:
	enum NMenuItems {
	    N_REINDENTFILE = 0,
	    N_SEPARATOR1,
	    N_ABOUT,

	    N_NBFUNCITEMS
	};
	static FuncItem arrFuncItems[N_NBFUNCITEMS];

public:
	static void		reIndentFile();
	static void		aboutDlg();
};
//---------------------------------------------------------------------------
#endif
