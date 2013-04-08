//this file is part of IndentByFold
//Copyright (C)2011 Ben Bluemel ( ben1982@gmail.com )
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.


#ifndef __IBFPLUGIN_H__
#define __IBFPLUGIN_H__

#include "NppPlugin.h"
#include "NPP/PluginInterface.h"

class IBFPlugin : public CNppPlugin
{
public:
	enum eConsts {
	    MAX_ESCAPED_PREFIX  = 20
	};

	static const TCHAR* PLUGIN_NAME;
private:
	
	bool decrementAfterAutoC;
	bool decrementAfterPaint;
	int linetodecrement;
	int indentationtouse;
	int foldleveltomatch;
	int postoblame;
	LangType langType;
protected:
	// internal vars
	int  m_nAutoRightBracketPos;
	int  m_nFileType;
	bool m_bSupportedFileType;
	bool isNewLine;
	int newLine;
	int lastFoldDownLine;
	int toggleDownUpLine;
	bool useNextLine;
public:
	IBFPlugin();
	virtual ~IBFPlugin();
	
	// standard n++ plugin functions
	virtual void         nppBeNotified( SCNotification* notifyCode );
	virtual FuncItem*    nppGetFuncsArray( int* pnbFuncItems );
	virtual const TCHAR* nppGetName();

	// common n++ notification
	virtual void OnNppSetInfo( const NppData& notpadPlusData );

	// custom n++ notifications
	void OnNppBufferActivated();
	void OnNppFileOpened();
	void OnNppFileSaved();
	void OnLangChanged( uptr_t idFrom );
	void OnNppReady();
	void OnNppShutdown();
	// custom scintilla notifications
	void OnSciCharAdded( const int ch );
	void reindentFile();
	void aboutDlg();
	void indentLine( int line, bool doingwholefile );
protected:
	// custom functions
	void UpdateFileType();
	int  getFileType( bool& isSupported );

protected:
	static bool    isNppWndUnicode;
	static WNDPROC nppOriginalWndProc;
	static LRESULT nppCallWndProc( HWND, UINT, WPARAM, LPARAM );
	static LRESULT CALLBACK nppNewWndProc( HWND, UINT, WPARAM, LPARAM );
};

#endif
