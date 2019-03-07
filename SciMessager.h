/////////////////////////////////////////////////////////////////////////////
//                                                                         //
//  IndentByFold - Auto indent based on the fold level                     //
//  Copyright (C) 2011 Ben Bluemel   <ben1982@gmail.com>                   //
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

#pragma once

#include "NPP/Scintilla.h"

class CSciMessager
{
public:
	CSciMessager( HWND hSciWnd = NULL );
	virtual ~CSciMessager();

	LRESULT SendSciMsg( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0 );
	LRESULT SendSciMsg( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0 ) const;

	HWND			getSciWnd() const  { return m_hSciWnd; }
	void			setSciWnd( HWND hSciWnd )  { m_hSciWnd = hSciWnd; }

	// Text retrieval and modification
	int				getText( int len, char* pText ) const;
	void			setText( const char* pText );
	void			beginUndoAction();
	void			endUndoAction();
	unsigned char	getCharAt( int pos ) const;
	unsigned int	getCodePage() const; // 0 (non-Unicode), SC_CP_UTF8, DBCS etc.
	int				getCurrentPos() const;
	int				getCaretInLine() const;
	LRESULT			getDocPointer() const; // identifies the document
	int				getLineFromPos( int pos ) const;
	int				getLineState( int line ) const;
	int				getSelectionMode() const; // SC_SEL_STREAM, SC_SEL_RECTANGLE, SC_SEL_LINES
	int				getSelectionEnd() const;
	int				getSelectionStart() const;
	int				getStyleAt( int pos ) const;
	int				getSelText( char* pText ) const;
	int				getTextLength() const;
	int				getTextRange( int pos1, int pos2, char* pText ) const;
	void			goToPos( int pos );
	bool			isModified() const;
	bool			isSelectionRectangle() const;
	bool			isAutoCActive() const;
	void			setCodePage( unsigned int codePage );
	void			setSel( int anchorPos, int currentPos );
	void			setSelectionMode( int mode ); // SC_SEL_STREAM, SC_SEL_RECTANGLE, SC_SEL_LINES
	void			setSelectionEnd( int pos );
	void			setSelectionStart( int pos );
	void			setSelText( const char* pText );
	void			autoCShow( int len, const char *list );
	void			autoCSetSeparator( char separator );
	void			autoCSetIgnoreCase( bool ignoreCase ) const;
	int				getEOLMode() const;
	int				getTabWidth() const;
	int				getFoldParent( int line ) const;
	int				getFoldLevel( int line ) const;
	int				getLineIndentation( int line ) const;
	int				getLineIndentPosition( int line ) const;
	int				getLineCount() const;
	int				getLineEndPos( int line ) const;
	int				getPosFromLine( int line ) const;
	int				getLineLength( int line ) const;
	int				getLine( int line, char * textbuf ) const;
	void			setLineIndentation( int line, int indentation );

protected:
	HWND m_hSciWnd;
	SciFnDirect m_pSciMsg;
	sptr_t m_pSciWndData;
};
