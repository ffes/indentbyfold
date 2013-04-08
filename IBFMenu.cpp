#include <windows.h>
#include <tchar.h>
#include "IBFMenu.h"
#include "IBFPlugin.h"

extern IBFPlugin ibfplugin;

FuncItem IBFMenu::arrFuncItems[N_NBFUNCITEMS] = {
	{ _T( "Reindent File" ), reIndentFile, 0, false, NULL },
	{ _T( "" ), NULL, 0, false, NULL }, // separator
	{ _T( "About" ), aboutDlg, 0, false, NULL }
};

void IBFMenu::reIndentFile()
{
	ibfplugin.reindentFile();
}

void IBFMenu::aboutDlg()
{
	ibfplugin.aboutDlg();
}
