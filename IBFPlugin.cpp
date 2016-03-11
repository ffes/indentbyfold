/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  IndentByFold - Auto indent based on the fold level                     //
//  Copyright (C) 2011 Ben Bluemel   <ben1982@gmail.com>                   //
//  Copyright (C) 2013 Frank Fesevur <fesevur@gmail.com>                   //
//                                                                         //
//  This program is free software; you can redistribute it and/or modify   //
//  it under the terms of the GNU General Public License as published by   //
//  the Free Software Foundation; either version 2 of the License, or      //
//  (at your option) any later version.                                    //
//                                                                         //
//  This program is distributed in the hope that it will be useful,        //
//  but WITHOUT ANY WARRANTY; without even the implied warranty of         //
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the           //
//  GNU General Public License for more details.                           //
//                                                                         //
//  You should have received a copy of the GNU General Public License      //
//  along with this program; if not, write to the Free Software            //
//  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.              //
//                                                                         //
/////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include "IBFPlugin.h"
#include "IBFMenu.h"
#include "SciMessager.h"
#include "WaitCursor.h"
#include "Version.h"

extern IBFPlugin ibfplugin;

WNDPROC IBFPlugin::nppOriginalWndProc = NULL;

IBFPlugin::IBFPlugin() {}

IBFPlugin::~IBFPlugin() {}

FuncItem* IBFPlugin::nppGetFuncsArray( int* pnbFuncItems )
{
	*pnbFuncItems = IBFMenu::N_NBFUNCITEMS;
	return IBFMenu::arrFuncItems;
}

bool IBFPlugin::isNppWndUnicode = true;

LRESULT IBFPlugin::nppCallWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return ::CallWindowProcW( nppOriginalWndProc, hWnd, uMsg, wParam, lParam );
}

LRESULT CALLBACK IBFPlugin::nppNewWndProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return nppCallWndProc( hWnd, uMsg, wParam, lParam );
}

const TCHAR* IBFPlugin::nppGetName()
{
	//return PLUGIN_NAME;
	return 0;
}

void IBFPlugin::OnLangChanged( uptr_t idFrom ) 
{
	useNextLine = false;
	m_nppMsgr.SendNppMsg( NPPM_GETCURRENTLANGTYPE, (WPARAM) 0, (LPARAM) & langType );
	if ( langType == L_RUBY || langType == L_HTML || langType == L_LISP || langType == L_LUA  || langType == L_PASCAL || langType == L_XML ) {
		useNextLine = true;
	}
}

