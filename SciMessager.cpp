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

#include <windows.h>
#include "SciMessager.h"

CSciMessager::CSciMessager( HWND hSciWnd )
{
	m_hSciWnd = hSciWnd;
	m_pSciMsg = (SciFnDirect) SendMessage(m_hSciWnd, SCI_GETDIRECTFUNCTION, 0, 0);
	m_pSciWndData = (sptr_t) SendMessage(m_hSciWnd, SCI_GETDIRECTPOINTER, 0, 0); 
}

CSciMessager::~CSciMessager()
{
}

LRESULT CSciMessager::SendSciMsg( UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	return m_pSciMsg(m_pSciWndData, uMsg, wParam, lParam);
}

LRESULT CSciMessager::SendSciMsg( UINT uMsg, WPARAM wParam, LPARAM lParam ) const
{
	return m_pSciMsg(m_pSciWndData, uMsg, wParam, lParam);
}

void CSciMessager::beginUndoAction()
{
	SendSciMsg( SCI_BEGINUNDOACTION );
}

void CSciMessager::endUndoAction()
{
	SendSciMsg( SCI_ENDUNDOACTION );
}

unsigned char CSciMessager::getCharAt( int pos ) const
{
	return ( unsigned char ) SendSciMsg( SCI_GETCHARAT, ( WPARAM ) pos );
}

unsigned int CSciMessager::getCodePage() const
{
	return ( unsigned int ) SendSciMsg( SCI_GETCODEPAGE );
}

int CSciMessager::getCurrentPos() const
{
	return ( int ) SendSciMsg( SCI_GETCURRENTPOS );
}

int CSciMessager::getLineFromPos( int pos ) const
{
	return ( int ) SendSciMsg( SCI_LINEFROMPOSITION, ( WPARAM ) pos );
}

int CSciMessager::getLineState( int line ) const
{
	return ( int ) SendSciMsg( SCI_GETLINESTATE, ( WPARAM ) line );
}

int CSciMessager::getCaretInLine() const
{
	int curpos = SendSciMsg( SCI_GETCURRENTPOS );
	int line = SendSciMsg( SCI_LINEFROMPOSITION, ( WPARAM ) curpos );
	int startofline = SendSciMsg( SCI_POSITIONFROMLINE, ( WPARAM ) line );
	return curpos - startofline;
}

LRESULT CSciMessager::getDocPointer() const
{
	return SendSciMsg( SCI_GETDOCPOINTER );
}

int CSciMessager::getSelectionMode() const
{
	return ( int ) SendSciMsg( SCI_GETSELECTIONMODE );
}

int CSciMessager::getSelectionEnd() const
{
	return ( int ) SendSciMsg( SCI_GETSELECTIONEND );
}

int CSciMessager::getSelectionStart() const
{
	return ( int ) SendSciMsg( SCI_GETSELECTIONSTART );
}

int CSciMessager::getSelText( char* pText ) const
{
	return ( int ) SendSciMsg( SCI_GETSELTEXT, 0, ( LPARAM ) pText );
}

int CSciMessager::getText( int len, char* pText ) const
{
	return ( int ) SendSciMsg( SCI_GETTEXT, ( WPARAM ) len, ( LPARAM ) pText );
}

int CSciMessager::getTextLength() const
{
	return ( int ) SendSciMsg( SCI_GETTEXTLENGTH );
}

int CSciMessager::getTextRange( int pos1, int pos2, char* pText ) const
{
	Sci_TextRange tr;
	tr.chrg.cpMin = pos1;
	tr.chrg.cpMax = pos2;
	tr.lpstrText = pText;
	return ( int ) SendSciMsg( SCI_GETTEXTRANGE, 0, ( LPARAM ) &tr );
}

int CSciMessager::getStyleAt( int pos ) const
{
	return ( int ) SendSciMsg( SCI_GETSTYLEAT, ( WPARAM ) pos );
}

void CSciMessager::goToPos( int pos )
{
	SendSciMsg( SCI_GOTOPOS, ( WPARAM ) pos );
}

