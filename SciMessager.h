#ifndef __SCI_MESSAGER_H__
#define __SCI_MESSAGER_H__
//---------------------------------------------------------------------------

#include "NPP/Scintilla.h"

class CSciMessager
{
protected:
	HWND m_hSciWnd;
	SciFnDirect pSciMsg;
	sptr_t pSciWndData; 

public:
	CSciMessager( HWND hSciWnd = NULL );
	virtual ~CSciMessager();

	LRESULT SendSciMsg( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0 );
	LRESULT SendSciMsg( UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0 ) const;

	/* Text retrieval and modification */
	int           getText( int len, char* pText ) const;
	void          setText( const char* pText );
	void          beginUndoAction();
	void          endUndoAction();
	unsigned char getCharAt( int pos ) const;
	unsigned int  getCodePage() const; // 0 (non-Unicode), SC_CP_UTF8, DBCS etc.
	int           getCurrentPos() const;
	int				getCaretInLine() const;
	LRESULT       getDocPointer() const; // identifies the document
	int				getLineFromPos( int pos ) const;
	int				getLineState( int line ) const;
	HWND          getSciWnd() const  {
		return m_hSciWnd;
	}

	int           getSelectionMode() const; // SC_SEL_STREAM, SC_SEL_RECTANGLE, SC_SEL_LINES
	int           getSelectionEnd() const;
	int           getSelectionStart() const;
	int				getStyleAt( int pos ) const;
	int           getSelText( char* pText ) const;
	int           getTextLength() const;
	int           getTextRange( int pos1, int pos2, char* pText ) const;
	void          goToPos( int pos );
	bool          isModified() const;
	bool          isSelectionRectangle() const;
	bool		isAutoCActive() const;
	void          setCodePage( unsigned int codePage );
	void          setSciWnd( HWND hSciWnd )  {
		m_hSciWnd = hSciWnd;
	}
	void          setSel( int anchorPos, int currentPos );
	void          setSelectionMode( int mode ); // SC_SEL_STREAM, SC_SEL_RECTANGLE, SC_SEL_LINES
	void          setSelectionEnd( int pos );
	void          setSelectionStart( int pos );
	void          setSelText( const char* pText );
	void		  autoCShow( int len, const char *list );
	void		  autoCSetSeparator( char separator );
	void		  autoCSetIgnoreCase( bool ignoreCase ) const;

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
};

//---------------------------------------------------------------------------
#endif