void IBFPlugin::nppBeNotified( SCNotification* notifyCode )
{
	if ( notifyCode->nmhdr.hwndFrom == m_nppMsgr.getNppWnd() ) {
		// >>> notifications from Notepad++
		switch ( notifyCode->nmhdr.code ) {
		case NPPN_BUFFERACTIVATED:
		case NPPN_FILESAVED:
		case NPPN_LANGCHANGED:
			OnLangChanged( notifyCode->nmhdr.idFrom );
			break;

		case NPPN_READY:
			OnNppReady();
			break;
		case NPPN_SHUTDOWN:
			OnNppShutdown();
			break;
		default:
			break;
		}
		
		// <<< notifications from Notepad++
	} else {
		bool autocselection = false;
		// >>> notifications from Scintilla
		switch ( notifyCode->nmhdr.code ) {
		case SCN_UPDATEUI:
			break;
		case SCN_CHARADDED:
			OnSciCharAdded( notifyCode->ch );
			break;
		case SCN_AUTOCSELECTION:
			autocselection = true;
		case SCN_PAINTED:
		case SCN_AUTOCCANCELLED:
			if ( ( notifyCode->nmhdr.code != SCN_PAINTED && decrementAfterAutoC ) || (notifyCode->nmhdr.code == SCN_PAINTED && decrementAfterPaint ) ) {
				if ( decrementAfterPaint ) decrementAfterPaint = false;
				else decrementAfterAutoC = false;
				
				CSciMessager sciMsgr( m_nppMsgr.getCurrentScintillaWnd() );
				int curpos = sciMsgr.getCurrentPos();
				int curline = sciMsgr.getLineFromPos(curpos);
				int curFold = sciMsgr.getFoldLevel( curline + 1 );
				if ( postoblame == curpos && ( curFold == foldleveltomatch || notifyCode->nmhdr.code == SCN_PAINTED )  ) {

					// Only interested in this if we are completing on the actual text
					if ( autocselection && postoblame == notifyCode->position + strlen( notifyCode->text ) ) {
						sciMsgr.SendSciMsg( SCI_AUTOCCANCEL );
						sciMsgr.setLineIndentation( curline, indentationtouse );
						lastFoldDownLine = curline;
					}  else if ( !autocselection ) {
						sciMsgr.setLineIndentation( curline, indentationtouse );
						lastFoldDownLine = curline;
					}
				}
				
			}
			break;
		case SCN_MODIFIED:
			if ( notifyCode->modificationType & SC_MOD_CHANGEFOLD ) {
				
				int foldlevelNowMask = notifyCode->foldLevelNow;
				bool foldlevelnowishead = false;
				if ( foldlevelNowMask & SC_FOLDLEVELWHITEFLAG ) {
					foldlevelNowMask = foldlevelNowMask &~SC_FOLDLEVELWHITEFLAG;
				}
				if ( foldlevelNowMask & SC_FOLDLEVELHEADERFLAG ) {
					foldlevelnowishead = true;
					foldlevelNowMask = foldlevelNowMask &~SC_FOLDLEVELHEADERFLAG;
				}
				int foldlevelNowMask2 = foldlevelNowMask & SC_FOLDLEVELNUMBERMASK ;

				int foldlevelPrevMask = notifyCode->foldLevelPrev;
				if ( foldlevelPrevMask & SC_FOLDLEVELWHITEFLAG ) {
					foldlevelPrevMask = foldlevelPrevMask &~SC_FOLDLEVELWHITEFLAG;
				}
				if ( foldlevelPrevMask & SC_FOLDLEVELHEADERFLAG ) {
					foldlevelPrevMask = foldlevelPrevMask &~SC_FOLDLEVELHEADERFLAG;
				}
				int foldlevelPrevMask2 = foldlevelPrevMask  & SC_FOLDLEVELNUMBERMASK;
				bool shifted = false;
				if (foldlevelNowMask2 == foldlevelPrevMask2 && foldlevelNowMask != foldlevelPrevMask) {
					shifted = true;
					foldlevelNowMask = ( notifyCode->foldLevelNow >> 16);
					foldlevelPrevMask = ( notifyCode->foldLevelPrev >> 16);
				} else {
					foldlevelNowMask = foldlevelNowMask2;
					foldlevelPrevMask = foldlevelPrevMask2;
				}
				
				if ( foldlevelNowMask < foldlevelPrevMask ) {
					CSciMessager sciMsgr( m_nppMsgr.getCurrentScintillaWnd() );
					int curline =  sciMsgr.getLineFromPos(sciMsgr.getCurrentPos());
					if ( curline == notifyCode->line || ( useNextLine && curline == notifyCode->line - 1 ) ) {
						int actualline = notifyCode->line;
						if ( curline == notifyCode->line - 1) {
							actualline--;
						}
						
						int foldparentline = sciMsgr.getFoldParent( actualline );
						toggleDownUpLine = -1;
						if (foldlevelnowishead) {
							foldparentline = sciMsgr.getFoldParent( actualline -1 );
						}
						int foldlevelparent = sciMsgr.getFoldLevel( foldparentline );
					
						if ( shifted ) {
							foldlevelparent = foldlevelparent >> 16;
						} else {
							foldlevelparent = foldlevelparent & SC_FOLDLEVELNUMBERMASK;
						}
						// The or here is for nppCF with cfelse/cfelseif
						if (	foldlevelparent == foldlevelPrevMask || 
								( foldlevelNowMask == foldlevelparent && foldlevelnowishead ) ||
								( actualline == notifyCode->line -1 && foldlevelparent == foldlevelPrevMask -1 )
								) {
							int indent = sciMsgr.getLineIndentation( foldparentline );
							if ( sciMsgr.isAutoCActive() ) {
								// store it 
								foldleveltomatch = notifyCode->foldLevelNow;

								decrementAfterAutoC = true;
								linetodecrement = actualline;
								postoblame = sciMsgr.getCurrentPos();
								indentationtouse = indent;
							} else {
								if ( langType == L_HTML ) {
									// Hacky for HTML
									decrementAfterPaint = true;
									linetodecrement = actualline;
									postoblame = sciMsgr.getCurrentPos();
									indentationtouse = indent;
								} else {
									sciMsgr.setLineIndentation( actualline, indent );
									lastFoldDownLine = curline;
								}
							}
						}
					}
				} else if ( isNewLine == true && newLine == notifyCode->line && foldlevelNowMask > foldlevelPrevMask ) {
					CSciMessager sciMsgr( m_nppMsgr.getCurrentScintillaWnd() );
					isNewLine = false;
					newLine = -1;
					indentLine( notifyCode->line, false );
					int indentpos = sciMsgr.getLineIndentPosition( notifyCode->line );
					sciMsgr.goToPos( indentpos );
				} else if ( !useNextLine && lastFoldDownLine > -1 && foldlevelNowMask > foldlevelPrevMask ) {
					CSciMessager sciMsgr( m_nppMsgr.getCurrentScintillaWnd() );
					int curline =  sciMsgr.getLineFromPos(sciMsgr.getCurrentPos());
					if ( curline == lastFoldDownLine ) {
						toggleDownUpLine = curline;
					}
				}
			}
			break;
		default:
			break;
		}
		// <<< notifications from Scintilla
	}
}

