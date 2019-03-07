#include <windows.h>
#include <tchar.h>
#include "IBFMenu.h"
#include "IBFPlugin.h"

extern IBFPlugin ibfplugin;

FuncItem IBFMenu::arrFuncItems[N_NBFUNCITEMS] = {
	{ L"Reindent File", reIndentFile, 0, false, NULL },
	{ L"", NULL, 0, false, NULL }, // separator
	{ L"Open Online Manual", openOnlineManual, 0, false, NULL },
	{ L"", NULL, 0, false, NULL }, // separator
	{ L"About", aboutDlg, 0, false, NULL }
};

void IBFMenu::reIndentFile()
{
	ibfplugin.reindentFile();
}

void IBFMenu::openOnlineManual()
{
	ShellExecute(NULL, L"open", L"https://indentbyfold.readthedocs.io", NULL, NULL, SW_SHOWNORMAL);
}

void IBFMenu::aboutDlg()
{
	ibfplugin.aboutDlg();
}