bool CSciMessager::isModified() const
{
	return SendSciMsg( SCI_GETMODIFY ) ? true : false;
}

bool CSciMessager::isSelectionRectangle() const
{
	return SendSciMsg( SCI_SELECTIONISRECTANGLE ) ? true : false;
}

bool CSciMessager::isAutoCActive() const
{
	return SendSciMsg( SCI_AUTOCACTIVE ) ? true : false;
}

void CSciMessager::setCodePage( unsigned int codePage )
{
	SendSciMsg( SCI_SETCODEPAGE, ( WPARAM ) codePage );
}

void CSciMessager::setSel( int anchorPos, int currentPos )
{
	SendSciMsg( SCI_SETSEL, ( WPARAM ) anchorPos, ( LPARAM ) currentPos );
}

void CSciMessager::setSelectionMode( int mode )
{
	SendSciMsg( SCI_SETSELECTIONMODE, ( WPARAM ) mode );
}

void CSciMessager::setSelectionEnd( int pos )
{
	SendSciMsg( SCI_SETSELECTIONEND, ( WPARAM ) pos );
}

void CSciMessager::setSelectionStart( int pos )
{
	SendSciMsg( SCI_SETSELECTIONSTART, ( WPARAM ) pos );
}

void CSciMessager::setSelText( const char* pText )
{
	SendSciMsg( SCI_REPLACESEL, 0, ( LPARAM ) pText );
}

void CSciMessager::setText( const char* pText )
{
	SendSciMsg( SCI_SETTEXT, 0, ( LPARAM ) pText );
}

void CSciMessager::autoCShow( int len, const char* list )
{
	SendSciMsg( SCI_AUTOCSHOW, ( WPARAM ) len, ( LPARAM ) list );
}

void CSciMessager::autoCSetSeparator( char separator )
{
	SendSciMsg( SCI_AUTOCSETSEPARATOR, ( WPARAM ) separator );
}

void CSciMessager::autoCSetIgnoreCase( bool ignoreCase ) const
{
	SendSciMsg( SCI_AUTOCSETIGNORECASE, ( WPARAM ) ignoreCase );
}

int CSciMessager::getEOLMode() const
{
	return ( int ) SendSciMsg( SCI_GETEOLMODE );
}

int CSciMessager::getTabWidth() const
{
	return ( int ) SendSciMsg( SCI_GETTABWIDTH );
}

int CSciMessager::getFoldParent( int line ) const
{
	return ( int ) SendSciMsg( SCI_GETFOLDPARENT, ( WPARAM ) line );
}

int CSciMessager::getLineIndentation( int line ) const
{
	return ( int ) SendSciMsg( SCI_GETLINEINDENTATION, ( WPARAM ) line );
}

int CSciMessager::getLineIndentPosition( int line ) const
{
	return ( int ) SendSciMsg( SCI_GETLINEINDENTPOSITION, ( WPARAM ) line );
}

int CSciMessager::getLineCount() const
{
	return ( int ) SendSciMsg( SCI_GETLINECOUNT );
}

int CSciMessager::getFoldLevel( int line ) const
{
	return ( int ) SendSciMsg( SCI_GETFOLDLEVEL, ( WPARAM ) line );
}

int CSciMessager::getLineEndPos( int line ) const
{
	return ( int ) SendSciMsg( SCI_GETLINEENDPOSITION, ( WPARAM ) line );
}

int CSciMessager::getPosFromLine( int line ) const
{
	return ( int ) SendSciMsg( SCI_POSITIONFROMLINE, ( WPARAM ) line );
}

int CSciMessager::getLineLength( int line ) const
{
	return ( int ) SendSciMsg( SCI_LINELENGTH, ( WPARAM ) line );
}

int CSciMessager::getLine( int line, char * textbuf ) const
{
	return ( int ) SendSciMsg( SCI_GETLINE, ( WPARAM ) line, ( LPARAM ) textbuf );
}

void CSciMessager::setLineIndentation( int line, int indentation )
{
	SendSciMsg( SCI_SETLINEINDENTATION, ( WPARAM ) line, ( LPARAM ) indentation );
}