void IBFPlugin::OnNppReady()
{
	if ( isNppWndUnicode )
	{
		nppOriginalWndProc = ( WNDPROC ) SetWindowLongPtrW(m_nppMsgr.getNppWnd(), GWLP_WNDPROC, ( LONG_PTR ) nppNewWndProc );
	}
}

void IBFPlugin::OnNppShutdown()
{
	if ( nppOriginalWndProc )
	{
		::SetWindowLongPtrW( m_nppMsgr.getNppWnd(), GWLP_WNDPROC, ( LONG_PTR ) nppOriginalWndProc );
	}
}

void IBFPlugin::OnSciCharAdded( int ch )
{
	CSciMessager sciMsgr( m_nppMsgr.getCurrentScintillaWnd() );

	// lets see if we can find one
	int currentpos = sciMsgr.getCurrentPos();
	int line = sciMsgr.getLineFromPos( currentpos );
	int eol = sciMsgr.getEOLMode();
	if ( ch == '\n' || (eol == SC_EOL_CR && ch == '\r' ) )
	{
		indentLine( line-1, false );
		indentLine( line, false );
		isNewLine = true;
		newLine = line;
		int indentpos = sciMsgr.getLineIndentPosition( line );
		sciMsgr.goToPos( indentpos );
	}
	else
	{
		isNewLine = false;
		newLine = -1;
	}
}

void IBFPlugin::reindentFile()
{
	// See FAQ in ReadMe for details about Python!
	if (langType == L_PYTHON)
	{
		return;
	}

	WaitCursor wait;
	CSciMessager sciMsgr(m_nppMsgr.getCurrentScintillaWnd());
	sciMsgr.beginUndoAction();
	int linecount = sciMsgr.getLineCount();
	sciMsgr.setLineIndentation(0, 0);
	//in scintilla line are 0 based
	for (int line = 0; line < linecount; line++)
	{
		indentLine(line, true);
	}
	sciMsgr.endUndoAction();
}

//TODO: remove doingwholefile, clean obsolete varaibles 
void IBFPlugin::indentLine( int line, bool doingwholefile )
{
	CSciMessager sciMsgr( m_nppMsgr.getCurrentScintillaWnd() );
	int getwidth = sciMsgr.getTabWidth();
	int foldLevelCurLine = sciMsgr.getFoldLevel(line);
	int foldLevel = foldLevelCurLine & SC_FOLDLEVELNUMBERMASK;
	//the first 16 bits contain fold level of after this line (in 0x0FFF0000)
	int foldLevelAfter = (foldLevelCurLine >> 16) & SC_FOLDLEVELNUMBERMASK;
	int indentPos = (foldLevel - SC_FOLDLEVELBASE) * getwidth;
	// move closing brackets down
	if (foldLevel > foldLevelAfter) indentPos -= (foldLevel - foldLevelAfter) * getwidth;
	sciMsgr.setLineIndentation(line, indentPos);
}

void IBFPlugin::OnNppSetInfo( const NppData& notpadPlusData )
{
	m_nppMsgr.setNppData( notpadPlusData );
	isNppWndUnicode = ::IsWindowUnicode( notpadPlusData._nppHandle ) ? true : false;
	lastFoldDownLine = -1;
	toggleDownUpLine = -1;
	newLine = -1;
	isNewLine = false;
	decrementAfterAutoC = false;
	decrementAfterPaint = false;
	postoblame = 0;
	langType = L_TEXT;
}

void IBFPlugin::aboutDlg()
{
	::MessageBox( m_nppMsgr.getNppWnd(),
	              TEXT( "IndentByFold by Ben Bluemel, Frank Fesevur\n\n" )
	              TEXT( "Version " ) VERSION_NUMBER_WSTR TEXT("\n\n")
	              TEXT( "https://code.google.com/p/indentbyfold/" ),
				  TEXT( "About IndentByFold" ),
	              MB_OK );
}
